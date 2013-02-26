// C++ headers
#include <iostream>
#include <vector>
// ROOT headers
#include "TROOT.h"
#include <TSystem.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
// RooFit headers
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooExtendPdf.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
// RooStat headers
#include "RooWorkspace.h"
#include "RooStats/SPlot.h"
// local files
#include "CMSStyle.C"
// Verbosity
#define DEBUG 0
// namespaces
using namespace std;
using namespace RooFit;
//using namespace RooStats;

// **************************************************************************************************************************
int main(int argc, char *argv[])
{
	// ##### GET ARGUMENTS #####
	cout << "argc= " << argc << endl;
	for(int iarg = 0 ; iarg < argc ; iarg++)
		cout << "argv[" << iarg << "]= " << argv[iarg] << endl;
	if( argc < 2 )
	{
		cout << "arguments should be passed !" << endl;
		return 1;
	}
	string filename = argv[1];
	string wspaceName = "WS_" + filename + ".root";

	// ##### INITIALIZATION OF PLOT STYLE #####
	gROOT->Reset();
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TCanvas *canvas = new TCanvas();

	// Open Rooworkspace
	TFile *f = new TFile(wspaceName.c_str());
	RooWorkspace *ws = (RooWorkspace*)f->Get("cms_hgg_workspace");
	ws->Print();

	RooRealVar *hggpdf_cat0_background_norm = ws->var("hggpdf_cat0_background_norm");
	RooRealVar *hggpdf_cat0_signal_norm = ws->var("hggpdf_cat0_signal_norm");
	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << endl;
	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;

	RooRealVar *PhotonsMass = ws->var("PhotonsMass");	
	RooRealVar *dipho_E = ws->var("dipho_E");
	RooRealVar *dipho_pt = ws->var("dipho_pt");
	RooRealVar *dipho_eta = ws->var("dipho_eta");
	RooRealVar *dipho_phi = ws->var("dipho_phi");
	RooRealVar *dipho_cosThetaStar_CS = ws->var("dipho_cosThetaStar_CS");
	RooRealVar *dipho_tanhYStar = ws->var("dipho_tanhYStar");
	RooRealVar *dipho_Y = ws->var("dipho_Y");
	RooRealVar *category = ws->var("category");
	RooRealVar *evweight = ws->var("evweight");
	RooRealVar *pu_weight = ws->var("pu_weight");
	RooArgSet *allVariables = new RooArgSet();
	allVariables->add(*PhotonsMass);
	allVariables->add(*dipho_E);
	allVariables->add(*dipho_pt);
	allVariables->add(*dipho_eta);
	allVariables->add(*dipho_phi);
	allVariables->add(*dipho_cosThetaStar_CS);
	allVariables->add(*dipho_tanhYStar);
	allVariables->add(*dipho_Y);
	allVariables->add(*category);
	allVariables->add(*evweight);
	allVariables->add(*pu_weight);

	RooPlot *mgg_frame = PhotonsMass->frame();
	RooAbsPdf *bkgpdf = ws->pdf("model_background_class_cat0");
//	bkgpdf->plotOn(mgg_frame, Normalization(hggpdf_cat0_background_norm->getVal()), LineColor(kRed));

	RooAbsPdf *sigpdf = ws->pdf("model_signal_class_cat0");

	double nsignal = hggpdf_cat0_signal_norm->getVal();
	double nbackground = hggpdf_cat0_background_norm->getVal();
	double ntot = nsignal + nbackground;	
//	double c_signal = nsignal / ntot;
//	double c_background = nbackground / ntot;
//	RooRealVar *csig = new RooRealVar("csig", "csig", c_signal);
//	RooRealVar *sigYield = new RooRealVar("sigYield", "sigYield", nsignal);
//	RooRealVar *bkgYield = new RooRealVar("bkgYield", "bkgYield", nbackground);

//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", *sigpdf, *bkgpdf, *csig);
//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*sigYield, *bkgYield));
	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*hggpdf_cat0_signal_norm, *hggpdf_cat0_background_norm));
	RooDataSet *toy = (RooDataSet*)totpdf->generate(*allVariables, ntot);
	toy->plotOn(mgg_frame);
	// fix signal parameters
	RooRealVar *frac_0_cat0 = ws->var("frac_0_cat0");		frac_0_cat0->setConstant();
	RooRealVar *frac_1_cat0 = ws->var("frac_1_cat0");		frac_1_cat0->setConstant();
	RooRealVar *mu_signal_0_cat0 = ws->var("mu_signal_0_cat0");		mu_signal_0_cat0->setConstant();
	RooRealVar *mu_signal_1_cat0 = ws->var("mu_signal_1_cat0");		mu_signal_1_cat0->setConstant();
	RooRealVar *mu_signal_2_cat0 = ws->var("mu_signal_2_cat0");		mu_signal_2_cat0->setConstant();
	RooRealVar *sigma_signal_0_cat0 = ws->var("sigma_signal_0_cat0");		sigma_signal_0_cat0->setConstant();
	RooRealVar *sigma_signal_1_cat0 = ws->var("sigma_signal_1_cat0");		sigma_signal_1_cat0->setConstant();
	RooRealVar *sigma_signal_2_cat0 = ws->var("sigma_signal_2_cat0");		sigma_signal_2_cat0->setConstant();
	// first fit of toy data with bkg pdf
	bkgpdf->fitTo(*toy, Extended());
	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << endl;
	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;
	// then fit the total pdf
//	sigpdf->plotOn(mgg_frame, Normalization(hggpdf_cat0_signal_norm->getVal()), LineColor(kGreen));
	totpdf->fitTo(*toy, Extended());
	totpdf->plotOn(mgg_frame, Components(*bkgpdf), LineColor(kRed));
	totpdf->plotOn(mgg_frame, Components(*sigpdf), LineColor(kPink));
	totpdf->plotOn(mgg_frame);

// now with the splot
// first : set model parameters to constant
	RooRealVar *pol0_cat0 = ws->var("pol0_cat0");		pol0_cat0->setConstant();
	RooRealVar *pol1_cat0 = ws->var("pol1_cat0");		pol1_cat0->setConstant();
	RooRealVar *pol2_cat0 = ws->var("pol2_cat0");		pol2_cat0->setConstant();
	RooRealVar *pol3_cat0 = ws->var("pol3_cat0");		pol3_cat0->setConstant();
	RooRealVar *pol4_cat0 = ws->var("pol4_cat0");		pol4_cat0->setConstant();
//	toy->Print();
//	toy->plotOn(mgg_frame);
	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << endl;
	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;

	cout << "##### Preparing SPlot #####" << endl;
//	const RooArgList *liste = new RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm);
//	RooStats::SPlot::SPlot *splot = new RooStats::SPlot::SPlot();
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, sigpdf, *liste);
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, sigpdf, RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm));
	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, totpdf, RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm));
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, *sigpdf, *liste, RooArgSet(), kTRUE, kFALSE, "");
//RooArgSet& projDeps = RooArgSet(), bool includeWeights = kTRUE, bool copyDataSet = kFALSE, const char* newName = ""
//	cout << "Printing out sWeights" << endl;
//	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;
//	cout << "splot->GetYieldFromSWeight(\"hggpdf_cat0_signal_norm\")= " << splot->GetYieldFromSWeight("hggpdf_cat0_signal_norm") << endl;


	mgg_frame->Draw();
	canvas->Print("dump.pdf");	

	delete splot;
	splot = 0;

	f->Close();
	delete f;
	f = 0;

	delete canvas;
	canvas = 0;
	return 0;
}

