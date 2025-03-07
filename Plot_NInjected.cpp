#include <algorithm>
#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include "RtypesCore.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TLegendEntry.h"

#include "ROOT/RDF/InterfaceUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RResultPtr.hxx"
#include "ROOT/RVec.hxx"

#include "include/Style.hpp"

using namespace ROOT::RDF;
using RDataFrame = ROOT::RDataFrame;

using namespace ROOT::VecOps;

void Plot_NInjected(const TString& prod_dir = "./files/mc_23l1a3") {

    /* Config */

    std::vector<Char_t> channels = {'A', 'D'};
    std::vector<Color_t> colors = {static_cast<short>(MyStyle::Red.GetNumber()), static_cast<short>(MyStyle::Green.GetNumber())};
    std::vector<TString> masses = {"1.73", "1.8", "1.87", "1.94", "2.01"};
    std::vector<TString> plot_names = {"NInjected", "NFoundSignal"};

    TString Particle_latex = "#bar{S}";
    TString Property_latex = "m";
    TString Property_units = "GeV/c^{2}";

    const auto n_bins = (Int_t)masses.size();
    const Float_t x_min = 1.73;
    const Float_t x_max = 2.08;

    std::map<std::tuple<Char_t, TString>, std::unique_ptr<TH1D>> hist;
    Double_t val_mass;
    for (auto channel : channels) {
        /* init hists */
        for (const auto& plot_name : plot_names) {
            hist[{channel, plot_name}] =
                std::make_unique<TH1D>(Form("Channel %c -- %s", channel, plot_name.Data()),                                               //
                                       Form(";%s(%s) [%s];Counts", Property_latex.Data(), Particle_latex.Data(), Property_units.Data()),  //
                                       n_bins, x_min, x_max);
        }
        /* fill hists */
        for (size_t mm = 0; mm < masses.size(); mm++) {
            val_mass = masses[mm].Atof();
            RDataFrame df("Events", Form("%s/%c%s/SexaquarkResults_merged.root", prod_dir.Data(), channel, masses[mm].Data()));
            RNode node = df  //
                             .Define("NInjected", "Sexaquark_Px.size()")
                             .Define("NFoundSignal", Form("AS%c_Px[AS%c_IsSignal].size()", channel, channel));
            for (const auto& plot_name : plot_names) {
                RVec<size_t> ev_n = node.Take<size_t>(plot_name).GetValue();
                hist[{channel, plot_name}]->SetBinContent(mm + 1, (Double_t)Sum(ev_n));
                std::cout << "Channel " << channel << " Mass " << val_mass << " " << plot_name << " " << Sum(ev_n) << '\n';
            }
        }
    }

    /* Draw */

    std::filesystem::create_directories("gfx");
    const auto canvas_size = 800;

    MyStyle::SetMyStyle();
    gStyle->SetOptStat(0);
    gStyle->SetPadGridX(kTRUE);
    std::unique_ptr<TCanvas> c1 = std::make_unique<TCanvas>("c1", "", canvas_size, canvas_size);

    Double_t y_max = 0;
    for (const auto& plot_name : plot_names) {
        c1->Clear();
        y_max = 0;
        for (Int_t cc = 0; cc < channels.size(); cc++) {
            y_max = std::max(hist[{channels[cc], plot_name}]->GetMaximum(), y_max);
            hist[{channels[cc], plot_name}]->SetLineWidth(2);
            hist[{channels[cc], plot_name}]->SetLineColor(colors[cc]);
            hist[{channels[cc], plot_name}]->SetMarkerStyle(20);
            hist[{channels[cc], plot_name}]->SetMarkerColor(colors[cc]);
            hist[{channels[cc], plot_name}]->SetMarkerSize(1.2);
            if (cc == 0) {
                hist[{channels[cc], plot_name}]->GetYaxis()->SetMaxDigits(3);
                hist[{channels[cc], plot_name}]->GetXaxis()->SetNdivisions(200 + n_bins);
                hist[{channels[cc], plot_name}]->GetXaxis()->SetLabelSize(0.05);
                for (Int_t j = 0; j < n_bins; j++) hist[{channels[cc], plot_name}]->GetXaxis()->SetBinLabel(j + 1, masses[j]);
                hist[{channels[cc], plot_name}]->Draw("P E1");
            } else {
                hist[{channels[cc], plot_name}]->Draw("P E1 SAME");
            }
        }
        hist[{channels[0], plot_name}]->GetYaxis()->SetRangeUser(0, 1.1 * y_max);
        hist[{channels[0], plot_name}]->Draw("AXIS SAME");

        std::unique_ptr<TLegend> leg = std::make_unique<TLegend>(0.25, 0.25, 0.4, 0.35);
        leg->SetTextFont(62);
        leg->SetTextSize(0.02);
        leg->SetBorderSize(0);
        // leg->SetFillStyle(0);
        for (Int_t cc = 0; cc < channels.size(); cc++) {
            leg->AddEntry(hist[{channels[cc], plot_name}].get(), Form("Channel %c", channels[cc]), "pl");
            (dynamic_cast<TLegendEntry*>(leg->GetListOfPrimitives()->Last()))->SetTextColor(colors[cc]);
        }
        leg->Draw();

        c1->Print(Form("gfx/%s_vsMass.png", plot_name.Data()));
    }
}

int main() {
    Plot_NInjected();
    return 0;
}
