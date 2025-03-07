#ifndef MACROS_STYLE_HPP
#define MACROS_STYLE_HPP

#include "RtypesCore.h"
#include "TColor.h"
#include "TH1.h"
#include "TH2.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TText.h"
#include "TVirtualPad.h"

namespace MyStyle {

// colors based on matplotlib main colors
TColor Blue(TColor::GetFreeColorIndex(), 31. / 255., 119. / 255., 180. / 255., "myBlue");
TColor Orange(TColor::GetFreeColorIndex(), 255. / 255., 127. / 255., 14. / 255., "myOrange");
TColor Green(TColor::GetFreeColorIndex(), 44. / 255., 160. / 255., 44. / 255., "myGreen");
TColor Red(TColor::GetFreeColorIndex(), 214. / 255., 39. / 255., 40. / 255., "myRed");
TColor Purple(TColor::GetFreeColorIndex(), 148. / 255., 103. / 255., 189. / 255., "myPurple");
TColor Brown(TColor::GetFreeColorIndex(), 140. / 255., 86. / 255., 75. / 255., "myBrown");
TColor Pink(TColor::GetFreeColorIndex(), 227. / 255., 119. / 255., 194. / 255., "myPink");
TColor Gray(TColor::GetFreeColorIndex(), 127. / 255., 127. / 255., 127. / 255., "myGray");
TColor Olive(TColor::GetFreeColorIndex(), 188. / 255., 189. / 255., 34. / 255., "myOlive");
TColor Cyan(TColor::GetFreeColorIndex(), 23. / 255., 190. / 255., 207. / 255., "myCyan");

TColor TransparentBlue(TColor::GetFreeColorIndex(), 31. / 255., 119. / 255., 180. / 255., "myTransparentBlue", 0.33);
TColor TransparentOrange(TColor::GetFreeColorIndex(), 255. / 255., 127. / 255., 14. / 255., "myTransparentOrange", 0.33);
TColor TransparentGreen(TColor::GetFreeColorIndex(), 44. / 255., 160. / 255., 44. / 255., "myTransparentGreen", 0.33);
TColor TransparentRed(TColor::GetFreeColorIndex(), 214. / 255., 39. / 255., 40. / 255., "myTransparentRed", 0.33);
TColor TransparentPurple(TColor::GetFreeColorIndex(), 148. / 255., 103. / 255., 189. / 255., "myTransparentPurple", 0.33);
TColor TransparentBrown(TColor::GetFreeColorIndex(), 140. / 255., 86. / 255., 75. / 255., "myTransparentBrown", 0.33);
TColor TransparentPink(TColor::GetFreeColorIndex(), 227. / 255., 119. / 255., 194. / 255., "myTransparentPink", 0.33);
TColor TransparentGray(TColor::GetFreeColorIndex(), 127. / 255., 127. / 255., 127. / 255., "myTransparentGray", 0.33);
TColor TransparentOlive(TColor::GetFreeColorIndex(), 188. / 255., 189. / 255., 34. / 255., "myTransparentOlive", 0.33);
TColor TransparentCyan(TColor::GetFreeColorIndex(), 23. / 255., 190. / 255., 207. / 255., "myTransparentCyan", 0.33);

inline void DrawHorizontalLine(Double_t y, const TColor &color, Style_t style, Width_t width) {
    gPad->Update();
    Double_t v = (y - gPad->GetY1()) / (gPad->GetY2() - gPad->GetY1());
    // v = (y - y1)/(y2 - y1);
    TLine *liney = new TLine(gPad->GetLeftMargin(), v, 1. - gPad->GetRightMargin(), v);
    liney->SetLineColor(static_cast<Color_t>(color.GetNumber()));  // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,)3}
    liney->SetLineStyle(style);                                    // kSolid, kDashed, kDotted
    liney->SetLineWidth(width);
    liney->SetNDC(kTRUE);
    liney->Draw();
}

inline void DrawVerticalLine(Double_t x, const TColor &color, Style_t style, Width_t width) {
    gPad->Update();
    Double_t u = (x - gPad->GetX1()) / (gPad->GetX2() - gPad->GetX1());
    // u = (x - x1)/(x2 - x1);
    TLine *linex = new TLine(u, gPad->GetBottomMargin(), u, 1. - gPad->GetTopMargin());
    linex->SetLineColor(static_cast<Color_t>(color.GetNumber()));  // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,)3}
    linex->SetLineStyle(style);                                    // kSolid, kDashed, kDotted
    linex->SetLineWidth(width);
    linex->SetNDC(kTRUE);
    linex->Draw();
}

inline void Set1DHistStyle(TH1 *theHist) {
    theHist->SetTitle("");
    theHist->SetLineWidth(2);
    theHist->SetFillStyle(0);

    theHist->GetYaxis()->SetTitleSize(0.04);
    theHist->GetYaxis()->SetTitleOffset(1.4);
    theHist->GetYaxis()->SetMaxDigits(3);
    theHist->GetYaxis()->SetTitleFont(62);

    theHist->GetXaxis()->SetTitleSize(0.04);
    theHist->GetXaxis()->SetTitleOffset(1.2);
    theHist->GetXaxis()->SetTitleFont(62);
}

inline void SetMyStyle() {
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetLineWidth(2);
    // set margin sizes
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadRightMargin(0.1);
    gStyle->SetPadBottomMargin(0.2);
    gStyle->SetPadLeftMargin(0.2);
}

inline void DrawText(const TString &content, const TColor &color, Float_t min_x, Float_t min_y, Short_t text_h_align, Short_t text_v_align) {
    TPaveText *pav = new TPaveText(min_x, min_y, min_x + 0.3, min_y + 0.1, "NDC");  // x1,y1,x2,y2
    pav->AddText(content);
    pav->SetTextSize(0.03);
    pav->SetTextColor(static_cast<Color_t>(color.GetNumber()));
    dynamic_cast<TText *>(pav->GetListOfLines()->Last())->SetTextAlign(text_h_align + text_v_align);
    pav->SetBorderSize(0);
    pav->SetFillStyle(0);
    // pav->SetFillColor(kWhite);
    pav->SetTextAlign(12);
    pav->Draw();
}

inline void Set2DHistStyle(TH2F *theHist) {
    theHist->SetTitle("");

    theHist->GetYaxis()->SetTitleSize(0.04);
    theHist->GetYaxis()->SetTitleOffset(1.2);
    theHist->GetYaxis()->SetTitleFont(62);

    theHist->GetXaxis()->SetTitleSize(0.04);
    theHist->GetXaxis()->SetTitleOffset(1.2);
    theHist->GetXaxis()->SetTitleFont(62);

    theHist->GetZaxis()->SetMaxDigits(3);
    theHist->GetZaxis()->SetTickLength(0.02);
}

inline void Set2DStyle() {
    gStyle->SetLineWidth(2);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    // gStyle->SetPalette(kDarkBodyRadiator);
    gStyle->SetNumberContours(255);
}

}  // namespace MyStyle

#endif
