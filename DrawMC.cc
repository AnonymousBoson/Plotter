// C++ headers
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
// ROOT headers
#include "TROOT.h"
#include <TChain.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TClonesArray.h>
#include <TGaxis.h>
#include <TError.h>
// local files
#include "CMSStyle.C"
#include "SampleHandler.h"
// Verbosity
#define DEBUG 0
// namespaces
using namespace std;

// **************************************************************************************************************************
void DrawMCPlot(TClonesArray* chain_sample, vector<Sample> sample_list, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi);

// **************************************************************************************************************************
int main()
{
	cout << "##### Drawing macro #####" << endl;
	cout << "##### Initialization #####" << endl;
	gErrorIgnoreLevel = kWarning;
	gROOT->Reset();
	gROOT->ProcessLine(".x setTDRStyle.C");
	TGaxis::SetMaxDigits(3);
	vector<Sample> sample_list;

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


// prodXsection@125GeV
//{'vbf_m120_8TeV': 1.649 * 2.23 10-3, 'vbf_m125_8TeV': 1.578 * 2.28 10-3, 'ggh_m125_8TeV': 19.52 * 2.28 10-3}
// number of initial events
//{'vbf_m120_8TeV': 79376.0, 'diphojet_8TeV': 639312.0, 'vbf_m125_8TeV': 79784.0, 'ggh_m125_8TeV': 69036.0}

	sample_list.push_back(bkg_DYJetsToLL);
	sample_list.push_back(bkg_qcd_30_8TeV_ff);
	sample_list.push_back(bkg_qcd_40_8TeV_ff);
	sample_list.push_back(bkg_qcd_30_8TeV_pf);
	sample_list.push_back(bkg_qcd_40_8TeV_pf);
	sample_list.push_back(bkg_gjet_20_8TeV_pf);
	sample_list.push_back(bkg_gjet_40_8TeV_pf);
	sample_list.push_back(bkg_gjet_20_8TeV_pp);
	sample_list.push_back(bkg_gjet_40_8TeV_pp);
	sample_list.push_back(bkg_diphojet_8TeV);
	sample_list.push_back(bkg_dipho_Box_25_8TeV);
	sample_list.push_back(bkg_dipho_Box_250_8TeV);
/*
	sample_list.push_back(sig_tth_120);
	sample_list.push_back(sig_wzh_120);
	sample_list.push_back(sig_vbf_120);
	sample_list.push_back(sig_ggh_120);
*/
//	sample_list.push_back(sig_tth_125);
//	sample_list.push_back(sig_wzh_125);
//	sample_list.push_back(sig_vbf_125);
	sample_list.push_back(sig_ggh_125);
/*
	sample_list.push_back(sig_tth_130);
	sample_list.push_back(sig_wzh_130);
	sample_list.push_back(sig_vbf_130);
	sample_list.push_back(sig_ggh_130);
*/

	TClonesArray * chain_sample = new TClonesArray("TChain", sample_list.size() - 1);
	for(unsigned int isample = 0; isample < sample_list.size() ; isample++)
	{
		new ((*chain_sample)[isample])	TChain(sample_list[isample].getName().c_str());
		((TChain*)chain_sample->At(isample))->Add(sample_list[isample].getFiles().c_str());
	}

	TCanvas *canvas = new TCanvas();

	cout << "##### DRAW #####" << endl;
	double integratedLumi = 19620.0;
//	double integratedLumi = -1.0;
	vector<double> lumi;
	lumi.clear();
	lumi.push_back(-1.0);
	lumi.push_back(19620.0);
	vector<string> cuts;
	cuts.clear();
	vector<string> cutName;
	cutName.clear();
	vector<string> cutflow;
	cutflow.clear();
	vector<string> cutflowName;
	cutflowName.clear();
	string generic_cut = "PhotonsMass < 180 && PhotonsMass > 100";
	string tempString;
	cutflow.push_back("1.0");
	cutflowName.push_back("");
	cutflow.push_back("dipho_pt < 20.");
	cutflowName.push_back("-diphoPtLT20");
	cutflow.push_back("dipho_pt < 20. && dipho_cosThetaStar_CS > .8");
	cutflowName.push_back("-diphoPtLT20-cosThetaStarGTp8");
	cutflow.push_back("dipho_pt < 20. && dipho_cosThetaStar_CS > .8 && (dipho_Y > 2 || dipho_Y < 2)");
	cutflowName.push_back("-diphoPtLT20-cosThetaStarGTp8-diphoYGT2");

	for(int iflow = 0 ; iflow < (int)cutflow.size() ; iflow++)
	{
		for(int iphotonID = 0 ; iphotonID < 14 ; iphotonID++)
		{
			for(int icat = 0 ; icat < 1 ; icat++)
//			for(int icat = 0 ; icat < 4 ; icat++)
			{
				tempString = Form("category == %i && ph1_ciclevel >= %i && ph2_ciclevel >= %i", icat, iphotonID, iphotonID);
				tempString += " && " + generic_cut + " && " + cutflow[iflow];
				cuts.push_back(tempString);
				tempString = Form("ciclevel%s%i-cat%i%s", iphotonID<10?"0":"", iphotonID, icat, cutflowName[iflow].c_str());
				cutName.push_back(tempString);
			}
		}
	}

	for(int icut = 0 ; icut < (int)cuts.size() ; icut++ )
	{
		cout << "##### NOW PROCESSING CUT " << icut+1 << " / " << cuts.size() << " : " << cutName[icut] << endl;
		DrawMCPlot(chain_sample, sample_list, "PhotonsMass", "PhotonsMass", "(80, 100, 180)", cuts[icut].c_str(), cutName[icut].c_str(), "m_{#gamma#gamma} [GeV]", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "PhotonsMass", "PhotonsMass", "(80, 100, 180)", cuts[icut].c_str(), cutName[icut].c_str(), "m_{#gamma#gamma} [GeV]", 1, canvas, integratedLumi);
	
		DrawMCPlot(chain_sample, sample_list, "dipho_tanhYStar", "diphoTanhYStar", "(20, 0.0, 1.0)", cuts[icut].c_str(), cutName[icut].c_str(), "|tanh(Y^{*})|", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_tanhYStar", "diphoTanhYStar", "(20, 0.0, 1.0)", cuts[icut].c_str(), cutName[icut].c_str(), "|tanh(Y^{*})|", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_cosThetaStar_CS", "diphoCosThetaStarCS", "(20, 0.0, 1.0)", cuts[icut].c_str(), cutName[icut].c_str(), "|cos(#theta^{*})|", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_cosThetaStar_CS", "diphoCosThetaStarCS", "(20, 0.0, 1.0)", cuts[icut].c_str(), cutName[icut].c_str(), "|cos(#theta^{*})|", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_Y", "diphoY", "(200, -3.0, 3.0)", cuts[icut].c_str(), cutName[icut].c_str(), "Y_{#gamma#gamma}", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_Y", "diphoY", "(200, -3.0, 3.0)", cuts[icut].c_str(), cutName[icut].c_str(), "Y_{#gamma#gamma}", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_pt", "diphoPt", "(200, 0.0, 500.0)", cuts[icut].c_str(), cutName[icut].c_str(), "p_{T}^{#gamma#gamma}", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_pt", "diphoPt", "(200, 0.0, 500.0)", cuts[icut].c_str(), cutName[icut].c_str(), "p_{T}^{#gamma#gamma}", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_pt", "diphoPt_zoom", "(200, 0.0, 150.0)", cuts[icut].c_str(), cutName[icut].c_str(), "p_{T}^{#gamma#gamma}", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_pt", "diphoPt_zoom", "(200, 0.0, 150.0)", cuts[icut].c_str(), cutName[icut].c_str(), "p_{T}^{#gamma#gamma}", 0, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_eta", "diphoEta", "(200, -10.0, 10.0)", cuts[icut].c_str(), cutName[icut].c_str(), "#eta^{#gamma#gamma}", 1, canvas, integratedLumi);
		DrawMCPlot(chain_sample, sample_list, "dipho_eta", "diphoEta", "(200, -10.0, 10.0)", cuts[icut].c_str(), cutName[icut].c_str(), "#eta^{#gamma#gamma}", 0, canvas, integratedLumi);
	}

	delete canvas;
	canvas = 0;
	chain_sample->Delete();
	sample_list.clear();

	return 0;
}

// **************************************************************************************************************************
void DrawMCPlot(TClonesArray* chain_sample, vector<Sample> sample_list, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi)
{
	if(DEBUG) cout << "##### INITIALIZATION #####" << endl;
	// ##### INITIALIZATION #####
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	// Get histos, set cuts
	TClonesArray * histos_temp = new TClonesArray("TH1F", sample_list.size() - 1);
	TClonesArray * histos = new TClonesArray("TH1F", sample_list.size() - 1);
	TClonesArray * superHistos = new TClonesArray("TH1F", sample_list.size() - 1);
	for(unsigned int isample = 0 ; isample < sample_list.size() ; isample++)
	{
		new ((*histos_temp)[isample]) TH1F();
		string tmp_histname = "histo_" + sample_list[isample].getName() + "_temp";
		string var = variable + ">>" + tmp_histname + range;
		string cut = "(" + cuts + " && " + sample_list[isample].getSpecificCuts() + ")";
		if( (sample_list[isample].getSpecificWeights()).find("manual") != std::string::npos )
		{
			std::ostringstream cutOSS;
			cutOSS << (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)integratedLumi * (double)sample_list[isample].getKFactor();
			string cutString = cutOSS.str();
			cut += " * pu_weight * " + cutString;
		} else {
			std::ostringstream cutOSS;
			cutOSS << (double) sample_list[isample].getKFactor();
			string cutString = cutOSS.str();
			cut += " * pu_weight * " + sample_list[isample].getSpecificWeights() + " * " + cutString;
		}
		if(DEBUG) sample_list[isample].print();
		if(DEBUG) cout << cut << endl;
		((TChain*)chain_sample->At(isample))->Draw(var.c_str(), cut.c_str());
		if(DEBUG) canvas->Print("dump.pdf");
		((*histos)[isample]) = (TH1F*)gDirectory->Get(tmp_histname.c_str());
		((*superHistos)[isample]) = (TH1F*)gDirectory->Get(tmp_histname.c_str());
		canvas->Clear();
	}

	if(DEBUG) cout << "##### SETUP STACK GROUPS #####" << endl;
	// ##### SETUP STACK GROUPS #####
	vector<string> stackGroups;
	vector<vector<int> > stackSamples;
	stackGroups.clear();
	stackSamples.clear();
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
	if(DEBUG)
	{
		for(int istack = 0 ; istack < (int)stackGroups.size() ; istack++)
		{
			cout << "stackGroups[" << istack << "]= " << stackGroups[istack] << endl;
		}
	
		for(int istack = 0 ; istack < (int)stackSamples.size() ; istack++)
		{
			cout << "stackSamples[" << istack << "]= ";
			for(int isample = 0 ; isample < (int)stackSamples[istack].size() ; isample++)
			{
				cout << stackSamples[istack][isample] << "(" << sample_list[ stackSamples[istack][isample] ].getName() << "), ";
			}
			cout << endl;
		}
	}
	if(DEBUG) cout << "##### GET INTEGRALS #####" << endl;
	// ##### GET INTEGRALS #####
	// to cope with under and overflow
	// do it only for the latest one in the stack
	vector<double> integrals;
	for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
	{
		integrals.push_back(0.0);
		for(int jsample=0 ; jsample < (int)stackSamples[istack].size() ; jsample++)
		{
			int isample = stackSamples[istack][jsample];
			string cut = "(" + cuts + " && " + sample_list[isample].getSpecificCuts() + ")";
			((TChain*)chain_sample->At(isample))->Draw("pu_weight>>temp_pu(100,0,10000)", cut.c_str());
			double pu_mean = (((TH1F*)gDirectory->Get("temp_pu"))->GetMean());
			canvas->Clear();
			if(DEBUG) cout << "### stack = " << stackGroups[istack] << "\tsample= " << sample_list[isample].getName() << endl;
			if(DEBUG) cout << "\tspecific weight= " << (sample_list[isample].getSpecificWeights()) << endl;
			if(DEBUG) cout << "\tisMatching= " << (sample_list[isample].getSpecificWeights()).find("manual") << endl;
			if( (sample_list[isample].getSpecificWeights()).find("manual") != std::string::npos )
			{
				integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)integratedLumi * sample_list[isample].getKFactor();
			} else {
				((TChain*)chain_sample->At(isample))->Draw("evweight>>temp_xsec(100,0,10000)", cut.c_str());
				double xsec_mean = (((TH1F*)gDirectory->Get("temp_xsec"))->GetMean());
				if(DEBUG) cout << "\tintegral = " << integrals[istack] << " + " << ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * xsec_mean * sample_list[isample].getKFactor()<< endl;
				integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * xsec_mean * sample_list[isample].getKFactor();
			}
			canvas->Clear();
			if(DEBUG) cout << "\tintegrals[" << istack << "]= " << integrals[istack] << endl;
		}
	}
	// If normalisation to unity asked for, divide histo by integral
/*	if(integratedLumi < 0.0)
	{
		if(DEBUG) cout << "##### NORMALIZATION TO UNITY, DIVIDE HISTO BY INTEGRAL #####" << endl;
		for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
		{
			int isample = stackSamples[istack].back();
			if(DEBUG) cout << "### sample= " << isample << "\t" << sample_list[isample].getName() << endl;
			if(DEBUG) cout << "\tintegral histogram= " << ((TH1F*)histos->At(isample))->Integral() << endl;
			if(DEBUG) cout << "\tmax,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum() << endl;
			((TH1F*)histos->At(isample))->Scale((double)1.0/(double)integrals[istack]);
			if(DEBUG) cout << "\tintegral stored= " << integrals[istack] << endl;
			if(DEBUG) cout << "\tmax,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum(0.0) << endl;
		}
	}
*/
	// effective stack, applied after correcting the event count if normalization to unity
	for( int istack = 0 ; istack < (int)stackSamples.size() ; istack++ )
	{
		for( int isample = 1 ; isample < (int)stackSamples[istack].size() ; isample++ )
		{
			((TH1F*)histos->At( stackSamples[istack][isample]) )->Add(   ((TH1F*)histos->At( stackSamples[istack][isample-1 ]))   );
		}
	}
	// superStack
	vector<string> superStackGroups;
	vector<vector<int> > superStackSamples;
	vector<double> superIntegrals;
	superStackGroups.clear();
	superStackSamples.clear();
	superIntegrals.clear();
	for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		string superStack = sample_list[isample].getSuperStackGroup();
		bool superStackAlreadyProcessed = false;
		for(int isuperStack=0 ; isuperStack<(int)superStackGroups.size() ; isuperStack++)
		{
			if( (superStack == superStackGroups[isuperStack]) && (superStack != "") )
			{
				superStackAlreadyProcessed = true;
				continue;
			}
		}
		if( (sample_list[isample].getSuperStackGroup() != "") && !superStackAlreadyProcessed )
		{ // if the sample is to be superStack, look for similar samples it is to be superStacked with
			superStackGroups.push_back(sample_list[isample].getSuperStackGroup());
			vector<int> samples;
			samples.clear();
			samples.push_back(isample);
			for(int jstack = istack+1 ; jstack < (int)stackSamples.size() ; jstack++)
			{
				int jsample = stackSamples[jstack].back();
				if( sample_list[isample].getSuperStackGroup() == sample_list[jsample].getSuperStackGroup() )
					samples.push_back(jsample);
			}
			superStackSamples.push_back(samples);
		} else if(sample_list[isample].getSuperStackGroup() == "") {
			superStackGroups.push_back(sample_list[isample].getDisplayName());
			vector<int> samples;
			samples.clear();
			samples.push_back(isample);
			superStackSamples.push_back(samples);
		}
	}
	if(DEBUG)
	{
		for(int isuperStack = 0 ; isuperStack < (int)superStackGroups.size() ; isuperStack++)
		{
			cout << "superStackGroups[" << isuperStack << "]= " << superStackGroups[isuperStack] << endl;
		}
	
		for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++)
		{
			cout << "superStackSamples[" << isuperStack << "]= ";
			for(int isample = 0 ; isample < (int)superStackSamples[isuperStack].size() ; isample++)
			{
				cout << superStackSamples[isuperStack][isample] << "(" << sample_list[ superStackSamples[isuperStack][isample] ].getName() << "), ";
			}
			cout << endl;
		}
	}
	// effective superStack
	for( int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++ )
	{
		for( int isample = 1 ; isample < (int)superStackSamples[isuperStack].size() ; isample++ )
		{
			((TH1F*)superHistos->At( superStackSamples[isuperStack][isample]) )->Add(   ((TH1F*)histos->At( superStackSamples[isuperStack][isample-1 ]))   );
		}
	}
	// renormalise superhistos if normalisation to unity
	if(integratedLumi < 0.0)
	{
		// step 1: compute superIntegral
		int iint = 0;
		for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++)
		{
			superIntegrals.push_back(0.0);
			for(int isample=0 ; isample < (int)superStackSamples[isuperStack].size() ; isample++)
			{
				if(DEBUG) cout << "\tiint= " << iint << "\tsuperIntegrals[" << isuperStack << "]+= " << integrals[iint] << "\t(= " << superIntegrals[isuperStack] + integrals[iint] << ")" << endl;
				superIntegrals[isuperStack] += integrals[iint];
				iint++;
			}
		}
		// step 2: normalisation
		for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++ )
		{
			for(int isample = 0 ; isample < (int)superStackSamples[isuperStack].size() ; isample++)
			{
				((TH1F*)superHistos->At( superStackSamples[isuperStack][isample]) )->Scale((double)1.0/(double)superIntegrals[isuperStack]);
//				((TH1F*)superHistos->At( superStackSamples[isuperStack][isample]) )->Scale((double)1.0/(double)integrals[0]);
			}
		}
	}
	if(DEBUG)
	{
		cout << "##### CHECKING INTEGRALS AND SUPERSTACKS #####" << endl;
		for(int iint=0 ; iint < (int)integrals.size() ; iint++)
		{
			cout << "integrals[" << iint << "]= " << integrals[iint] << endl;
		}
		for(int iint=0 ; iint < (int)superIntegrals.size() ; iint++)
		{
			cout << "superIntegrals[" << iint << "]= " << superIntegrals[iint] << endl;
		}
	}


	if(DEBUG) cout << "##### SET THE Y RANGE #####" << endl;
	// ##### SET THE Y RANGE #####
	// to keep some space for the legend
	double YMax = -INFINITY;
	double YMin = INFINITY;
	if(DEBUG) cout << "YMax= " << YMax << "\tYMin= " << YMin << endl;

	for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++)
	{
		int isample = superStackSamples[isuperStack].back();
		double max_sample = ((TH1F*)superHistos->At(isample))->GetMaximum();
		YMax = max(max_sample, YMax);
		double min_sample = ((TH1F*)superHistos->At(isample))->GetMinimum(0.0);
		YMin = min(min_sample, YMin);
	}
/*
	for(int istack = 0 ; istack < (int)stackSamples.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		double max_sample = ((TH1F*)histos->At(isample))->GetMaximum();
		YMax = max(max_sample, YMax);
		double min_sample = ((TH1F*)histos->At(isample))->GetMinimum(0.0);
		YMin = min(min_sample, YMin);
	}
*/
	if(DEBUG) cout <<"YMin= " << YMin << "\tYMax= " << YMax << endl;
	double YMin_lin = (double)YMin / (double)10.0;
	double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
	double YMax_lin = 0.2*Range_lin + YMax;
	if(DEBUG) cout << "YMin_lin= " << YMin_lin << "\tRange_lin= " << Range_lin << "\tYMax_lin= " << YMax_lin << endl;

	double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
	double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
	double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);

	if(DEBUG) cout << "##### SET UP NAMES, TITLES, LEGEND #####" << endl;
	// ##### SET UP NAMES, TITLES, LEGEND #####
	string canvas_name = variableFileName + "_" + cutsFileName;
	std::ostringstream binWidthOSS;
	binWidthOSS << (double)((TH1F*)histos->At(0))->GetBinWidth(1);
	string binWidth = binWidthOSS.str();
	string yAxisTitle = "";
	if( (xAxisTitle.rfind("[") < xAxisTitle.size()) && (xAxisTitle.rfind("]") < xAxisTitle.size()) )
	{
		string unit = xAxisTitle.substr(xAxisTitle.rfind("[")+1, xAxisTitle.rfind("]")-xAxisTitle.rfind("[")-1);
		yAxisTitle = (integratedLumi<0.0?"Normalized to unity / ":"Events / ") + binWidth + " " + unit;
	} else {
		yAxisTitle = (integratedLumi<0.0?"Normalized to unity / ":"Events / ") + binWidth;
	}


	((TH1F*)histos->At(0))->SetName(canvas_name.c_str());
	canvas->SetName(canvas_name.c_str());
	canvas->SetTitle(canvas_name.c_str());

	TLegend *legend = new TLegend(0.65, 0.82, 0.90, 0.93, "");
	legend->SetTextSize(0.025);
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	legend->SetShadowColor(kWhite);

	if(DEBUG) cout << "##### DRAW #####" << endl;
	// ##### DRAW #####
	gPad->Update();
//	((TH1F*)histos->At(stackSamples[0].back()))->GetXaxis()->SetTitle(xAxisTitle.c_str());
//	((TH1F*)histos->At(stackSamples[0].back()))->GetYaxis()->SetTitle(yAxisTitle.c_str());
	((TH1F*)histos->At(superStackSamples[0].back()))->GetXaxis()->SetTitle(xAxisTitle.c_str());
	((TH1F*)histos->At(superStackSamples[0].back()))->GetYaxis()->SetTitle(yAxisTitle.c_str());

	if( inLogScale ) canvas->SetLogy(1);
	else canvas->SetLogy(0);

	for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++)
	{
		for(int jsample = ((int)superStackSamples[isuperStack].size()-1) ; jsample >= 0 ; jsample--){
		int isample = superStackSamples[isuperStack][jsample];
		if(DEBUG) cout << "isuperStack= " << isuperStack << endl;
		if(DEBUG) cout << "isample= " << isample << endl;
		((TH1F*)superHistos->At(isample))->SetLineColor(sample_list[isample].getColor());
		((TH1F*)superHistos->At(isample))->SetFillColor(sample_list[isample].getColor());
		((TH1F*)superHistos->At(isample))->SetLineWidth(sample_list[isample].getLineWidth());
		((TH1F*)superHistos->At(isample))->SetFillStyle(sample_list[isample].getFillStyle());
		if( !inLogScale )
		{
			((TH1F*)superHistos->At(isample))->SetMaximum(YMax_lin);
			((TH1F*)superHistos->At(isample))->SetMinimum(YMin_lin);
		} else {
			((TH1F*)superHistos->At(isample))->SetMaximum(YMax_log);
			((TH1F*)superHistos->At(isample))->SetMinimum(YMin_log);
			((TH1F*)superHistos->At(isample))->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		}
		((TH1F*)superHistos->At(isample))->Draw((sample_list[isample].getDrawStyle() + ((isuperStack==0 && jsample == ((int)superStackSamples[isuperStack].size()-1)) ? "": "same")).c_str());
		string legendText = "";
		if( sample_list[isample].getStackGroup() != "" )
			legendText = sample_list[isample].getStackGroup();
		else
			legendText = sample_list[isample].getDisplayName();
		legend->AddEntry(((TH1F*)superHistos->At(isample))->GetName(), legendText.c_str(), "f");
	}
	}
/*
	for(int istack = 0 ; istack < (int)stackGroups.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		((TH1F*)histos->At(isample))->SetLineColor(sample_list[isample].getColor());
		((TH1F*)histos->At(isample))->SetFillColor(sample_list[isample].getColor());
		((TH1F*)histos->At(isample))->SetLineWidth(sample_list[isample].getLineWidth());
		((TH1F*)histos->At(isample))->SetFillStyle(sample_list[isample].getFillStyle());
		if( !inLogScale )
		{
			((TH1F*)histos->At(isample))->SetMaximum(YMax_lin);
			((TH1F*)histos->At(isample))->SetMinimum(YMin_lin);
		} else {
			((TH1F*)histos->At(isample))->SetMaximum(YMax_log);
			((TH1F*)histos->At(isample))->SetMinimum(YMin_log);
			((TH1F*)histos->At(isample))->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		}
		((TH1F*)histos->At(isample))->Draw((sample_list[isample].getDrawStyle() + (istack==0 ? "": "same")).c_str());
				legend->AddEntry(((TH1F*)histos->At(isample))->GetName(), stackGroups[istack].c_str(), "f");
	}
*/
	// Redraw signal on top
	for(int isuperStack=0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++)
	{
		int isample = superStackSamples[isuperStack].back();
		if( sample_list[isample].getType() < 0 )
			if( sample_list[isample].getSuperStackGroup() == "" )
				((TH1F*)superHistos->At(isample))->Draw("same");
	}
/*
	for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		if( sample_list[isample].getType() < 0 )
			((TH1F*)histos->At(isample))->Draw("same");
	}
*/

	gPad->RedrawAxis();
	legend->Draw();
	canvas->Update();

	TLatex *latexLabel = new TLatex();
	std::ostringstream intLumiString;
	intLumiString << setprecision (2) << fixed << (double)integratedLumi / (double)1000.0;
	string intLumiText = "#intL= " + intLumiString.str() + " fb^{-1}";
	latexLabel->SetTextSize(0.03);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.25, 0.96, "CMS Private 2013");
	latexLabel->DrawLatex(0.50, 0.96, "#sqrt{s} = 8 TeV");
	if(integratedLumi > 0.0) latexLabel->DrawLatex(0.67, 0.96, intLumiText.c_str());

	TLatex *latexYields = new TLatex();
	if( integratedLumi > 0.0 )
	{
		latexYields->SetTextSize(0.03);
		latexYields->SetNDC();
		double yCoordinate = 0.90;
		double yStep = .04;
		for(int istack = 0 ; istack < (int)integrals.size() ; istack++, yCoordinate-=yStep )
		{
			std::ostringstream tempString;
			tempString << setprecision(2) << fixed << integrals[istack];
			string tempText = "N_{" + stackGroups[istack] + "}= " + tempString.str();
			latexYields->DrawLatex(0.18, yCoordinate, tempText.c_str());
		}
	}

	canvas->Update();
	canvas->Draw();

	string PicName = "";
//	PicName="gif/" + canvas_name + (inLogScale?"_log":"_lin") + ".gif";
	PicName="gif/DataMC_" + canvas_name + (inLogScale?"_log":"") + ".gif";
	canvas->Print(PicName.c_str());
//	PicName="root/" + canvas_name + (inLogScale?"_log":"_lin") + ".root";
	PicName="root/DataMC_" + canvas_name + (inLogScale?"_log":"") + ".root";
	canvas->Print(PicName.c_str());
//	PicName="pdf/" + canvas_name + (inLogScale?"_log":"_lin") + ".pdf";
	PicName="pdf/DataMC_" + canvas_name + (inLogScale?"_log":"") + ".pdf";
	canvas->Print(PicName.c_str());

	delete legend;
	legend = 0;
	delete latexLabel;
	latexLabel = 0;
	delete latexYields;
	latexYields = 0;

	integrals.clear();
	histos_temp->Delete();
	histos->Delete();

	return;
}

