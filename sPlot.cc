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
#include "RooProdPdf.h"
#include "RooBernstein.h"
#include "RooGaussian.h"
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

void addToyDataToWorkSpace(RooWorkspace *ws)
{
	cout << "##### ADD TOY DATA TO WORKSPACE #####" << endl;
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
	RooRealVar dummy("dummy", "dummy", -10., 10.);
	RooRealVar mu_sig("mu_sig", "mu_sig", 5.);
	RooRealVar sigma_sig("sigma_sig", "sigma_sig", 1.0);
	RooRealVar mu_bkg("mu_bkg", "mu_bkg", -5.);
	RooRealVar sigma_bkg("sigma_bkg", "sigma_bkg", 1.0);
	RooGaussian dummy_sig("dummy_sig", "dummy_sig", dummy, mu_sig, sigma_sig);
	RooGaussian dummy_bkg("dummy_bkg", "dummy_bkg", dummy, mu_bkg, sigma_bkg);

	RooAbsPdf *bkgpdf = ws->pdf("model_background_bernstein_class_0");
	RooAbsPdf *sigpdf = ws->pdf("gauss_signal_class_cat0");
	cout << "##### PREPARING AND GENERATING TOY DATA #####" << endl;
	double nbackground = 20000;
	double nsignal = nbackground * 0.02;
	double ntot = nsignal + nbackground;
	cout << "### NTOT= " << ntot << " ###" << endl;
	RooRealVar *nsig = new RooRealVar("nsig", "nsig", nsignal, 0., 100000.);
	RooRealVar *nbkg = new RooRealVar("nbkg", "nbkg", nbackground, 0., 100000.);
	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*nsig, *nbkg));
	totpdf->graphVizTree("dump____model.dot");

	RooAddPdf *dummypdf = new RooAddPdf("dummypdf", "dummypdf", RooArgList(dummy_sig, dummy_bkg), RooArgList(*nsig, *nbkg));
//	RooProdPdf twodmodel("twodmodel", "twodmodel", RooArgList(*totpdf, *dummypdf));


	RooProdPdf *sig = new RooProdPdf("sig", "sig", RooArgList(*sigpdf, dummy_sig));
	RooProdPdf *bkg = new RooProdPdf("bkg", "bkg", RooArgList(*bkgpdf, dummy_bkg));
	RooAddPdf twodmodel("twodmodel", "twodmodel", RooArgList(*sig, *bkg), RooArgList(*nsig, *nbkg));

//	RooDataSet *toyData = (RooDataSet*)totpdf->generate(*allVariables, ntot);
	RooDataSet *toyData = (RooDataSet*)twodmodel.generate(RooArgList(*PhotonsMass, dummy), ntot);

	TCanvas *canvas = new TCanvas();
	RooPlot *dummy_frame = dummy.frame();
	RooPlot *mgg_frame = PhotonsMass->frame();
	toyData->plotOn(dummy_frame);
	toyData->plotOn(mgg_frame);
	dummy_sig.plotOn(dummy_frame, LineColor(kRed));
	sigpdf->plotOn(mgg_frame, LineColor(kRed));
	dummy_bkg.plotOn(dummy_frame);
	bkgpdf->plotOn(mgg_frame);

	dummy_frame->Draw();
	canvas->Print("dump_dummy.pdf");
	canvas->Clear();

	mgg_frame->Draw();
	canvas->Print("dump_mgg.pdf");
	canvas->Clear();	

	cout << "##### IMPORT (TOY) DATA #####" << endl;

	ws->import(*toyData, Rename("data"));

	return;
}

void makeCombinedModel(RooWorkspace *ws)
{
	cout << "##### SETTING UP SIGNAL+BACKGROUND MODEL #####" << endl;
	RooAbsPdf *bkgpdf = ws->pdf("model_background_bernstein_class_0");
	RooAbsPdf *sigpdf = ws->pdf("gauss_signal_class_cat0");
	RooRealVar *nsig = new RooRealVar("nsig", "nsig", 10., 0., 10000.);
	RooRealVar *nbkg = new RooRealVar("nbkg", "nbkg", 90., 0., 50000.);
	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*nsig, *nbkg));
	RooDataSet* data = (RooDataSet*)ws->data("data");
//	totpdf->fitTo(*data, Extended());

	cout << "##### IMPORT MODEL INTO WORKSPACE #####" << endl;
	ws->import(*totpdf);
	return;
}

void doSPlot(RooWorkspace *ws)
{
	TCanvas *canvas = new TCanvas();
	cout << "# READ WORKSPACE CONTENT #" << endl;
	ws->Print();
	RooAbsPdf *totpdf = ws->pdf("totpdf");
	RooRealVar *nsig = ws->var("nsig");
	RooRealVar *nbkg = ws->var("nbkg");
	RooDataSet *data = (RooDataSet*) ws->data("data");
	RooRealVar *PhotonsMass = ws->var("PhotonsMass");
	RooRealVar *dummy = ws->var("dummy");
//	RooAbsPdf *bkgpdf = ws->pdf("model_background_bernstein_class_0");
//	RooAbsPdf *sigpdf = ws->pdf("gauss_signal_class_cat0");
//	RooArgSet* pdfObs = totpdf->getObservables(*data);
//	pdfObs->Print();

	RooRealVar *frac_0_cat0 = ws->var("frac_0_cat0");   frac_0_cat0->setConstant();
	RooRealVar *mu_signal_0_cat0 = ws->var("mu_signal_0_cat0");   mu_signal_0_cat0->setConstant();
	RooRealVar *mu_signal_1_cat0 = ws->var("mu_signal_1_cat0");   mu_signal_1_cat0->setConstant();
	RooRealVar *sigma_signal_0_cat0 = ws->var("sigma_signal_0_cat0");   sigma_signal_0_cat0->setConstant();
	RooRealVar *sigma_signal_1_cat0 = ws->var("sigma_signal_1_cat0");   sigma_signal_1_cat0->setConstant();

	// fix signal model parameters
	cout << "# FIT DATA #" << endl;
	totpdf->fitTo(*data, Extended());
//	totpdf->fitTo(*data);
	RooPlot *mgg_frame = PhotonsMass->frame();
	data->plotOn(mgg_frame);
	totpdf->plotOn(mgg_frame, Components("gauss_signal_class_cat0"), LineStyle(kDashed), LineColor(kCyan));
	totpdf->plotOn(mgg_frame, Components("model_background_bernstein_class_0"), LineStyle(kDashed), LineColor(kRed));
	totpdf->plotOn(mgg_frame);
	mgg_frame->Draw();
	canvas->Print("dump.pdf");
	canvas->Clear();
	cout << "# PREPARE SPLOT #" << endl;
	RooRealVar *pol0_cat0 = ws->var("pol0_cat0");   pol0_cat0->setConstant();
	RooRealVar *pol1_cat0 = ws->var("pol1_cat0");   pol1_cat0->setConstant();
	RooRealVar *pol2_cat0 = ws->var("pol2_cat0");   pol2_cat0->setConstant();
	RooRealVar *pol3_cat0 = ws->var("pol3_cat0");   pol3_cat0->setConstant();
	RooRealVar *pol4_cat0 = ws->var("pol4_cat0");   pol4_cat0->setConstant();
	
	cout << "# SPLOT #" << endl;
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *data, totpdf, RooArgList(*nsig, *nbkg));
//	ws->pdf("totpdf")->Dump();
//	totpdf->Print();
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *data, totpdf, RooArgList(*nsig, *nbkg));
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *data, (RooAddPdf*)ws->pdf("totpdf"), RooArgList(*nsig, *nbkg));
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *((RooDataSet*)ws->data("data")), ws->pdf("totpdf"), RooArgList(*(ws->var("nsig")), *(ws->var("nbkg"))));
/*
	RooRealVar *mu0 = new RooRealVar("mu0", "mu0", mu_signal_0_cat0->getVal());
	RooRealVar *mu1 = new RooRealVar("mu1", "mu1", mu_signal_1_cat0->getVal());
	RooRealVar *sig0 = new RooRealVar("sig0", "sig0", sigma_signal_0_cat0->getVal());
	RooRealVar *sig1 = new RooRealVar("sig1", "sig1", sigma_signal_1_cat0->getVal());
	RooRealVar *f0 = new RooRealVar("f0", "f0", frac_0_cat0->getVal());
	RooRealVar *p0 = new RooRealVar("p0", "p0", pol0_cat0->getVal());
	RooRealVar *p1 = new RooRealVar("p1", "p1", pol1_cat0->getVal());
	RooRealVar *p2 = new RooRealVar("p2", "p2", pol2_cat0->getVal());
	RooRealVar *p3 = new RooRealVar("p3", "p3", pol3_cat0->getVal());
	RooRealVar *p4 = new RooRealVar("p4", "p4", pol4_cat0->getVal());

	RooGaussian *gau0 = new RooGaussian("gau0", "gau0", *PhotonsMass, *mu0, *sig0);
	RooGaussian *gau1 = new RooGaussian("gau1", "gau1", *PhotonsMass, *mu1, *sig1);
	RooAddPdf *sig = new RooAddPdf("sig", "sig", RooArgList(*gau0, *gau1), *f0);
	RooBernstein *bkg = new RooBernstein("bkg", "bkg", *PhotonsMass, RooArgList(*p0, *p1, *p2, *p3, *p4));
	RooAddPdf *totpdf2 = new RooAddPdf("totpdf2", "totpdf2", RooArgList(*sig, *bkg), RooArgList(*nsig, *nbkg));
*/
	RooGaussian *gau0 = new RooGaussian("gau0", "gau0", *PhotonsMass, *mu_signal_0_cat0, *sigma_signal_0_cat0);
	RooGaussian *gau1 = new RooGaussian("gau1", "gau1", *PhotonsMass, *mu_signal_1_cat0, *sigma_signal_1_cat0);
	RooAddPdf *sig = new RooAddPdf("sig", "sig", RooArgList(*gau0, *gau1), *frac_0_cat0);
	RooBernstein *bkg = new RooBernstein("bkg", "bkg", *PhotonsMass, RooArgList(*pol0_cat0, *pol1_cat0, *pol2_cat0, *pol3_cat0, *pol4_cat0));
	RooAddPdf *totpdf2 = new RooAddPdf("totpdf2", "totpdf2", RooArgList(*sig, *bkg), RooArgList(*nsig, *nbkg));
	totpdf2->fitTo(*data, Extended());

	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *data, totpdf2, RooArgList(*nbkg, *nsig));

/*
	RooStats::SPlot *splot2 = new RooStats::SPlot("splot", "splot", *data, ws->pdf("totpdf"), RooArgList(*nsig, *nbkg));

	cout << "##### NEXT TRY, WITH DUMMY VARIABLE #####" << endl;
	RooRealVar mu1("mu1", "mu1", 0., 10.);
	RooRealVar mu2("mu2", "mu2", -10., 0.);
	RooRealVar sig1("sig1", "sig1", 0., 2.);
	RooRealVar sig2("sig2", "sig2", 0., 2.);
	RooGaussian g1("g1", "g1", *dummy, mu1, sig1);
	RooGaussian g2("g2", "g2", *dummy, mu2, sig2);
	RooAddPdf *gg = new RooAddPdf("gg", "gg", RooArgList(g1, g2), RooArgList(*nsig, *nbkg));
	gg->fitTo(*data, Extended());

	RooPlot *dummy_frame = dummy->frame();
	data->plotOn(dummy_frame);
	gg->plotOn(dummy_frame);
	dummy_frame->Draw();
	canvas->Print("dump2.pdf");
	canvas->Clear();


	mu1.setConstant();
	mu2.setConstant();
	sig1.setConstant();
	sig2.setConstant();

	RooStats::SPlot *splot3 = new RooStats::SPlot("splot3", "splot3", *data, gg, RooArgList(*nsig, *nbkg));
*/

	RooRealVar mu_sig("mu_sig", "mu_sig", 5.);
	RooRealVar sigma_sig("sigma_sig", "sigma_sig", 1.0);
	RooRealVar mu_bkg("mu_bkg", "mu_bkg", -5.);
	RooRealVar sigma_bkg("sigma_bkg", "sigma_bkg", 1.0);
	RooGaussian dummy_sig("dummy_sig", "dummy_sig", *dummy, mu_sig, sigma_sig);
	RooGaussian dummy_bkg("dummy_bkg", "dummy_bkg", *dummy, mu_bkg, sigma_bkg);

	RooDataSet * dataw = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"nsig_sw"); 
	RooPlot *sdummy_frame = dummy->frame();
	dataw->plotOn(sdummy_frame);
	dummy_sig.plotOn(sdummy_frame);
	sdummy_frame->Draw();
	canvas->Print("dumps.pdf");
	canvas->Clear();

	RooPlot *smgg_frame = PhotonsMass->frame();
	dataw->plotOn(smgg_frame);
	sig->plotOn(smgg_frame);
	smgg_frame->Draw();
	canvas->Print("dumpss.pdf");
	canvas->Clear();

	RooDataSet * datawb = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"nbkg_sw"); 
	RooPlot *sdummy_frameb = dummy->frame();
	datawb->plotOn(sdummy_frameb);
	dummy_bkg.plotOn(sdummy_frameb);
	sdummy_frameb->Draw();
	canvas->Print("dumpb.pdf");
	canvas->Clear();

	RooPlot *smgg_frameb = PhotonsMass->frame();
	datawb->plotOn(smgg_frameb);
	bkg->plotOn(smgg_frameb);
	smgg_frameb->Draw();
	canvas->Print("dumpbb.pdf");
	canvas->Clear();

	return;
}

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
	cout << "##### OPEN AND PRINT ROOWORKSPACE #####" << endl;
	TFile *f = new TFile(wspaceName.c_str());
	RooWorkspace *ws = (RooWorkspace*)f->Get("cms_hgg_workspace");

//	ws->Print();
	addToyDataToWorkSpace(ws);
//	ws->Print();
	makeCombinedModel(ws);
	ws->Print();
	doSPlot(ws);


/*
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
	RooPlot *mgg_frame_signal = PhotonsMass->frame();
	RooPlot *mgg_frame_background = PhotonsMass->frame();
//	RooAbsPdf *bkgpdf = ws->pdf("model_background_class_cat0");
	RooAbsPdf *bkgpdf = ws->pdf("model_background_bernstein_class_0");
//	RooBernstein *bkgpdf = (RooBernstein*)(ws->pdf("model_background_class_cat0");
//	bkgpdf->plotOn(mgg_frame, Normalization(hggpdf_cat0_background_norm->getVal()), LineColor(kRed));
//	RooAbsPdf *sigpdf = ws->pdf("model_signal_class_cat0");
	RooAbsPdf *sigpdf = ws->pdf("gauss_signal_class_cat0");
//	RooAddPdf *sigpdf = ws->pdf("model_signal_class_cat0");

	cout << "##### PREPARING AND GENERATING TOY DATA #####" << endl;
	double nsignal = 10000;
	double nbackground = 10000;
//	double nsignal = hggpdf_cat0_signal_norm->getVal();
//	double nbackground = hggpdf_cat0_background_norm->getVal();
	double ntot = nsignal + nbackground;	
//	double ntot = 10;
	cout << "### NTOT= " << ntot << " ###" << endl;
//	double c_signal = nsignal / ntot;
//	double c_background = nbackground / ntot;
//	RooRealVar *csig = new RooRealVar("csig", "csig", c_signal);
//	RooRealVar *sigYield = new RooRealVar("sigYield", "sigYield", nsignal);
//	RooRealVar *bkgYield = new RooRealVar("bkgYield", "bkgYield", nbackground);

//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", *sigpdf, *bkgpdf, *csig);
//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*sigYield, *bkgYield));
	RooRealVar *nsig = new RooRealVar("nsig", "nsig", nsignal, 0., 100000.);
	RooRealVar *nbkg = new RooRealVar("nbkg", "nbkg", nbackground, 0., 100000.);
//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*hggpdf_cat0_signal_norm, *hggpdf_cat0_background_norm));
	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*nsig, *nbkg));
	totpdf->graphVizTree("dump_model.dot");
//	ntot = 100000;
	ntot = ntot*0.9;
//	RooAddPdf *totpdf = new RooAddPdf("totpdf", "totpdf", RooArgList(*sigpdf, *bkgpdf), RooArgList(*nsig, *nbkg));
//	RooDataSet *toy = (RooDataSet*)totpdf->generate(*allVariables, 1000);
//	RooDataSet *toy = (RooDataSet*)totpdf->generate(*allVariables, 100000);
	RooDataSet *toy = (RooDataSet*)totpdf->generate(*allVariables, ntot);
	RooDataSet *toy2 = (RooDataSet*)toy->reduce("PhotonsMass < 140 && PhotonsMass > 110");
//	toy2->plotOn(mgg_frame, LineColor(kBlue));

	cout << "##### RE-FIT SIG+BKG ON TOY DATA #####" << endl;
	cout << "##### FIXING FIT PARAMETERS #####" << endl;
	// fix signal parameters
	RooRealVar *frac_0_cat0 = ws->var("frac_0_cat0");		frac_0_cat0->setConstant();
//	RooRealVar *frac_1_cat0 = ws->var("frac_1_cat0");		frac_1_cat0->setConstant();
	RooRealVar *mu_signal_0_cat0 = ws->var("mu_signal_0_cat0");		mu_signal_0_cat0->setConstant();
	RooRealVar *mu_signal_1_cat0 = ws->var("mu_signal_1_cat0");		mu_signal_1_cat0->setConstant();
//	RooRealVar *mu_signal_2_cat0 = ws->var("mu_signal_2_cat0");		mu_signal_2_cat0->setConstant();
	RooRealVar *sigma_signal_0_cat0 = ws->var("sigma_signal_0_cat0");		sigma_signal_0_cat0->setConstant();
	RooRealVar *sigma_signal_1_cat0 = ws->var("sigma_signal_1_cat0");		sigma_signal_1_cat0->setConstant();
	totpdf->fitTo(*toy, Extended(), Range(110, 140));
	RooRealVar *pol0_cat0 = ws->var("pol0_cat0");		pol0_cat0->setConstant();
	RooRealVar *pol1_cat0 = ws->var("pol1_cat0");		pol1_cat0->setConstant();
	RooRealVar *pol2_cat0 = ws->var("pol2_cat0");		pol2_cat0->setConstant();
	RooRealVar *pol3_cat0 = ws->var("pol3_cat0");		pol3_cat0->setConstant();
	RooRealVar *pol4_cat0 = ws->var("pol4_cat0");		pol4_cat0->setConstant();
//	RooRealVar *sigma_signal_2_cat0 = ws->var("sigma_signal_2_cat0");		sigma_signal_2_cat0->setConstant();
	// first fit of toy data with bkg pdf



	bkgpdf->fitTo(*toy, Extended(), Range(110, 140));
//	bkgpdf->fitTo(*toy2, Extended());
	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << endl;
	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;
	// then fit the total pdf
//	sigpdf->plotOn(mgg_frame, Normalization(hggpdf_cat0_signal_norm->getVal()), LineColor(kGreen));
//	totpdf->fitTo(*toy2, Extended());
	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << endl;
	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << endl;
	totpdf->plotOn(mgg_frame, Components(*bkgpdf), LineColor(kRed));
	totpdf->plotOn(mgg_frame, Components(*sigpdf), LineColor(kPink));
	totpdf->plotOn(mgg_frame);

// now with the splot
// first : set model parameters to constant
//	toy->Print();
//	toy->plotOn(mgg_frame);

//	cout << "##### Preparing SPlot #####" << endl;
//	const RooArgList *liste = new RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm);
//	RooStats::SPlot::SPlot *splot = new RooStats::SPlot::SPlot();
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, sigpdf, *liste);
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, sigpdf, RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm));
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, totpdf, RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm));
////	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, totpdf, RooArgList(*nsig, *nbkg));
//	RooStats::SPlot *splot = new RooStats::SPlot("splot", "splot", *toy, *sigpdf, *liste, RooArgSet(), kTRUE, kFALSE, "");
//RooArgSet& projDeps = RooArgSet(), bool includeWeights = kTRUE, bool copyDataSet = kFALSE, const char* newName = ""
//	cout << "##### Printing out sWeights #####" << endl;
//	cout << "hggpdf_cat0_signal_norm->getVal()= " << hggpdf_cat0_signal_norm->getVal() << "\tsplot->GetYieldFromSWeight(\"hggpdf_cat0_signal_norm\")= " << splot->GetYieldFromSWeight("hggpdf_cat0_signal_norm") << endl;
//	cout << "hggpdf_cat0_background_norm->getVal()= " << hggpdf_cat0_background_norm->getVal() << "\tsplot->GetYieldFromSWeight(\"hggpdf_cat0_background_norm\")= " << splot->GetYieldFromSWeight("hggpdf_cat0_background_norm") << endl;

//	cout << "##### TEST ON REDUCE DATASET #####" << endl;
//	RooStats::SPlot *splot2 = new RooStats::SPlot("splot2", "splot2", *toy2, totpdf, RooArgList(*hggpdf_cat0_background_norm, *hggpdf_cat0_signal_norm));

	cout << "##### CREATE DATASET WITH SIGNAL WEIGHTS #####" << endl;
	RooDataSet *sToy = new RooDataSet(toy->GetName(), toy->GetTitle(), toy, *toy->get(), 0, "hggpdf_cat0_signal_norm_sw"); 
	RooDataSet *sToy2 = new RooDataSet(toy->GetName(), toy->GetTitle(), toy, *toy->get(), 0, "hggpdf_cat0_background_norm_sw"); 


	toy->plotOn(mgg_frame, LineColor(kGreen));
	totpdf->plotOn(mgg_frame);
	mgg_frame->Draw();
	canvas->Print("dump.pdf");	
	sToy->plotOn(mgg_frame_signal, LineColor(kOrange));
	sigpdf->plotOn(mgg_frame_signal);
	mgg_frame_signal->Draw();
	canvas->Print("dump_sg.pdf");	
	sToy2->plotOn(mgg_frame_background, LineColor(kOrange));
	bkgpdf->plotOn(mgg_frame_background);
	mgg_frame_background->Draw();
	canvas->Print("dump_bg.pdf");	
*/
//	delete splot;
//	splot = 0;

	f->Close();
	delete f;
	f = 0;

	delete canvas;
	canvas = 0;
	return 0;
}

