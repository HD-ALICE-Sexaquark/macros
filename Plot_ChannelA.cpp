#include <filesystem>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "RtypesCore.h"
#include "TAttLine.h"
#include "TCanvas.h"
#include "TH1.h"

#include "Math/Vector4D.h"

#include "ROOT/RDF/InterfaceUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RResultPtr.hxx"
#include "ROOT/RVec.hxx"

#include "include/Style.hpp"

using PxPyPzEVector = ROOT::Math::PxPyPzEVector;

using namespace ROOT::RDF;
using RDataFrame = ROOT::RDataFrame;

using namespace ROOT::VecOps;
using RVecD = ROOT::RVecD;
using cRVecD = const ROOT::RVecD&;

void Plot_ChannelA(const TString& input_path = "./files/mc_23l1*3/*/SexaquarkResults_merged.root") {

    /* Config */

    std::vector<TString> Property_names = {"Mass",     "P",           "Pt",          "Mass_asDecay", "Rapidity",        "Zv",
                                           "Eta",      "Phi",         "Radius",      "DCAV0aSV",     "DCAV0aNegSV",     "DCAV0aPosSV",
                                           "DCAV0bSV", "DCAV0bNegSV", "DCAV0bPosSV", "DCAbtwV0s",    "V0a_DecayLength", "V0b_DecayLength"};
    std::vector<TString> Property_latex = {"m(#bar{p}#pi^{-}#pi^{+}#pi^{-}-n)",
                                           "p",
                                           "p_{T}",
                                           "m(#bar{p}#pi^{-}#pi^{+}#pi^{-})",
                                           "Rapidity",
                                           "v_{z}",
                                           "#eta",
                                           "#phi",
                                           "Radius",
                                           "DCA(#bar{#Lambda},SV)",
                                           "DCA(#bar{#Lambda}#rightarrow#bar{p},SV)",
                                           "DCA(#bar{#Lambda}#rightarrow#pi^{+},SV)",
                                           "DCA(K^{0}_{S},SV)",
                                           "DCA(K^{0}_{S}#rightarrow#pi^{-},SV)",
                                           "DCA(K^{0}_{S}#rightarrow#pi^{+},SV)",
                                           "DCA(#bar{#Lambda},K^{0}_{S})",
                                           "DecayLength(#bar{#Lambda})",
                                           "DecayLength(K^{0}_{S})"};
    std::vector<TString> Property_units = {"GeV/c^{2}", "GeV/c", "GeV/c", "GeV/c^{2}", "-",  "cm", "-",  "rad", "cm",
                                           "cm",        "cm",    "cm",    "cm",        "cm", "cm", "cm", "cm",  "cm"};
    const std::vector<Float_t> min = {-4., 0., 0., 0., -1.2, -200., -1.2, -1.2 * TMath::Pi(), 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
    const std::vector<Float_t> max = {4., 50., 10., 10., 1.2, 200., 1.2, 1.2 * TMath::Pi(), 200., 15., 15., 15., 15., 15., 15., 3., 100., 100.};
    std::vector<TString> Condition = {"", "ASA_IsSignal", "ASA_IsHybrid", "!ASA_IsSignal && !ASA_IsHybrid"};
    std::vector<TString> Tag_names = {"", "IsSignal", "IsHybrid", "TrueBkg"};
    std::vector<Color_t> Tag_colors = {static_cast<Short_t>(MyStyle::Blue.GetNumber()), static_cast<Short_t>(MyStyle::Red.GetNumber()),  //
                                       static_cast<Short_t>(MyStyle::Green.GetNumber()), static_cast<Short_t>(MyStyle::Purple.GetNumber())};

    /* Init */

    RDataFrame df("Events", input_path);

    /* Define columns */

    RNode node = df.Define("LV_ASA",
                           [](cRVecD asa_px, cRVecD asa_py, cRVecD asa_pz, cRVecD asa_e) {
                               RVec<PxPyPzEVector> output;
                               output.reserve(asa_px.size());
                               for (size_t i = 0; i < asa_e.size(); i++) {
                                   output.emplace_back(PxPyPzEVector(asa_px[i], asa_py[i], asa_pz[i], asa_e[i]));
                               }
                               return output;
                           },
                           {"ASA_Px", "ASA_Py", "ASA_Pz", "ASA_E"})
                     .Define("LV_ASA_asDecay",
                             [](cRVecD asa_px, cRVecD asa_py, cRVecD asa_pz, cRVecD asa_e) {
                                 RVec<PxPyPzEVector> output;
                                 output.reserve(asa_px.size());
                                 for (size_t i = 0; i < asa_e.size(); i++) {
                                     output.emplace_back(PxPyPzEVector(asa_px[i], asa_py[i], asa_pz[i], asa_e[i]));
                                 }
                                 return output;
                             },
                             {"ASA_Px", "ASA_Py", "ASA_Pz", "ASA_EasDecay"})
                     .Define("ASA_Mass", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.M(); });")
                     .Define("ASA_P", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.P(); });")
                     .Define("ASA_Pt", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.Pt(); });")
                     .Define("ASA_Mass_asDecay", "return Map(LV_ASA_asDecay, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.M(); });")
                     .Define("ASA_Rapidity", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.Rapidity(); });")
                     .Define("ASA_Eta", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.Eta(); });")
                     .Define("ASA_Phi", "return Map(LV_ASA, [](const ROOT::Math::PxPyPzEVector& lv) { return lv.Rapidity(); });")
                     .Define("ASA_Radius", "sqrt(ASA_Xv*ASA_Xv + ASA_Yv*ASA_Yv)");
    for (const auto& prop_name : Property_names) {
        for (size_t k = 0; k < Tag_names.size(); k++) {
            if (Tag_names[k] == "") continue;
            node = node.Define(Form("ASA_%s__%s", prop_name.Data(), Tag_names[k].Data()),  //
                               Form("ASA_%s[%s]", prop_name.Data(), Condition[k].Data()));
        }
    }

    /* Prepare histograms */

    const Int_t n_bins = 50;

    std::map<std::tuple<TString, TString>, RResultPtr<::TH1D>> hist;
    std::map<TString, std::unique_ptr<TH1D>> sb_ratio;
    RResultPtr<::TH1D> h;
    TString col_name = "";
    for (size_t j = 0; j < Property_names.size(); j++) {
        for (auto& tag_name : Tag_names) {
            col_name = Form("ASA_%s%s", Property_names[j].Data(), tag_name == "" ? "" : ("__" + tag_name).Data());
            h = node.Histo1D({col_name, Form(";%s (%s);Counts", Property_latex[j].Data(), Property_units[j].Data()),  //
                              n_bins, min[j], max[j]},
                             col_name);
            hist[{Property_names[j], tag_name}] = h;
        }
    }

    /* Draw */

    std::filesystem::create_directories("gfx");
    const Int_t max_n_col = 3;
    const auto n_rows = (Int_t)Property_names.size() / max_n_col + (Property_names.size() % max_n_col != 0);
    const auto canvas_size = 600;

    gStyle->SetOptStat(0);
    std::unique_ptr<TCanvas> c1 = std::make_unique<TCanvas>("c1", "", max_n_col * canvas_size, n_rows * canvas_size);
    c1->Divide(max_n_col, n_rows);

    Double_t y_max = 0;
    for (Int_t j = 0; j < Property_names.size(); j++) {
        c1->cd(j + 1);
        y_max = 0;
        for (Int_t k = 0; k < Tag_names.size(); k++) {
            y_max = std::max(y_max, hist[{Property_names[j], Tag_names[k]}]->GetMaximum());
            hist[{Property_names[j], Tag_names[k]}]->SetLineWidth(2);
            hist[{Property_names[j], Tag_names[k]}]->SetLineColor(Tag_colors[k]);
            if (k == 0) {
                hist[{Property_names[j], Tag_names[k]}]->GetYaxis()->SetMaxDigits(3);
                hist[{Property_names[j], Tag_names[k]}]->Draw("P E1");
            } else {
                hist[{Property_names[j], Tag_names[k]}]->Draw("P E1 SAME");
            }
        }
        hist[{Property_names[j], Tag_names[0]}]->GetYaxis()->SetRangeUser(0, 1.2 * y_max);
        hist[{Property_names[j], Tag_names[0]}]->Draw("AXIS SAME");
        /*  */
        sb_ratio[Property_names[j]] =
            std::make_unique<TH1D>(Form("ASA_%s__SBRatio", Property_names[j].Data()),
                                   Form(";%s (%s);S/B", Property_latex[j].Data(), Property_units[j].Data()), n_bins, min[j], max[j]);
        sb_ratio[Property_names[j]]->Divide(hist[{Property_names[j], "IsSignal"}].GetPtr(), hist[{Property_names[j], "TrueBkg"}].GetPtr(), 1., 1.,
                                            "B");
    }
    c1->Print("gfx/ChannelA.png");

    c1->Clear();
    c1->Divide(max_n_col, n_rows);
    for (Int_t j = 0; j < Property_names.size(); j++) {
        c1->cd(j + 1);
        sb_ratio[Property_names[j]]->SetLineColor(MyStyle::Gray.GetNumber());
        sb_ratio[Property_names[j]]->SetMarkerColor(MyStyle::Gray.GetNumber());
        sb_ratio[Property_names[j]]->SetMarkerSize(10.);
        sb_ratio[Property_names[j]]->SetLineWidth(2);
        sb_ratio[Property_names[j]]->Draw("P E1");
        MyStyle::DrawHorizontalLine(1., MyStyle::Red, kDashed, 2);
    }
    c1->Print("gfx/ChannelA_SB.png");

    std::cout << "NRuns = " << df.GetNRuns() << '\n';
}

int main() {
    Plot_ChannelA();
    return 0;
}
