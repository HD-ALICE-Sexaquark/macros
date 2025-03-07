#include <filesystem>
#include <memory>
#include <vector>

#include "RtypesCore.h"
#include "TCanvas.h"
#include "TH1.h"

#include "ROOT/RDF/InterfaceUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RResultPtr.hxx"

#include "include/Style.hpp"

using namespace ROOT::RDF;
using RDataFrame = ROOT::RDataFrame;

void Plot_Injected(const TString& input_path = "./files/mc_23l1a3/A*/SexaquarkResults_merged.root") {

    /* Config */

    std::vector<TString> Property_names = {"Pt", "Phi", "Pt_AfterReaction", "Radius"};
    std::vector<TString> Property_latex = {"p_{T}", "#phi", "p_{T} (after reaction)", "Radius"};
    std::vector<TString> Property_units = {"(GeV/c)", "(rad)", "(GeV/c)", "(cm)"};
    const std::vector<Float_t> min = {0., -1.2 * TMath::Pi(), 0., 0.};
    const std::vector<Float_t> max = {6., 1.2 * TMath::Pi(), 6., 200.};

    /* Init */

    RDataFrame df("Events", input_path);

    /* Define columns */

    RNode node = df.Define("Injected_Pt", "sqrt(Sexaquark_Px*Sexaquark_Px + Sexaquark_Py*Sexaquark_Py)")  //
                     .Define("Injected_Phi", "atan2(Sexaquark_Py, Sexaquark_Px)");

    /* Prepare histograms */

    const Int_t n_bins = 50;

    std::vector<RResultPtr<::TH1D>> hist;
    RResultPtr<::TH1D> h;
    for (size_t j = 0; j < Property_names.size(); j++) {
        h = node.Histo1D({TString::Format("Injected_%s", Property_names[j].Data()),                              //
                          TString::Format(";%s %s;Counts", Property_latex[j].Data(), Property_units[j].Data()),  //
                          n_bins, min[j], max[j]},                                                               //
                         TString::Format("Injected_%s", Property_names[j].Data()));
        hist.push_back(h);
    }

    /* Draw */

    std::filesystem::create_directories("gfx");
    const auto n_x = 2;
    const auto n_y = 2;
    const auto canvas_size = 600;

    gStyle->SetOptStat(0);
    std::unique_ptr<TCanvas> c1 = std::make_unique<TCanvas>("c1", "", n_x * canvas_size, n_y * canvas_size);
    c1->Divide(n_x, n_y);

    for (Int_t j = 0; j < Property_names.size(); j++) {
        c1->cd(j + 1);
        //
        hist[j]->GetYaxis()->SetMaxDigits(3);
        hist[j]->SetLineWidth(2);
        hist[j]->SetLineColor(MyStyle::Gray.GetNumber());
        hist[j]->Draw();
    }

    c1->Print("gfx/Injected.png");
    std::cout << "NRuns = " << df.GetNRuns() << '\n';
}

int main() {
    Plot_Injected();
    return 0;
}
