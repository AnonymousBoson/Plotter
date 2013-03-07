// C++ headers
//#include <iostream>
//#include <vector>
// ROOT headers
#include "TROOT.h"
#include <TSystem.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TStyle.h>
// RooFit headers
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussian.h"
#include "RooBernstein.h"
#include "RooFitResult.h"
#include "RooPlot.h"
// RooStat headers
#include "RooWorkspace.h"
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
	string wspaceName = "WS_" + filename + ".root";


	// ##### INITIALIZATION OF PLOT STYLE #####
	gROOT->Reset();
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	TCanvas *canvas = new TCanvas();

	// ##### SETUP THE SAMPLES #####
/*
	Sample sig_ggf("ggh_m125_8TeV", "GGF (125 GeV)", -1, 1.0);
  sig_ggf.setFiles("datastore/../kinematics_v01/tree_v11.root");

	Sample bkg_diphojet_8TeV("diphojet_8TeV", "#gamma#gamma + jets", 1, 1.0);
	bkg_diphojet_8TeV.setFiles("datastore/tree_v15.root");
*/
// mh= 120GeV

	Sample sig_ggh_120("ggh_m120_8TeV", "ggH (120 GeV)", -1, 1.0);
	sig_ggh_120.setFiles("datastore/tree_v12.root");
	sig_ggh_120.setStyle(kMagenta, 3, 3004, "");
	sig_ggh_120.setXSection((21.13 * 2.28 * 0.001));
	sig_ggh_120.setInitialNumberOfEvents(69036.0);
	sig_ggh_120.setSpecificWeights("manual");
	sig_ggh_120.setStackGroup("SM Higgs (120GeV)");

	Sample sig_vbf_120("vbf_m120_8TeV", "VBF (120 GeV)", -1, 1.0);
	sig_vbf_120.setFiles("datastore/tree_v12.root");
	sig_vbf_120.setStyle(kRed+1, 3, 3004, "");
	sig_vbf_120.setXSection((1.649 * 2.28 * 0.001));
	sig_vbf_120.setInitialNumberOfEvents(79784.0);
	sig_vbf_120.setSpecificWeights("manual");
	sig_vbf_120.setStackGroup("SM Higgs (120GeV)");

	Sample sig_wzh_120("wzh_m120_8TeV", "WZH (120 GeV)", -1, 1.0);
	sig_wzh_120.setFiles("datastore/tree_v12.root");
	sig_wzh_120.setStyle(kRed+2, 3, 3004, "");
	sig_wzh_120.setXSection(((0.7966 + 0.4483) * 2.28 * 0.001));
	sig_wzh_120.setInitialNumberOfEvents(69036.0);
	sig_wzh_120.setSpecificWeights("manual");
	sig_wzh_120.setStackGroup("SM Higgs (120GeV)");

	Sample sig_tth_120("tth_m120_8TeV", "WZH (120 GeV)", -1, 1.0);
	sig_tth_120.setFiles("datastore/tree_v12.root");
	sig_tth_120.setStyle(kRed+2, 3, 3004, "");
	sig_tth_120.setXSection((0.1470 * 2.28 * 0.001));
	sig_tth_120.setInitialNumberOfEvents(69036.0);
	sig_tth_120.setSpecificWeights("manual");
	sig_tth_120.setStackGroup("SM Higgs (120GeV)");

// mh= 125GeV
	Sample sig_ggh_125("ggh_m125_8TeV", "ggH (125 GeV)", -1, 1.0);
	sig_ggh_125.setFiles("datastore/tree_v11.root");
	sig_ggh_125.setStyle(kRed, 3, 3005, "");
	sig_ggh_125.setXSection((19.52 * 2.28 * 0.001));
	sig_ggh_125.setInitialNumberOfEvents(69036.0);
	sig_ggh_125.setSpecificWeights("manual");
	sig_ggh_125.setStackGroup("SM Higgs (125GeV)");

	Sample sig_vbf_125("vbf_m125_8TeV", "VBF (125 GeV)", -1, 1.0);
	sig_vbf_125.setFiles("datastore/tree_v11.root");
	sig_vbf_125.setStyle(kRed+1, 3, 3004, "");
	sig_vbf_125.setXSection((1.578 * 2.28 * 0.001));
	sig_vbf_125.setInitialNumberOfEvents(79784.0);
	sig_vbf_125.setSpecificWeights("manual");
	sig_vbf_125.setStackGroup("SM Higgs (125GeV)");

	Sample sig_wzh_125("wzh_m125_8TeV", "WZH (125 GeV)", -1, 1.0);
	sig_wzh_125.setFiles("datastore/tree_v11.root");
	sig_wzh_125.setStyle(kRed+2, 3, 3004, "");
	sig_wzh_125.setXSection(((0.6966 + 0.3943) * 2.28 * 0.001));
	sig_wzh_125.setInitialNumberOfEvents(69036.0);
	sig_wzh_125.setSpecificWeights("manual");
	sig_wzh_125.setStackGroup("SM Higgs (125GeV)");

	Sample sig_tth_125("tth_m125_8TeV", "WZH (125 GeV)", -1, 1.0);
	sig_tth_125.setFiles("datastore/tree_v11.root");
	sig_tth_125.setStyle(kRed+2, 3, 3004, "");
	sig_tth_125.setXSection((0.1302 * 2.28 * 0.001));
	sig_tth_125.setInitialNumberOfEvents(69036.0);
	sig_tth_125.setSpecificWeights("manual");
	sig_tth_125.setStackGroup("SM Higgs (125GeV)");

// mh= 130GeV
	Sample sig_ggh_130("ggh_m130_8TeV", "ggH (130 GeV)", -1, 1.0);
	sig_ggh_130.setFiles("datastore/tree_v10.root");
	sig_ggh_130.setStyle(kBlue, 3, 3006, "");
	sig_ggh_130.setXSection((18.07 * 2.28 * 0.001));
	sig_ggh_130.setInitialNumberOfEvents(69036.0);
	sig_ggh_130.setSpecificWeights("manual");
	sig_ggh_130.setStackGroup("SM Higgs (130GeV)");

	Sample sig_vbf_130("vbf_m130_8TeV", "VBF (130 GeV)", -1, 1.0);
	sig_vbf_130.setFiles("datastore/tree_v10.root");
	sig_vbf_130.setStyle(kRed+1, 3, 3004, "");
	sig_vbf_130.setXSection((1.511 * 2.28 * 0.001));
	sig_vbf_130.setInitialNumberOfEvents(79784.0);
	sig_vbf_130.setSpecificWeights("manual");
	sig_vbf_130.setStackGroup("SM Higgs (130GeV)");

	Sample sig_wzh_130("wzh_m130_8TeV", "WZH (130 GeV)", -1, 1.0);
	sig_wzh_130.setFiles("datastore/tree_v10.root");
	sig_wzh_130.setStyle(kRed+2, 3, 3004, "");
	sig_wzh_130.setXSection(((0.6095 + 0.3473) * 2.28 * 0.001));
	sig_wzh_130.setInitialNumberOfEvents(69036.0);
	sig_wzh_130.setSpecificWeights("manual");
	sig_wzh_130.setStackGroup("SM Higgs (130GeV)");

	Sample sig_tth_130("tth_m130_8TeV", "WZH (130 GeV)", -1, 1.0);
	sig_tth_130.setFiles("datastore/tree_v10.root");
	sig_tth_130.setStyle(kRed+2, 3, 3004, "");
	sig_tth_130.setXSection((0.1157 * 2.28 * 0.001));
	sig_tth_130.setInitialNumberOfEvents(69036.0);
	sig_tth_130.setSpecificWeights("manual");
	sig_tth_130.setStackGroup("SM Higgs (130GeV)");

	// backgrounds
	Sample bkg_qcd_30_8TeV_ff("qcd_30_8TeV_ff", "QCD", 1, 1.0);
	bkg_qcd_30_8TeV_ff.setFiles("datastore/tree_v13.root");
	bkg_qcd_30_8TeV_ff.setStyle(kSpring-9, 1, 3001, "");
	bkg_qcd_30_8TeV_ff.setSpecificWeights("evweight");
	bkg_qcd_30_8TeV_ff.setSpecificCuts("evweight < 100");
	bkg_qcd_30_8TeV_ff.setStackGroup("ff");
	bkg_qcd_30_8TeV_ff.setSuperStackGroup("Background");

	Sample bkg_qcd_40_8TeV_ff("qcd_40_8TeV_ff", "QCD", 1, 1.0);
	bkg_qcd_40_8TeV_ff.setFiles("datastore/tree_v13.root");
	bkg_qcd_40_8TeV_ff.setStyle(kSpring-9, 1, 3001, "");
	bkg_qcd_40_8TeV_ff.setSpecificWeights("evweight");
	bkg_qcd_40_8TeV_ff.setSpecificCuts("evweight < 100");
	bkg_qcd_40_8TeV_ff.setStackGroup("ff");
	bkg_qcd_40_8TeV_ff.setSuperStackGroup("Background");

	Sample bkg_qcd_30_8TeV_pf("qcd_30_8TeV_pf", "QCD", 1, 1.0);
	bkg_qcd_30_8TeV_pf.setFiles("datastore/tree_v13.root");
	bkg_qcd_30_8TeV_pf.setStyle(kAzure+1, 1, 3001, "");
	bkg_qcd_30_8TeV_pf.setSpecificWeights("evweight");
	bkg_qcd_30_8TeV_pf.setSpecificCuts("evweight < 100");
	bkg_qcd_30_8TeV_pf.setStackGroup("pf");
	bkg_qcd_30_8TeV_pf.setSuperStackGroup("Background");

	Sample bkg_qcd_40_8TeV_pf("qcd_40_8TeV_pf", "QCD", 1, 1.0);
	bkg_qcd_40_8TeV_pf.setFiles("datastore/tree_v13.root");
	bkg_qcd_40_8TeV_pf.setStyle(kAzure+1, 1, 3001, "");
	bkg_qcd_40_8TeV_pf.setSpecificWeights("evweight");
	bkg_qcd_40_8TeV_pf.setSpecificCuts("evweight < 100");
	bkg_qcd_40_8TeV_pf.setStackGroup("pf");
	bkg_qcd_40_8TeV_pf.setSuperStackGroup("Background");

	Sample bkg_gjet_20_8TeV_pf("gjet_20_8TeV_pf", "#gamma + jets", 1, 1.0);
	bkg_gjet_20_8TeV_pf.setFiles("datastore/tree_v14.root");
	bkg_gjet_20_8TeV_pf.setStyle(kAzure+1, 1, 3001, "");
	bkg_gjet_20_8TeV_pf.setSpecificWeights("evweight");
	bkg_gjet_20_8TeV_pf.setStackGroup("pf");
	bkg_gjet_20_8TeV_pf.setSuperStackGroup("Background");

	Sample bkg_gjet_40_8TeV_pf("gjet_40_8TeV_pf", "#gamma + jets", 1, 1.0);
	bkg_gjet_40_8TeV_pf.setFiles("datastore/tree_v14.root");
	bkg_gjet_40_8TeV_pf.setStyle(kAzure+1, 1, 3001, "");
	bkg_gjet_40_8TeV_pf.setSpecificWeights("evweight");
	bkg_gjet_40_8TeV_pf.setStackGroup("pf");
	bkg_gjet_40_8TeV_pf.setSuperStackGroup("Background");

	Sample bkg_gjet_20_8TeV_pp("gjet_20_8TeV_pp", "#gamma + jets", 1, 1.0);
	bkg_gjet_20_8TeV_pp.setFiles("datastore/tree_v14.root");
	bkg_gjet_20_8TeV_pp.setStyle(kGreen+2, 1, 3001, "");
	bkg_gjet_20_8TeV_pp.setSpecificWeights("evweight");
	bkg_gjet_20_8TeV_pp.setStackGroup("pp");
	bkg_gjet_20_8TeV_pp.setSuperStackGroup("Background");

	Sample bkg_gjet_40_8TeV_pp("gjet_40_8TeV_pp", "#gamma + jets", 1, 1.0);
	bkg_gjet_40_8TeV_pp.setFiles("datastore/tree_v14.root");
	bkg_gjet_40_8TeV_pp.setStyle(kGreen+2, 1, 3001, "");
	bkg_gjet_40_8TeV_pp.setSpecificWeights("evweight");
	bkg_gjet_40_8TeV_pp.setStackGroup("pp");
	bkg_gjet_40_8TeV_pp.setSuperStackGroup("Background");

	Sample bkg_diphojet_8TeV("diphojet_8TeV", "#gamma#gamma + jets", 1, 1.0);
	bkg_diphojet_8TeV.setFiles("datastore/tree_v15.root");
	bkg_diphojet_8TeV.setStyle(kGreen+2, 1, 3001, "");
	bkg_diphojet_8TeV.setSpecificWeights("evweight");
	bkg_diphojet_8TeV.setStackGroup("pp");
	bkg_diphojet_8TeV.setSuperStackGroup("Background");

	Sample bkg_dipho_Box_25_8TeV("dipho_Box_25_8TeV", "#gamma#gamma + jets (Box)", 1, 1.0);
	bkg_dipho_Box_25_8TeV.setFiles("datastore/tree_v15.root");
	bkg_dipho_Box_25_8TeV.setStyle(kGreen+2, 1, 3001, "");
	bkg_dipho_Box_25_8TeV.setSpecificWeights("evweight");
	bkg_dipho_Box_25_8TeV.setStackGroup("pp");
	bkg_dipho_Box_25_8TeV.setSuperStackGroup("Background");

	Sample bkg_dipho_Box_250_8TeV("dipho_Box_250_8TeV", "#gamma + jets", 1, 1.0);
	bkg_dipho_Box_250_8TeV.setFiles("datastore/tree_v15.root");
	bkg_dipho_Box_250_8TeV.setStyle(kGreen+2, 1, 3001, "");
	bkg_dipho_Box_250_8TeV.setSpecificWeights("evweight");
	bkg_dipho_Box_250_8TeV.setStackGroup("pp");
	bkg_dipho_Box_250_8TeV.setSuperStackGroup("Background");

	Sample bkg_DYJetsToLL("DYJetsToLL", "Drell-Yan", 1, 1.0);
	bkg_DYJetsToLL.setFiles("datastore/tree_v15.root");
	bkg_DYJetsToLL.setStyle(kViolet+1, 1, 3001, "");
	bkg_DYJetsToLL.setSpecificWeights("evweight");
	bkg_DYJetsToLL.setStackGroup("DY");
	bkg_DYJetsToLL.setSuperStackGroup("Background");

	vector<Sample> sample_list;
	sample_list.push_back(sig_ggh_125);
	sample_list.push_back(sig_vbf_125);
	sample_list.push_back(sig_wzh_125);
	sample_list.push_back(sig_tth_125);
	sample_list.push_back(bkg_diphojet_8TeV);


	TClonesArray * chain_sample = new TClonesArray("TChain", sample_list.size() - 1);
	for(int isample = 0 ; isample < (int)sample_list.size() ; isample++)
	{
		new ((*chain_sample)[isample]) TChain(sample_list[isample].getName().c_str());
		((TChain*)chain_sample->At(isample))->Add(sample_list[isample].getFiles().c_str());
	}

	// Creating RooDataSet per stack group
	vector<string> stackGroups;
	vector<vector<int> > stackSamples;
	stackGroups.clear();
	stackSamples.clear();
	getStackGroups(sample_list, stackGroups, stackSamples);

	cout << endl << endl << endl << endl;
	cout << "stackGroups.size()= " << stackGroups.size() << "\t\tstackSamples.size()= " << stackSamples.size() << endl;
	for(int is = 0 ; is < (int)stackGroups.size() ; is++)
	{
		cout << "stackGroups[" << is << "]= " << stackGroups[is] << endl;
		for(int js = 0 ; js < (int)stackSamples[is].size() ; js++)
			cout << "\tstackSamples[" << is << "][" << js << "]= " << stackSamples[is][js] << "\tname= " << sample_list[stackSamples[is][js]].getName() << endl;
	}
	cout << endl << endl << endl << endl;

/*
	for(int isample = 0 ; isample < chain_sample->GetEntriesFast() ; isample++)
  {
    string stack = sample_list[isample].getStackGroup();
    bool stackAlreadyProcessed = false;
    for(int istack = 0 ; istack < (int)stackGroups.size() ; istack++)
    { // check if this stack group has already been processed
      if( (stack == stackGroups[istack])  && (stack != "") )
      {
        stackAlreadyProcessed = true;
        continue;
      }
    }
    if( (sample_list[isample].getStackGroup() != "") && !stackAlreadyProcessed )
    { // if the sample is to be stack, look for similar samples it is to be stacked with
      stackGroups.push_back(sample_list[isample].getStackGroup());
      vector<int> samples;
      samples.clear();
      samples.push_back(isample);
      for(int jsample = isample+1 ; jsample < chain_sample->GetEntriesFast() ; jsample++)
      {
        if( sample_list[isample].getStackGroup() == sample_list[jsample].getStackGroup() )
          samples.push_back(jsample);
      }
      stackSamples.push_back(samples);
    } else if(sample_list[isample].getStackGroup() == "") {
      stackGroups.push_back(sample_list[isample].getDisplayName());
      vector<int> samples;
      samples.clear();
      samples.push_back(isample);
      stackSamples.push_back(samples);
    }
  }
*/
	// ##### PREPARE FIT MODELS #####
	string cuts = "category == 0";
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
	// ### BACKGROUND ###
	TClonesArray pol0("RooRealVar", n);
	TClonesArray pol1("RooRealVar", n);
	TClonesArray pol2("RooRealVar", n);
	TClonesArray pol3("RooRealVar", n);
	TClonesArray pol4("RooRealVar", n);
	TClonesArray pol5("RooRealVar", n);
	TClonesArray background_model_bernstein("RooBernstein", n);
	TClonesArray background_model("RooExtendPdf", n);
	TClonesArray n_background("RooRealVar", n);
	TClonesArray background_dataset("RooDataSet", n);	

	// ### SETUP VARIABLES AND INITIALIZE FIT PARAMETERS ###
	RooRealVar CMS_hgg_mass("PhotonsMass", "m_{#gamma#gamma}", 100., 180., "GeV");
	RooRealVar dipho_E("dipho_E", "E^{#gammagamma}", 0., 200., "GeV");
	RooRealVar dipho_pt("dipho_pt", "p_{T}^{#gammagamma}", 0., 200., "GeV");
	RooRealVar dipho_eta("dipho_eta", "#eta^{#gammagamma}", -5., 5., "GeV");
	RooRealVar dipho_phi("dipho_phi", "#phi^{#gammagamma}", -3.16, 3.16, "GeV");
	RooRealVar dipho_cosThetaStar_CS("dipho_cosThetaStar_CS", "|cos(#theta^{*})|", 0., 1., "GeV");
	RooRealVar dipho_tanhYStar("dipho_tanhYStar", "|tanh(Y^{*})|", 0., 1., "GeV");
	RooRealVar dipho_Y("dipho_Y", "Y^{#gammagamma}", -10., 10., "GeV");
	RooRealVar category("category", "category", 0, 20);
	RooRealVar evweight("evweight", "evweight", 0, 100);
	RooRealVar pu_weight("pu_weight", "pu_weight", 0, 100);
	RooArgSet *allVariables = new RooArgSet();
	allVariables->add(CMS_hgg_mass);
	allVariables->add(dipho_E);
	allVariables->add(dipho_pt);
	allVariables->add(dipho_eta);
	allVariables->add(dipho_phi);
	allVariables->add(dipho_cosThetaStar_CS);
	allVariables->add(dipho_tanhYStar);
	allVariables->add(dipho_Y);
	allVariables->add(category);
	allVariables->add(evweight);
	allVariables->add(pu_weight);

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
//	new (signal_model_gauss[iclass])      RooAddPdf(Form("gauss_signal_class_cat%i", iclass), Form("gauss_signal_class_cat%i", iclass), RooArgList(*(RooGaussian*)gauss_signal_0.At(iclass), *(RooGaussian*)gauss_signal_1.At(iclass)), RooArgList(*(RooRealVar*)frac_0.At(iclass)), kFALSE);
	new(n_signal[iclass])           RooRealVar(Form("hggpdf_cat%i_signal_norm", iclass), "N_{0}", 20., 0., 500., "events");
	new(signal_model[iclass])       RooExtendPdf(Form("model_signal_class_cat%i", iclass), Form("model_signal_class_cat%i", iclass), *(RooAddPdf*)signal_model_gauss.At(iclass), *(RooRealVar*)n_signal.At(iclass));
	new (pol0[iclass])              RooRealVar(Form("pol0_cat%i", iclass), "b_{0}", 0.0001, 0., 1.);
	new (pol1[iclass])              RooRealVar(Form("pol1_cat%i", iclass), "b_{1}", 0.0001, 0., 1.);
	new (pol2[iclass])              RooRealVar(Form("pol2_cat%i", iclass), "b_{2}", 0.0001, 0., 1.);
	new (pol3[iclass])              RooRealVar(Form("pol3_cat%i", iclass), "b_{3}", 0.0001, 0., 1.);
	new (pol4[iclass])              RooRealVar(Form("pol4_cat%i", iclass), "b_{4}", 0.0001, 0., 1.);
	new (pol5[iclass])              RooRealVar(Form("pol5_cat%i", iclass), "b_{5}", 0.0001, 0., 1.);
	new (n_background[iclass])      RooRealVar(Form("hggpdf_cat%i_background_norm", iclass), "N_{0}", 1000., 0., 1000000000., "events");
	new (background_model_bernstein[iclass])  RooBernstein(Form("model_background_bernstein_class_%i", iclass), Form("model_background_bernstein_class_%i", iclass), CMS_hgg_mass, RooArgList(*(RooRealVar*)pol0.At(iclass), *(RooRealVar*)pol1.At(iclass), *(RooRealVar*)pol2.At(iclass), *(RooRealVar*)pol3.At(iclass), *(RooRealVar*)pol4.At(iclass)));
	new (background_model[iclass])  RooExtendPdf(Form("model_background_class_cat%i", iclass), Form("model_background_class_cat%i", iclass), *(RooBernstein*)background_model_bernstein.At(iclass), *(RooRealVar*)n_background.At(iclass));

	// ##### PREPARING ROODATASETS #####
	RooDataSet *unw_signal = new RooDataSet("signal", "signal", ((TChain*)chain_sample->At(0)), *allVariables);
	RooFormulaVar wSignalFunc("wS", "event weight", "pu_weight * 19.52 * 2.28 * 0.001 * 19620.0 / 69036.0 * 1.0", pu_weight);
	RooRealVar* wSignal = (RooRealVar*) unw_signal->addColumn(wSignalFunc);
	RooDataSet *signal = new RooDataSet(unw_signal->GetName(), unw_signal->GetTitle(), unw_signal, *unw_signal->get(), 0, wSignal->GetName());
	cout << "##### signal->isWeighted()= " << signal->isWeighted() << endl;
	RooDataSet *unw_background = new RooDataSet("background", "background", ((TChain*)chain_sample->At(1)), *allVariables);
	RooFormulaVar wBackgroundFunc("wB", "event weight", "evweight * pu_weight", RooArgList(evweight, pu_weight));
	RooRealVar* wBackground = (RooRealVar*) unw_background->addColumn(wBackgroundFunc);
	RooDataSet *background = new RooDataSet(unw_background->GetName(), unw_background->GetTitle(), unw_background, *unw_background->get(), 0, wBackground->GetName());
//		RooDataSet *background = new RooDataSet("background", "background", ((TChain*)chain_sample->At(1)), RooArgList(CMS_hgg_mass, category, evweight, pu_weight), "", "");
	cout << "##### background->isWeighted()= " << background->isWeighted() << endl;


/*
// Construct formula to calculate (fake) weight for events
  RooFormulaVar wFunc("w","event weight","(x*x+10)",x) ;
  // Add column with variable w to previously generated dataset
  RooRealVar* w = (RooRealVar*) data->addColumn(wFunc) ;
  // Instruct dataset wdata in interpret w as event weight rather than as observable
  RooDataSet wdata(data->GetName(),data->GetTitle(),data,*data->get(),0,w->GetName()) ;

	TClonesArray pof("RooRealVar", 10);
	new (pof[0]) RooRealVar();

	TClonesArray paf("RooDataSet", 10);
	new (paf[0]) RooDataSet();
*/


	TClonesArray signal_dataset("RooDataSet", n);
	new (signal_dataset[iclass])		RooDataSet(Form("signal_dataset_cat%i", iclass), Form("signal_dataset_cat%i", iclass), signal, RooArgSet(CMS_hgg_mass, category, *wSignal), Form("category == %i", iclass), wSignal->GetName());
	new (background_dataset[iclass])		RooDataSet(Form("background_dataset_cat%i", iclass), Form("background_dataset_cat%i", iclass), background, RooArgSet(CMS_hgg_mass, category, *wBackground), Form("category == %i", iclass), wBackground->GetName());
//	new (signal_dataset[iclass])		(RooDataSet)(RooDataSet());
//	new (background_dataset[iclass])		RooDataSet();
//	new (signal_dataset[0])		RooDataSet();
//	new (background_dataset[0])		RooDataSet();
	((RooDataSet*)signal_dataset.At(iclass))->SetName(Form("signal_dataset_cat%i", iclass));
	((RooDataSet*)background_dataset.At(iclass))->SetName(Form("background_dataset_cat%i", iclass));

	// ##### FIT #####
	cout << "##### (RooDataSet*)signal_dataset.At(iclass)->isWeighted= " << ((RooDataSet*)signal_dataset.At(iclass))->isWeighted() << endl;
	cout << "##### (RooDataSet*)background_dataset.At(iclass)->isWeighted= " << ((RooDataSet*)background_dataset.At(iclass))->isWeighted() << endl;
	RooFitResult *result_signal = ((RooAbsPdf*)signal_model.At(iclass))->fitTo(*(RooDataSet*)signal_dataset.At(iclass), Save(), SumW2Error(kTRUE));
	RooFitResult *result_background = ((RooAbsPdf*)background_model.At(iclass))->fitTo(*(RooDataSet*)background_dataset.At(iclass), Save(), SumW2Error(kTRUE));

	// ##### PLOT THE FIT #####
	// ### SIGNAL
	RooPlot *mgg_frame_signal = CMS_hgg_mass.frame(Title("signal"));
	((RooDataSet*)signal_dataset.At(iclass))->plotOn(mgg_frame_signal, DataError(RooAbsData::SumW2));
	((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_0_cat%i", iclass)), LineStyle(kDashed), LineColor(kGreen), LineWidth(2));
	((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_1_cat%i", iclass)), LineStyle(kDashed), LineColor(kBlue)), LineWidth(2);
	((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, Components(Form("gauss_signal_2_cat%i", iclass)), LineStyle(kDashed), LineColor(kCyan), LineWidth(2));
	((RooAbsPdf*)signal_model.At(iclass))->plotOn(mgg_frame_signal, LineColor(kRed), LineWidth(2));
	mgg_frame_signal->Draw();
	RooArgList param_signal = result_signal->floatParsFinal();
	canvas->Print("dump_signal.pdf");
	canvas->Clear();
	// ### BACKGROUND
	RooPlot *mgg_frame_background = CMS_hgg_mass.frame(Title("background"));
	((RooDataSet*)background_dataset.At(iclass))->plotOn(mgg_frame_background, DataError(RooAbsData::SumW2));
	((RooAbsPdf*)background_model.At(iclass))->plotOn(mgg_frame_background, LineColor(kRed), LineWidth(2));
	mgg_frame_background->Draw();
	RooArgList param_background = result_background->floatParsFinal();
	canvas->Print("dump_background.pdf");
	canvas->Clear();

	// ##### SAVE STUFF INTO A ROOWORKSPACE #####
	RooWorkspace *myWS = new RooWorkspace("cms_hgg_workspace");
	// ### SAVING SPECTATOR AND DISCRIMINANT VARIABLES
	myWS->import(*allVariables);

/*
	myWS->import(PhotonsMass);
	myWS->import(dipho_E);
	myWS->import(dipho_pt);
	myWS->import(dipho_eta);
	myWS->import(dipho_phi);
	myWS->import(dipho_cosThetaStar_CS);
	myWS->import(dipho_tanhYStar);
	myWS->import(dipho_Y);
*/

	// ### SAVING BACKGROUND
	myWS->import(*(RooAbsPdf*)background_model.At(iclass));
	// ### SAVING SIGNAL
	myWS->import(*(RooAbsPdf*)signal_model.At(iclass));
	// ### SAVING (PSEUDO-)DATA
	// FIXME
	// ### WRITING FILE
	myWS->writeToFile(wspaceName.c_str());

	cout << "((RooRealVar*)n_signal.At(0))->getVal()= " << ((RooRealVar*)n_signal.At(0))->getVal() << endl;
	cout << "((RooRealVar*)n_background.At(0))->getVal()= " << ((RooRealVar*)n_background.At(0))->getVal() << endl;

	return 0;
}

