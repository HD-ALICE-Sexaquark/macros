#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <tuple>
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

void Plot_V0s(const TString& input_path = "./files/mc_23l1a3/A*/SexaquarkResults_merged.root") {

    /* Config */

    std::vector<std::string> V0s_names = {"AL", "K0S"};
    std::vector<std::string> V0s_dau_latex = {"#bar{p}#pi^{+}", "#pi^{-}#pi^{+}"};
    std::vector<std::string> Property_names = {"Mass", "Pt", "Radius"};
    std::vector<std::string> Property_latex = {"m", "p_{T}", "Radius"};
    std::vector<std::string> Property_units = {"GeV/c^{2}", "GeV/c", "cm"};
    std::map<std::tuple<std::string, std::string>, Float_t> min = {{{"AL", "Mass"}, 1.08}, {{"K0S", "Mass"}, 0.47},  //
                                                                   {{"AL", "Pt"}, 0.},     {{"K0S", "Pt"}, 0.},
                                                                   {{"AL", "Radius"}, 0.}, {{"K0S", "Radius"}, 0.}};
    std::map<std::tuple<std::string, std::string>, Float_t> max = {{{"AL", "Mass"}, 1.16},   {{"K0S", "Mass"}, 0.53},  //
                                                                   {{"AL", "Pt"}, 5.},       {{"K0S", "Pt"}, 5.},
                                                                   {{"AL", "Radius"}, 200.}, {{"K0S", "Radius"}, 200.}};

    /* Init */

    RDataFrame df("Events", input_path);
    RNode node = df;

    /* Define columns */

    TString prop_expression;
    for (const std::string& V0 : V0s_names) {
        prop_expression = Form("sqrt(%s_E*%s_E - %s_Px*%s_Px - %s_Py*%s_Py - %s_Pz*%s_Pz)",  //
                               V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str());
        node = node.Define(V0 + "_Mass", prop_expression.Data());
        //
        prop_expression = Form("sqrt(%s_Px*%s_Px + %s_Py*%s_Py)",  //
                               V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str());
        node = node.Define(V0 + "_Pt", prop_expression.Data());
        //
        prop_expression = Form("sqrt(%s_Xv*%s_Xv + %s_Yv*%s_Yv)",  //
                               V0.c_str(), V0.c_str(), V0.c_str(), V0.c_str());
        node = node.Define(V0 + "_Radius", prop_expression.Data());
        //
        for (const std::string& prop : Property_names) {
            node = node.Define(Form("%s_%s__IsSignal", V0.c_str(), prop.c_str()),  //
                               Form("%s_%s[%s_IsSignal]", V0.c_str(), prop.c_str(), V0.c_str()));
        }
    }

    /* Prepare histograms */

    const Int_t n_bins = 50;

    std::map<std::tuple<std::string, std::string, std::string>, RResultPtr<::TH1D>> hist;
    RResultPtr<::TH1D> h;
    for (size_t i = 0; i < V0s_names.size(); i++) {
        for (size_t j = 0; j < Property_names.size(); j++) {
            for (const std::string& is_signal : {"", "__IsSignal"}) {
                h = node.Histo1D({Form("%s_%s%s", V0s_names[i].c_str(), Property_names[j].c_str(), is_signal.c_str()),                          //
                                  Form(";%s(%s) [%s];Counts", Property_latex[j].c_str(), V0s_dau_latex[i].c_str(), Property_units[j].c_str()),  //
                                  n_bins,                                                                                                       //
                                  min[{V0s_names[i], Property_names[j]}],                                                                       //
                                  max[{V0s_names[i], Property_names[j]}]},                                                                      //
                                 Form("%s_%s%s", V0s_names[i].c_str(), Property_names[j].c_str(), is_signal.c_str()));
                hist[{V0s_names[i], Property_names[j], is_signal}] = h;
            }
        }
    }

    /* Draw */

    std::filesystem::create_directories("gfx");
    const auto n_x = (Int_t)Property_names.size();
    const auto canvas_size = 600;

    gStyle->SetOptStat(0);
    std::unique_ptr<TCanvas> c1 = std::make_unique<TCanvas>("c1", "", n_x * canvas_size, canvas_size);

    TString h_name;
    for (auto& V0s_name : V0s_names) {
        c1->Clear();
        c1->Divide(n_x, 1);
        for (Int_t j = 0; j < n_x; j++) {
            c1->cd(j + 1);
            //
            hist[{V0s_name, Property_names[j], ""}]->GetYaxis()->SetMaxDigits(3);
            hist[{V0s_name, Property_names[j], ""}]->SetLineWidth(2);
            hist[{V0s_name, Property_names[j], ""}]->SetLineColor(MyStyle::Blue.GetNumber());
            hist[{V0s_name, Property_names[j], ""}]->Draw();
            //
            hist[{V0s_name, Property_names[j], "__IsSignal"}]->SetLineWidth(2);
            hist[{V0s_name, Property_names[j], "__IsSignal"}]->SetLineColor(MyStyle::Red.GetNumber());
            hist[{V0s_name, Property_names[j], "__IsSignal"}]->Draw("SAME");
            //
            hist[{V0s_name, Property_names[j], ""}]->Draw("AXIS SAME");
        }
        c1->Print(Form("gfx/%s.png", V0s_name.c_str()));
    }

    std::cout << "NRuns = " << df.GetNRuns() << '\n';
}

int main() {
    Plot_V0s();
    return 0;
}
