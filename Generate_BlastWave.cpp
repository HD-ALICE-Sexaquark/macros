#include <array>
#include <filesystem>
#include <memory>
#include <vector>

#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TString.h"

#include "Math/Functor.h"
#include "Math/Integrator.h"

/*
 * Define blast-wave function.
 */
Double_t BlastWaveFcn(Double_t* x, Double_t* par) {

    Double_t pt = x[0];

    Double_t m0 = par[0];
    Double_t T_kin = par[1];
    Double_t avg_beta_temp = par[2];
    Double_t np = par[3];

    Double_t mt = TMath::Sqrt(pt * pt + m0 * m0);
    Double_t beta_s = 0.5 * (np + 2) * avg_beta_temp;

    auto BlastWaveIntegrand = [&](Double_t r) -> Double_t {
        Double_t rho = TMath::ATanH(beta_s * TMath::Power(r, np));
        return r * TMath::BesselI0(pt * TMath::SinH(rho) / T_kin) * TMath::BesselK1(mt * TMath::CosH(rho) / T_kin);
    };

    ROOT::Math::Functor1D BlastWaveIntFunctor(BlastWaveIntegrand);
    ROOT::Math::Integrator integrator(BlastWaveIntFunctor);

    return pt * mt * integrator.Integral(0., 1.);
}

void Generate_BlastWave(const ULong_t n_entries = 1E6) {

    const std::vector<Float_t> m0 = {1.73, 1.8, 1.87, 1.94, 2.01};  // mass of the anti-sexaquark (in GeV/c^2)
    const Float_t min_pt = 0.;
    const Float_t max_pt = 10.;

    /* Parameters taken from Production of charged pions, kaons, and (anti-)protons in Pb-Pb and inelastic pp collisions at √sNN = 5.02 TeV */
    /* -- ALICE Collab. PRC 101, 044907 (2020) */
    const size_t n_centralities = 10;
    const std::array<TString, n_centralities> centr_str = {"0-5",   "5-10",  "10-20", "20-30", "30-40",  //
                                                           "40-50", "50-60", "60-70", "70-80", "80-90"};
    const std::array<Float_t, n_centralities> t_kin = {0.090, 0.091, 0.094, 0.097, 0.101,  // kinetic freeze-out temperature (in GeV)
                                                       0.108, 0.115, 0.129, 0.147, 0.161};
    const std::array<Float_t, n_centralities> avg_beta_temp = {0.663, 0.660, 0.655, 0.643, 0.622,  // transverse velocity profile
                                                               0.595, 0.557, 0.506, 0.435, 0.355};
    const std::array<Float_t, n_centralities> np = {0.735, 0.736, 0.739, 0.771, 0.828,  // radial flow power
                                                    0.908, 1.052, 1.262, 1.678, 2.423};

    std::filesystem::create_directories("output");
    TString output_filename = "output/blastwave.root";

    std::unique_ptr<TFile> file(TFile::Open(output_filename, "RECREATE"));
    if (!file || file->IsZombie()) {
        std::cout << "!! ERROR !! Generate_BlastWave !! Couldn't open TFile " << output_filename << " !!\n";
        return;
    }

    std::unique_ptr<TRandom3> rnd = std::make_unique<TRandom3>(0);
    std::unique_ptr<TF1> f;
    std::unique_ptr<TH1D> h;
    const Int_t n_bins = 100;
    for (auto inv_mass : m0) {
        for (Int_t centr_i = 0; centr_i < n_centralities; centr_i++) {

            /* Function */

            f = std::make_unique<TF1>(TString::Format("Fcn_BlastWave_%.2f_%s", inv_mass, centr_str.at(centr_i).Data()), BlastWaveFcn, min_pt, max_pt,
                                      4);
            f->SetParameter(0, inv_mass);
            f->SetParameter(1, t_kin.at(centr_i));
            f->SetParameter(2, avg_beta_temp.at(centr_i));
            f->SetParameter(3, np.at(centr_i));

            file->WriteObject(f.get(), f->GetName());

            /* Histogram */

            h = std::make_unique<TH1D>(TString::Format("Hist_BlastWave_%.2f_%s", inv_mass, centr_str.at(centr_i).Data()), "", n_bins, min_pt, max_pt);
            h->Sumw2();

            for (ULong_t i = 0; i < n_entries; i++) {
                h->Fill(f->GetRandom(rnd.get()));
            }

            file->WriteObject(h.get(), h->GetName());
        }
    }

    std::cout << "!! INFO  !! Generate_BlastWave !! TFile " << output_filename << " has been created !!\n";
}

int main() {
    Generate_BlastWave();
    return 0;
}
