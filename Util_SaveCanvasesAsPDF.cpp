#include <filesystem>
#include <format>
#include <memory>
#include <print>
#include <string_view>

#include <TCanvas.h>
#include <TFile.h>
#include <TKey.h>
#include <TList.h>
#include <TROOT.h>

#include "include/Constants.hpp"
#include "include/Style.hpp"
namespace SM = SexaquarkMacros;

void Util_SaveCanvasesAsPDF(SM::Const::EStages stage = SM::Const::kDeepESD,                   //
                            std::string_view input_filename = "output/DeepESD_Canvas1D.root"  //
) {

    // Open File //

    std::unique_ptr<TFile> input_file(TFile::Open(static_cast<std::string>(input_filename).c_str(), "READ"));
    if (input_file == nullptr || input_file->IsZombie()) {
        std::println(stderr, "ERROR :: Util_SaveCanvasesAsPDF :: Can't open TFile {}", input_filename);
        return;
    }
    std::println(stdout, "INFO  :: Util_SaveCanvasesAsPDF :: Opened TFile {}", input_filename);

    // Prepare Output Dir //

    std::string output_dir{std::format("{}/{}", SM::Const::PlotsDir, SM::Const::StagesDirNames[stage])};
    std::filesystem::create_directories(output_dir);

    // Draw //

    SM::Style::SetStyle();

    for (auto *obj : *input_file->GetListOfKeys()) {
        auto *key = dynamic_cast<TKey *>(obj);
        if (gROOT->GetClass(key->GetClassName()) != TCanvas::Class()) continue;
        auto *c = key->ReadObject<TCanvas>();
        std::string output_path{std::format("{}/{}.pdf", output_dir, c->GetName())};
        c->SaveAs(output_path.c_str());
    }
}

int main() {
    Util_SaveCanvasesAsPDF();
    return 0;
}
