#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"

using namespace std;

void NormalizeHist(string rootfile) {

TFile* f = TFile::Open(rootfile.c_str(), "UPDATE");

//f->ls();

TH1F * hg1x = (TH1F*)f->Get("Number of clusters on g1x;1");
TH1F * hg1y = (TH1F*)f->Get("Number of clusters on g1y;1");
TH1F * hg2x = (TH1F*)f->Get("Number of clusters on g2x;1");
TH1F * hg2y = (TH1F*)f->Get("Number of clusters on g2y;1");
TH1F * hg3x = (TH1F*)f->Get("Number of clusters on g3x;1");
TH1F * hg3y = (TH1F*)f->Get("Number of clusters on g3y;1");

gStyle->SetTitleFontSize(0.06);
gStyle->SetOptStat(111111);
//gStyle->SetStatFontSize(0.1);

double scale = 1;
int entries = 0;
hg1x->SetLineColor(1.);
hg1x->SetMarkerColor(1.);
hg1x->GetXaxis()->SetTitle("Number of clusters");
hg1x->GetYaxis()->SetTitle("Entries [%]");
hg1x->GetXaxis()->SetTitleSize(0.06);
hg1x->GetYaxis()->SetTitleSize(0.06);
hg1x->GetXaxis()->SetLabelSize(0.06);
hg1x->GetYaxis()->SetLabelSize(0.06);
hg1x->GetXaxis()->SetNdivisions(6);
entries = hg1x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;	}
hg1x->Scale(scale);
//hg1x->Draw("");

scale = 1;
entries = 0;
hg1y->SetLineColor(1.);
hg1y->SetMarkerColor(1.);
hg1y->GetXaxis()->SetTitle("Number of clusters");
hg1y->GetYaxis()->SetTitle("Entries [%]");
hg1y->GetXaxis()->SetTitleSize(0.06);
hg1y->GetYaxis()->SetTitleSize(0.06);
hg1y->GetXaxis()->SetLabelSize(0.06);
hg1y->GetYaxis()->SetLabelSize(0.06);
hg1y->GetXaxis()->SetNdivisions(6);
entries = hg1y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
hg1y->Scale(scale);
//hg1y->Draw("");

scale = 1;
entries = 0;
hg2x->SetLineColor(1.);
hg2x->SetMarkerColor(1.);
hg2x->GetXaxis()->SetTitle("Number of clusters");
hg2x->GetYaxis()->SetTitle("Entries [%]");
hg2x->GetXaxis()->SetTitleSize(0.06);
hg2x->GetYaxis()->SetTitleSize(0.06);
hg2x->GetXaxis()->SetLabelSize(0.06);
hg2x->GetYaxis()->SetLabelSize(0.06);
hg2x->GetXaxis()->SetNdivisions(6);
entries = hg2x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
hg2x->Scale(scale);
//hg2x->Draw("");

scale = 1;
entries = 0;
hg2y->SetLineColor(1.);
hg2y->SetMarkerColor(1.);
hg2y->GetXaxis()->SetTitle("Number of clusters");
hg2y->GetYaxis()->SetTitle("Entries [%]");
hg2y->GetXaxis()->SetTitleSize(0.06);
hg2y->GetYaxis()->SetTitleSize(0.06);
hg2y->GetXaxis()->SetLabelSize(0.06);
hg2y->GetYaxis()->SetLabelSize(0.06);
hg2y->GetXaxis()->SetNdivisions(6);
entries = hg2y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
hg2y->Scale(scale);
//hg2y->Draw("");

scale = 1;
entries = 0;
hg3x->SetLineColor(1.);
hg3x->SetMarkerColor(1.);
hg3x->GetXaxis()->SetTitle("Number of clusters");
hg3x->GetYaxis()->SetTitle("Entries [%]");
hg3x->GetXaxis()->SetTitleSize(0.06);
hg3x->GetYaxis()->SetTitleSize(0.06);
hg3x->GetXaxis()->SetLabelSize(0.06);
hg3x->GetYaxis()->SetLabelSize(0.06);
hg3x->GetXaxis()->SetNdivisions(6);
entries = hg3x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
hg3x->Scale(scale);
//hg3x->Draw("");

scale = 1;
entries = 0;
hg3y->SetLineColor(1.);
hg3y->SetMarkerColor(1.);
hg3y->GetXaxis()->SetTitle("Number of clusters");
hg3y->GetYaxis()->SetTitle("Entries [%]");
hg3y->GetXaxis()->SetTitleSize(0.06);
hg3y->GetYaxis()->SetTitleSize(0.06);
hg3y->GetXaxis()->SetLabelSize(0.06);
hg3y->GetYaxis()->SetLabelSize(0.06);
hg3y->GetXaxis()->SetNdivisions(6);
entries = hg3y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
hg3y->Scale(scale);
//hg3y->Draw("");

TCanvas *c = new TCanvas("c","multipads",2000,1000);
c->Divide(3,2);

c->cd(1);
hg1x->Draw();
c->cd(2);
hg1y->Draw();
c->cd(3);
hg2x->Draw();
c->cd(4);
hg2y->Draw();
c->cd(5);
hg3x->Draw();
c->cd(6);
hg3y->Draw();


c->Write();

f->Write();


   TImage *img = TImage::Create();
   img->FromPad(c);
   size_t pos = rootfile.find(".root");
   string pngfile = rootfile.erase(pos,5);
   pngfile = pngfile.append(".png");

   img->WriteImage(pngfile.c_str());


f->Close();

}