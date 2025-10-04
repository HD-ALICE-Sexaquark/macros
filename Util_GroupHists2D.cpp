#include <filesystem>
#include <format>
#include <print>
#include <string_view>
#include <vector>

#include <TCanvas.h>
#include <TFile.h>
#include <TH2.h>
#include <TKey.h>

#include "include/Constants.hpp"
#include "include/HP_DeepESD.hpp"
#include "include/HP_PackedV0s.hpp"
#include "include/Style.hpp"
namespace SM = SexaquarkMacros;

void Util_GroupHists2D(SM::Const::EStages stage = SM::Const::kDeepESD,                                      //
                       std::string_view input_filename = "files/deep_esd/AnalysisResults_A1.8_wave3b.root"  //
) {

    // Settings //

    int n_props_2d{};
    const std::vector<std::string_view>* props_1d{nullptr};
    const std::vector<int>* props_2d_y{nullptr};
    const std::vector<int>* props_2d_x{nullptr};
    int n_sets{};
    const std::vector<std::string_view>* suffixes{nullptr};

    if (stage == SM::Const::kDeepESD) {
        n_props_2d = SM::DeepESD::EProp2D::NProps2D;
        props_1d = &SM::DeepESD::Prop1D_Name;
        props_2d_y = &SM::DeepESD::Prop2D_YProp;
        props_2d_x = &SM::DeepESD::Prop2D_XProp;
        n_sets = SM::DeepESD::ESet::NSets;
        suffixes = &SM::DeepESD::Set_Suffix;
    } else if (stage == SM::Const::kConverted) {
        // PENDING
    } else if (stage == SM::Const::kPackedEvents) {
        // PENDING
    } else if (stage == SM::Const::kFound) {
        // PENDING
    }

    // Open File //

    std::unique_ptr<TFile> input_file(TFile::Open(static_cast<std::string>(input_filename).c_str(), "READ"));
    if (input_file == nullptr || input_file->IsZombie()) {
        std::println(stderr, "ERROR :: Util_GroupHists2D :: Can't open TFile {}", input_filename);
        return;
    }
    std::println(stdout, "INFO  :: Util_GroupHists2D :: Opened TFile {}", input_filename);

    // -- get TList when analyzing DeepESD //

    TList* list{};
    if (stage == SM::Const::kDeepESD) {
        std::string tlist_name{"Hists2D"};
        list = input_file->Get<TList>(tlist_name.data());
        if (list == nullptr) {
            std::println(stderr, "ERROR :: Util_GroupHists2D :: TList \"{}\" couldn't be loaded", tlist_name);
            return;
        }
    }

    // Prepare Output //

    std::filesystem::create_directories(SM::Const::OutputDir);
    auto output_file =
        std::make_unique<TFile>(std::format("{}/{}_Canvas2D.root", SM::Const::OutputDir, SM::Const::StagesNames[stage]).c_str(), "RECREATE");

    // Extract and Group Histograms //

    std::vector<std::vector<TH2D*>> all_hists(n_sets);

    for (int pp{0}; pp < n_props_2d; ++pp) {
        for (int ss{0}; ss < n_sets; ++ss) {
            std::string y_axis_name{props_1d->at(props_2d_y->at(pp))};
            std::string x_axis_name{props_1d->at(props_2d_x->at(pp))};
            std::string hist_name{std::format("{}_vs_{}{}", y_axis_name, x_axis_name, suffixes->at(ss))};
            TH2D* hist{nullptr};
            if (stage == SM::Const::kDeepESD) {
                hist = dynamic_cast<TH2D*>(list->FindObject(hist_name.c_str()));
            } else {
                hist = input_file->Get<TH2D>(hist_name.c_str());
            }
            all_hists[ss].push_back(hist);
        }
    }

    // Draw //

    output_file->cd();

    for (int pp{0}; pp < n_props_2d; ++pp) {

        std::string y_axis_name{props_1d->at(props_2d_y->at(pp))};
        std::string x_axis_name{props_1d->at(props_2d_x->at(pp))};
        std::string c_name{std::format("{}_vs_{}", y_axis_name, x_axis_name)};
        auto c = std::make_unique<TCanvas>(c_name.c_str(), c_name.c_str(), SM::Style::Default::CanvasSize, SM::Style::Default::CanvasSize);
        c->Divide(5, 3);

        // PENDING
        // if (pp <= DE::EProp2D::TPC_DCAz_vs_TPC_DCAxy) c->SetLogz(1);
        // if (pp >= DE::EProp2D::TPC_Signal_vs_Inner_P && pp <= DE::EProp2D::TPC_SignalTuned_vs_Inner_Eta) c->SetLogy(1);

        for (int ss{0}; ss < n_sets; ++ss) {
            c->cd(ss + 1);
            std::string hist_title{suffixes->at(ss) == "" ? "All" : suffixes->at(ss)};
            all_hists[ss][pp]->SetTitle(hist_title.c_str());
            all_hists[ss][pp]->SetTitleSize(1.5);
            all_hists[ss][pp]->Draw("COLZ");
        }

        c->Write();
    }

    std::println(stdout, "INFO  :: Util_GroupHists2D :: TFile {} has been created", output_file->GetName());
}

int main() {
    Util_GroupHists2D();
    return 0;
}
