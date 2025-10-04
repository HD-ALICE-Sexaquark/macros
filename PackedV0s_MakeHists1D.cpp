#include <cstddef>
#include <filesystem>
#include <format>
#include <memory>
#include <print>
#include <string_view>
#include <vector>

#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

#include <Math/Point3D.h>
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
using XYZPoint = ROOT::Math::XYZPoint;
using XYZVector = ROOT::Math::XYZVector;
using PxPyPzEVector = ROOT::Math::PxPyPzEVector;

#include "include/Constants.hpp"
#include "include/DF_PackedEvents.hpp"
#include "include/HP_PackedV0s.hpp"
#include "include/Math.hpp"
namespace SM = SexaquarkMacros;
namespace PV0s = SM::PackedV0s;

void PackedV0s_MakeHists1D(std::string_view v0_name = "K0S", bool is_mc = true,                   //
                           std::string_view input_path = "files/t2s_packed/Packed_MC_A1.80.root"  //
) {

    // Macro Properties //

    std::string tree_name{SM::Const::StagesNames[SM::Const::kPackedEvents]};

    const int n_bins{100};

    // -- override histogram properties
    if (v0_name == "AL") {
        PV0s::Properties_latex[PV0s::Mass] = SM::Const::Latex_AntiLambda;
        PV0s::Properties_min[PV0s::Mass] = SM::Const::MinMass_Lambda;
        PV0s::Properties_max[PV0s::Mass] = SM::Const::MaxMass_Lambda;
    } else if (v0_name == "L") {
        PV0s::Properties_latex[PV0s::Mass] = SM::Const::Latex_Lambda;
        PV0s::Properties_min[PV0s::Mass] = SM::Const::MinMass_Lambda;
        PV0s::Properties_max[PV0s::Mass] = SM::Const::MaxMass_Lambda;
    } else {  // ~ v0_name == "K0S"
        PV0s::Properties_latex[PV0s::Mass] = SM::Const::Latex_K0S;
        PV0s::Properties_min[PV0s::Mass] = SM::Const::MinMass_K0S;
        PV0s::Properties_max[PV0s::Mass] = SM::Const::MaxMass_K0S;
    }

    // Prepare Input //

    auto chain = std::make_unique<TChain>();
    chain->Add(std::format("{}/{}", input_path, tree_name).c_str());

    TTreeReader reader{chain.get()};
    SM::Packed::Event event{reader};
    SM::Packed::V0 v0{reader, v0_name};
    SM::Packed::MC_V0 mc_v0{reader, v0_name};

    // Prepare Output //

    std::filesystem::create_directories(SM::Const::OutputDir);
    auto output_file =
        std::make_unique<TFile>(std::format("{}/Packed{}_{}_Hists1D.root", SM::Const::OutputDir, is_mc ? "MC" : "RD", v0_name).c_str(), "RECREATE");

    // Prepare Histograms //

    std::vector<std::vector<TH1D>> vvHists(PV0s::NSubsets);
    for (auto& v : vvHists) v.reserve(PV0s::NProperties);

    for (size_t ss{0}; ss < PV0s::NSubsets; ++ss) {
        for (size_t pp{0}; pp < PV0s::NProperties; ++pp) {
            TH1D hist{std::format("{}{}", PV0s::Properties_names[pp], PV0s::Subsets_names[ss]).c_str(),  //
                      std::format(";{};Counts", PV0s::Properties_latex[pp]).c_str(),                     //
                      n_bins, PV0s::Properties_min[pp], PV0s::Properties_max[pp]};
            vvHists[ss].push_back(hist);
        }
    }

    // Fill Histograms //

    // loop over events
    while (reader.Next()) {

        // get event properties
        XYZPoint pv{*event.PV_Xv, *event.PV_Yv, *event.PV_Zv};
        float bz{*event.MagneticField};

        // loop over subsets
        for (size_t rr{0}; rr < PV0s::NSubsets; ++rr) {

            // loop over v0s
            for (size_t vv{0}; vv < v0.GetSize(); ++vv) {

                if (rr == PV0s::True && !static_cast<bool>(mc_v0.IsTrue[vv])) continue;
                if (rr == PV0s::Secondary && !static_cast<bool>(mc_v0.IsSecondary[vv])) continue;
                if (rr == PV0s::Signal && !static_cast<bool>(mc_v0.IsSignal[vv])) continue;
                if (rr == PV0s::Hybrid && !static_cast<bool>(mc_v0.IsHybrid[vv])) continue;
                if (rr == PV0s::RealBkg && (static_cast<bool>(mc_v0.IsSignal[vv]) || static_cast<bool>(mc_v0.IsHybrid[vv]))) continue;

                XYZPoint v0_xyz{v0.X[vv], v0.Y[vv], v0.Z[vv]};
                vvHists[rr][PV0s::DecayX].Fill(v0_xyz.X());
                vvHists[rr][PV0s::DecayY].Fill(v0_xyz.Y());
                vvHists[rr][PV0s::DecayZ].Fill(v0_xyz.Z());
                // vvHists[rr][PV0s::Phi].Fill(phi);
                vvHists[rr][PV0s::Radius2D].Fill(v0_xyz.Rho());

                PxPyPzEVector v0_lv{v0.Px[vv], v0.Py[vv], v0.Pz[vv], v0.E[vv]};
                vvHists[rr][PV0s::Px].Fill(v0_lv.Px());
                vvHists[rr][PV0s::Py].Fill(v0_lv.Py());
                vvHists[rr][PV0s::Pz].Fill(v0_lv.Pz());
                vvHists[rr][PV0s::Pt].Fill(v0_lv.Pt());
                vvHists[rr][PV0s::P].Fill(v0_lv.P());
                vvHists[rr][PV0s::Mass].Fill(v0_lv.M());
                vvHists[rr][PV0s::Eta].Fill(v0_lv.Eta());

                vvHists[rr][PV0s::CPAwrtPV].Fill(SM::Math::CosinePointingAngle(v0_lv.Vect(), v0_xyz, pv));
                vvHists[rr][PV0s::DCAwrtPV].Fill(SM::Math::FastDCALineVertex(v0_lv.Vect(), v0_xyz, pv));

                XYZPoint neg_xyz{v0.Neg_X_AtPCA[vv], v0.Neg_Y_AtPCA[vv], v0.Neg_Z_AtPCA[vv]};
                XYZPoint pos_xyz{v0.Pos_X_AtPCA[vv], v0.Pos_Y_AtPCA[vv], v0.Pos_Z_AtPCA[vv]};

                XYZVector neg_v3{v0.Neg_Px_AtPCA[vv], v0.Neg_Py_AtPCA[vv], v0.Neg_Pz_AtPCA[vv]};
                XYZVector pos_v3{v0.Pos_Px_AtPCA[vv], v0.Pos_Py_AtPCA[vv], v0.Pos_Pz_AtPCA[vv]};

                double arm_qt_over_alpha{SM::Math::ArmenterosQt(v0_lv.Vect(), neg_v3) /
                                         std::abs(SM::Math::ArmenterosAlpha(v0_lv.Vect(), neg_v3, pos_v3))};
                vvHists[rr][PV0s::ArmQtOverAlpha].Fill(arm_qt_over_alpha);

                double dca_neg_v0{SM::Math::FastDCAHelixVertex(neg_v3, neg_xyz, -1, v0_xyz, bz)};
                vvHists[rr][PV0s::DCAnegV0].Fill(dca_neg_v0);

                double dca_pos_v0{SM::Math::FastDCAHelixVertex(neg_v3, neg_xyz, +1, v0_xyz, bz)};
                vvHists[rr][PV0s::DCAposV0].Fill(dca_pos_v0);

                vvHists[rr][PV0s::DCAbtwDau].Fill((neg_xyz - pos_xyz).R());
            }
        }
    }

    // Save //

    output_file->cd();

    for (size_t pp{0}; pp < PV0s::NProperties; ++pp) {
        for (size_t ss{0}; ss < PV0s::NSubsets; ++ss) {
            vvHists[ss][pp].Write();
        }
    }

    std::println(stdout, "INFO  :: PackedV0s_MakeHists1D :: TFile {} has been created", output_file->GetName());
}

int main() {
    PackedV0s_MakeHists1D();
    return 0;
}
