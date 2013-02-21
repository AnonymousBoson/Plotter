// C++ headers
#include <iostream>
#include <vector>
// ROOT headers
#include "TROOT.h"
#include <TSystem.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TStyle.h>
// RooFit headers
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussian.h"
#include "RooBernstein.h"
#include "RooFitResult.h"
#include "RooPlot.h"
// local files
#include "CMSStyle.C"
#include "SampleHandler.h"
// Verbosity
#define DEBUG 0
// namespaces
using namespace std;
using namespace RooFit;

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

	// ##### INITIALIZATION OF PLOT STYLE #####
	gROOT->Reset();
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TCanvas *canvas = new TCanvas();

	// ##### SETUP THE SAMPLES #####
	Sample sig_ggf("ggh_m125_8TeV", "GGF (125 GeV)", -1, 1.0);
  sig_ggf.setFiles("datastore/../kinematics_v01/tree_v11.root");

	vector<Sample> sample_list;
	sample_list.push_back(sig_ggf);

	TClonesArray * chain_sample = new TClonesArray("TChain", sample_list.size() - 1);
	for(int isample = 0 ; isample < (int)sample_list.size() ; isample++)
	{
		new ((*chain_sample)[isample]) TChain(sample_list[isample].getName().c_str());
		((TChain*)chain_sample->At(isample))->Add(sample_list[isample].getFiles().c_str());
	}

	// ##### PREPARE FIT MODELS #####
	// ### SIGNAL ###
	int n = 10;
	TClonesArray mu_signal_0("RooRealVar", n);
	TClonesArray sigma_signal_0("RooRealVar", n);
	TClonesArray gauss_signal_0("RooGaussian", n);
	TClonesArray mu_signal_1("RooRealVar", n);
	TClonesArray sigma_signal_1("RooRealVar", n);
	TClonesArray gauss_signal_1("RooGaussian", n);
	TClonesArray mu_signal_2("RooRealVar", n);
	TClonesArray sigma_signal_2("RooRealVar", n);
	TClonesArray gauss_signal_2("RooGaussian", n);
	TClonesArray frac_0("RooRealVar", n);
	TClonesArray frac_1("RooRealVar", n);
	TClonesArray signal_model_gauss("RooAddPdf", n);
	TClonesArray signal_model("RooExtendPdf", n);
	TClonesArray n_signal("RooRealVar", n);
	TClonesArray signal_dataset("RooDataSet", n);

	// ### SETUP VARIABLES ###
	RooRealVar CMS_hgg_mass("PhotonsMass", "m_{#gamma#gamma}", 100., 160., "GeV");
	int iclass=0;
	new (mu_signal_0[iclass])	RooRealVar(Form("mu_signal_0_cat%i", iclass), "#mu_{0}", 125., 120., 130., "GeV");
    new (sigma_signal_0[iclass])    RooRealVar(Form("sigma_signal_0_cat%i", iclass), "#sigma_{0}", 2.5, 0.1, 4., "GeV");
    new (gauss_signal_0[iclass])    RooGaussian(Form("gauss_signal_0_cat%i", iclass), Form("gauss_signal_0_cat%i", iclass), CMS_hgg_mass, *(RooAbsReal*)mu_signal_0.At(iclass), *(RooAbsReal*)sigma_signal_0.At(iclass));
    new (mu_signal_1[iclass])       RooRealVar(Form("mu_signal_1_cat%i", iclass), "#mu_{1}", 124., 120., 130., "GeV");
    new (sigma_signal_1[iclass])    RooRealVar(Form("sigma_signal_1_cat%i", iclass), "#sigma_{1}", 4., 1.0, 7., "GeV");
    new (gauss_signal_1[iclass])    RooGaussian(Form("gauss_signal_1_cat%i", iclass), Form("gauss_signal_1_cat%i", iclass), CMS_hgg_mass, *(RooAbsReal*)mu_signal_1.At(iclass), *(RooAbsReal*)sigma_signal_1.At(iclass));
    new (mu_signal_2[iclass])       RooRealVar(Form("mu_signal_2_cat%i", iclass), "#mu_{2}", 120., 100., 160., "GeV");
    new (sigma_signal_2[iclass])    RooRealVar(Form("sigma_signal_2_cat%i", iclass), "#sigma_{2}", 20., 5., 50., "GeV");
    new (gauss_signal_2[iclass])    RooGaussian(Form("gauss_signal_2_cat%i", iclass), Form("gauss_signal_2_cat%i", iclass), CMS_hgg_mass, *(RooAbsReal*)mu_signal_2.At(iclass), *(RooAbsReal*)sigma_signal_2.At(iclass));
    new (frac_0[iclass])            RooRealVar(Form("frac_0_cat%i", iclass), "frac_{0}", .5, 0.001, 0.999);
    new (frac_1[iclass])            RooRealVar(Form("frac_1_cat%i", iclass), "frac_{1}", .3, 0.001, 0.999);
    new (signal_model_gauss[iclass])      RooAddPdf(Form("gauss_signal_class_cat%i", iclass), Form("gauss_signal_class_cat%i", iclass), RooArgList(*(RooGaussian*)gauss_signal_0.At(iclass), *(RooGaussian*)gauss_signal_1.At(iclass), *(RooGaussian*)gauss_signal_2.At(iclass)), RooArgList(*(RooRealVar*)frac_0.At(iclass), *(RooRealVar*)frac_1.At(iclass)), kFALSE);
//    new (signal_model_gauss[iclass])      RooAddPdf(Form("gauss_signal_class_cat%i", iclass), Form("gauss_signal_class_cat%i", iclass), RooArgList(*(RooGaussian*)gauss_signal_0.At(iclass), *(RooGaussian*)gauss_signal_1.At(iclass)), RooArgList(*(RooRealVar*)frac_0.At(iclass)), kFALSE);
    new(n_signal[iclass])           RooRealVar(Form("hggpdf_cat%i_signal_norm", iclass), "N_{0}", 20., 0., 200., "events");
    new(signal_model[iclass])       RooExtendPdf(Form("model_signal_class_cat%i", iclass), Form("model_signal_class_cat%i", iclass), *(RooAddPdf*)signal_model_gauss.At(iclass), *(RooRealVar*)n_signal.At(iclass));

	RooDataSet *signal = new RooDataSet("signal", "signal", ((TChain*)chain_sample->At(0)), RooArgList(CMS_hgg_mass));

	new (signal_dataset[iclass])		RooDataSet(Form("signal_dataset_cat%i", iclass), Form("signal_dataset_cat%i", iclass), signal, RooArgSet(CMS_hgg_mass));
	((RooDataSet*)signal_dataset.At(iclass))->SetName(Form("signal_dataset_cat%i", iclass));
	RooFitResult *result_signal = ((RooAbsPdf*)signal_model.At(iclass))->fitTo(*(RooDataSet*)signal_dataset.At(iclass), Save(), SumW2Error(kTRUE));
	RooPlot *mgg_frame_signal = CMS_hgg_mass.frame(Title("signal"));
    ((RooDataSet*)signal_dataset.At(iclass))->plotOn(mgg_frame_signal, DataError(RooAbsData::SumW2));
    ((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_0_cat%i", iclass)), LineStyle(kDashed), LineColor(kGreen), LineWidth(2));
    ((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_1_cat%i", iclass)), LineStyle(kDashed), LineColor(kBlue)), LineWidth(2);
    ((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_2_cat%i", iclass)), LineStyle(kDashed), LineColor(kCyan), LineWidth(2));
    ((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, LineColor(kRed), LineWidth(2));
    mgg_frame_signal->Draw();
    RooArgList param_signal = result_signal->floatParsFinal();

	canvas->Print("dump.pdf");

	return 0;
}

