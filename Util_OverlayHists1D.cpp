#include <filesystem>
#include <format>
#include <print>
#include <string_view>
#include <vector>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TKey.h>

#include "include/Constants.hpp"
#include "include/HP_DeepESD.hpp"
#include "include/HP_PackedV0s.hpp"
#include "include/Style.hpp"
#include "include/Utilities.hpp"
namespace SM = SexaquarkMacros;

void Util_OverlayHists1D(SM::Const::EStages stage = SM::Const::kDeepESD,  //
                         std::string_view input_filename = "files/deep_esd/AnalysisResults_A1.8_wave3b.root") {

    // Settings //

    int n_properties{};
    const std::vector<std::string_view>* properties{nullptr};
    int n_sets{};
    const std::vector<std::string_view>* suffixes{nullptr};

    if (stage == SM::Const::kDeepESD) {
        n_properties = SM::DeepESD::EProp1D::NProps1D;
        properties = &SM::DeepESD::Prop1D_Name;
        n_sets = SM::DeepESD::ESet::NSets;
        suffixes = &SM::DeepESD::Set_Suffix;
    } else if (stage == SM::Const::kConverted) {
        // PENDING
    } else if (stage == SM::Const::kPackedV0s) {
        n_properties = SM::PackedV0s::EProperties::NProperties;
        properties = &SM::PackedV0s::Properties_names;
        n_sets = SM::PackedV0s::ESubsets::NSubsets;
        suffixes = &SM::PackedV0s::Subsets_names;
    } else if (stage == SM::Const::kFound) {
        // PENDING
    }

    // Open File //

    std::unique_ptr<TFile> input_file(TFile::Open(static_cast<std::string>(input_filename).c_str(), "READ"));
    if (input_file == nullptr || input_file->IsZombie()) {
        std::println(stderr, "ERROR :: Util_OverlayHists1D :: Can't open TFile {}", input_filename);
        return;
    }
    std::println(stdout, "INFO  :: Util_OverlayHists1D :: Opened TFile {}", input_filename);

    // -- Get List If  //

    TList* list{};
    if (stage == SM::Const::kDeepESD) {
        std::string tlist_name{"Hists1D"};
        list = input_file->Get<TList>(tlist_name.data());
        if (list == nullptr) {
            std::println(stderr, "ERROR :: Util_OverlayHists1D :: TList \"{}\" couldn't be loaded", tlist_name);
            return;
        }
    }

    // Prepare Output //

    std::filesystem::create_directories(SM::Const::OutputDir);
    auto output_file =
        std::make_unique<TFile>(std::format("{}/{}_Canvas1D.root", SM::Const::OutputDir, SM::Const::StagesNames[stage]).c_str(), "RECREATE");

    // Extract and Group Histograms //

    std::vector<std::vector<TH1D*>> all_hists(n_sets);

    for (int pp{0}; pp < n_properties; ++pp) {
        for (int ss{0}; ss < n_sets; ++ss) {
            std::string hist_name{std::format("{}{}", properties->at(pp), suffixes->at(ss))};
            TH1D* hist{nullptr};
            if (stage == SM::Const::kDeepESD) {
                hist = dynamic_cast<TH1D*>(list->FindObject(hist_name.c_str()));
            } else {
                hist = input_file->Get<TH1D>(hist_name.c_str());
            }
            all_hists[ss].push_back(hist);
        }
    }

    // Draw //

    output_file->cd();

    for (int pp{0}; pp < n_properties; ++pp) {

        auto c = std::make_unique<TCanvas>(properties->at(pp).data(), properties->at(pp).data(),  //
                                           SM::Style::Default::CanvasSize, SM::Style::Default::CanvasSize);
        c->SetLogy();

        // auto leg = std::make_unique<TLegend>();

        for (int ss{0}; ss < n_sets; ++ss) {
            all_hists[ss][pp]->SetLineWidth(2);
            if (ss == 0) {
                all_hists[ss][pp]->SetLineColor(EColor::kBlack);
                all_hists[ss][pp]->SetMinimum(1);
                all_hists[ss][pp]->Draw("HIST");
            } else {
                all_hists[ss][pp]->SetLineColor(static_cast<short>(SM::Style::Blue.GetNumber() + ss - 1));
                all_hists[ss][pp]->Draw("HIST SAME");
            }
            // leg->AddEntry(all_hists[ss][pp], DE::Set_Suffix[ss].data());
        }
        // leg->Draw();

        c->Write();
    }

    std::println(stdout, "INFO  :: DeepESD_MakeHists1D :: TFile {} has been created", output_file->GetName());
}

int main() {
    Util_OverlayHists1D();
    return 0;
}
