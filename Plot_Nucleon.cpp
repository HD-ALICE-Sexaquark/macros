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

void Plot_Nucleon(const TString& input_path = "./files/mc_23l1a3/*/SexaquarkResults_merged.root") {

    /* Config */

    std::vector<TString> Property_names = {"P", "Phi", "Theta", "Px", "Py", "Pz"};
    std::vector<TString> Property_latex = {"p", "#phi", "#theta", "P_{x}", "P_{y}", "P_{z}"};
    std::vector<TString> Property_units = {"GeV/c", "rad", "rad", "GeV/c", "GeV/c", "GeV/c"};
    const std::vector<Float_t> min = {0.2, -1.2 * TMath::Pi(), 0., -0.3, -0.3, -0.3};
    const std::vector<Float_t> max = {0.3, 1.2 * TMath::Pi(), TMath::Pi(), 0.3, 0.3, 0.3};

    /* Init */

    RDataFrame df("Events", input_path);

    /* Define columns */

    RNode node = df.Define("Nucleon_P", "sqrt(Nucleon_Px*Nucleon_Px + Nucleon_Py*Nucleon_Py + Nucleon_Pz*Nucleon_Pz)")
                     .Define("Nucleon_Phi", "atan2(Nucleon_Py, Nucleon_Px)")
                     .Define("Nucleon_Theta", "acos(Nucleon_Pz / Nucleon_P)");

    /* Prepare histograms */

    const Int_t n_bins = 50;

    std::vector<RResultPtr<::TH1D>> hist;
    RResultPtr<::TH1D> h;
    for (size_t j = 0; j < Property_names.size(); j++) {
        h = node.Histo1D({TString::Format("Nucleon_%s", Property_names[j].Data()),                                 //
                          TString::Format(";%s (%s);Counts", Property_latex[j].Data(), Property_units[j].Data()),  //
                          n_bins, min[j], max[j]},                                                                 //
                         TString::Format("Nucleon_%s", Property_names[j].Data()));
        hist.push_back(h);
    }

    /* Draw */

    std::filesystem::create_directories("gfx");
    const auto n_x = 3;
    const auto n_y = (Int_t)Property_names.size() / n_x;
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

    c1->Print("gfx/Nucleon.png");
    std::cout << "NRuns = " << df.GetNRuns() << '\n';
}

int main() {
    Plot_Nucleon();
    return 0;
}
