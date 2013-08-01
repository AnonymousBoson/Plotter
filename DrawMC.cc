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
void DrawMCPlot(TClonesArray* chain_sample, vector<Sample> sample_list, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi, vector<string> othervariable, bool computeEffSigma = false);
string to_string(int num);
Double_t effSigma(TH1 * hist);

// **************************************************************************************************************************
int main()
{
	cout << "##### Drawing macro #####" << endl;
	cout << "##### Initialization #####" << endl;
	gErrorIgnoreLevel = kWarning;
	gROOT->ProcessLine(".x setTDRStyle.C");
	TGaxis::SetMaxDigits(3);
//	string file = "../BJetRegression/Radion_mALL_8TeV_nm_StandardFullSelection.root";
//	string file = "../BJetRegression/Radion_mALL_8TeV_nm_StandardFullSelection_oneRegressionPerMass.root";
//	string file = "../BJetRegression/Radion_mALL_8TeV_nm_StandardFullSelection_SimultaneousRegressionEqualWeightPerMass.root";
	string file = "../BJetRegression/Radion_mALL_8TeV_nm_StandardFullSelection_SimultaneousRegressionXSweight.root";

// 300 GeV Radion
	Sample radion_m300("Radion_m300_8TeV_nm", "Radion (300 GeV)", -1, 1.0);
	radion_m300.setFiles(file);
	radion_m300.setStyle(kGreen+3, 3, 3004, "");
	radion_m300.setInitialNumberOfEvents(20000);
	radion_m300.setXSection(2.71e-4);
	radion_m300.setSpecificWeights("manual");

	Sample radion_m300_reg(radion_m300);
	radion_m300_reg.setDisplayName("Radion (300 GeV) (Reg)");
	radion_m300_reg.setStyle(kRed+2, 3, 3005, "");
	radion_m300_reg.setUseAlternativeVariable(1);

	Sample radion_m300_regkin(radion_m300);
	radion_m300_regkin.setDisplayName("Radion (300 GeV) (Reg+Kin)");
	radion_m300_regkin.setStyle(kBlue, 3, 3003, "");
	radion_m300_regkin.setUseAlternativeVariable(2);

	vector<Sample> sample_list_m300;
	sample_list_m300.push_back(radion_m300);
	sample_list_m300.push_back(radion_m300_reg);
	sample_list_m300.push_back(radion_m300_regkin);

	vector<Sample> sample_list_nokin_m300;
	sample_list_nokin_m300.push_back(radion_m300);
	sample_list_nokin_m300.push_back(radion_m300_reg);

// 500 GeV Radion
	Sample radion_m500("Radion_m500_8TeV_nm", "Radion (500 GeV)", -1, 1.0);
	radion_m500.setFiles(file);
	radion_m500.setStyle(kGreen+3, 3, 3004, "");
	radion_m500.setInitialNumberOfEvents(19998);
	radion_m500.setXSection(4.71e-05);
	radion_m500.setSpecificWeights("manual");

	Sample radion_m500_reg(radion_m500);
	radion_m500_reg.setDisplayName("Radion (500 GeV) (Reg)");
	radion_m500_reg.setStyle(kRed+2, 3, 3005, "");
	radion_m500_reg.setUseAlternativeVariable(1);

	Sample radion_m500_regkin(radion_m500);
	radion_m500_regkin.setDisplayName("Radion (500 GeV) (Reg+Kin)");
	radion_m500_regkin.setStyle(kBlue, 3, 3003, "");
	radion_m500_regkin.setUseAlternativeVariable(2);

	vector<Sample> sample_list_m500;
	sample_list_m500.push_back(radion_m500);
	sample_list_m500.push_back(radion_m500_reg);
	sample_list_m500.push_back(radion_m500_regkin);

	vector<Sample> sample_list_nokin_m500;
	sample_list_nokin_m500.push_back(radion_m500);
	sample_list_nokin_m500.push_back(radion_m500_reg);

// 700 GeV Radion
	Sample radion_m700("Radion_m700_8TeV_nm", "Radion (700 GeV)", -1, 1.0);
	radion_m700.setFiles(file);
	radion_m700.setStyle(kGreen+3, 3, 3004, "");
	radion_m700.setInitialNumberOfEvents(19998);
	radion_m700.setXSection(1.58E-05);
	radion_m700.setSpecificWeights("manual");

	Sample radion_m700_reg(radion_m700);
	radion_m700_reg.setDisplayName("Radion (700 GeV) (Reg)");
	radion_m700_reg.setStyle(kRed+2, 3, 3005, "");
	radion_m700_reg.setUseAlternativeVariable(1);

	Sample radion_m700_regkin(radion_m700);
	radion_m700_regkin.setDisplayName("Radion (700 GeV) (Reg+Kin)");
	radion_m700_regkin.setStyle(kBlue, 3, 3003, "");
	radion_m700_regkin.setUseAlternativeVariable(2);

	vector<Sample> sample_list_m700;
	sample_list_m700.push_back(radion_m700);
	sample_list_m700.push_back(radion_m700_reg);
	sample_list_m700.push_back(radion_m700_regkin);

	vector<Sample> sample_list_nokin_m700;
	sample_list_nokin_m700.push_back(radion_m700);
	sample_list_nokin_m700.push_back(radion_m700_reg);

// 1000 GeV Radion
	Sample radion_m1000("Radion_m1000_8TeV_nm", "Radion (1000 GeV)", -1, 1.0);
	radion_m1000.setFiles(file);
	radion_m1000.setStyle(kGreen+3, 3, 3004, "");
	radion_m1000.setInitialNumberOfEvents(19996);
	radion_m1000.setXSection(2.63E-06);
	radion_m1000.setSpecificWeights("manual");

	Sample radion_m1000_reg(radion_m1000);
	radion_m1000_reg.setDisplayName("Radion (1000 GeV) (Reg)");
	radion_m1000_reg.setStyle(kRed+2, 3, 3005, "");
	radion_m1000_reg.setUseAlternativeVariable(1);

	Sample radion_m1000_regkin(radion_m1000);
	radion_m1000_regkin.setDisplayName("Radion (1000 GeV) (Reg+Kin)");
	radion_m1000_regkin.setStyle(kBlue, 3, 3003, "");
	radion_m1000_regkin.setUseAlternativeVariable(2);

	vector<Sample> sample_list_m1000;
	sample_list_m1000.push_back(radion_m1000);
	sample_list_m1000.push_back(radion_m1000_reg);
	sample_list_m1000.push_back(radion_m1000_regkin);

	vector<Sample> sample_list_nokin_m1000;
	sample_list_nokin_m1000.push_back(radion_m1000);
	sample_list_nokin_m1000.push_back(radion_m1000_reg);


	TClonesArray * chain_sample_m300 = new TClonesArray("TChain", sample_list_m300.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_m300.size() ; isample++)
	{
		new ((*chain_sample_m300)[isample])	TChain(sample_list_m300[isample].getName().c_str());
		((TChain*)chain_sample_m300->At(isample))->Add(sample_list_m300[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_m500 = new TClonesArray("TChain", sample_list_m500.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_m500.size() ; isample++)
	{
		new ((*chain_sample_m500)[isample])	TChain(sample_list_m500[isample].getName().c_str());
		((TChain*)chain_sample_m500->At(isample))->Add(sample_list_m500[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_m700 = new TClonesArray("TChain", sample_list_m700.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_m700.size() ; isample++)
	{
		new ((*chain_sample_m700)[isample])	TChain(sample_list_m700[isample].getName().c_str());
		((TChain*)chain_sample_m700->At(isample))->Add(sample_list_m700[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_m1000 = new TClonesArray("TChain", sample_list_m1000.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_m1000.size() ; isample++)
	{
		new ((*chain_sample_m1000)[isample])	TChain(sample_list_m1000[isample].getName().c_str());
		((TChain*)chain_sample_m1000->At(isample))->Add(sample_list_m1000[isample].getFiles().c_str());
	}

// no kin
	TClonesArray * chain_sample_nokin_m300 = new TClonesArray("TChain", sample_list_nokin_m300.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_nokin_m300.size() ; isample++)
	{
		new ((*chain_sample_nokin_m300)[isample])	TChain(sample_list_nokin_m300[isample].getName().c_str());
		((TChain*)chain_sample_nokin_m300->At(isample))->Add(sample_list_nokin_m300[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_nokin_m500 = new TClonesArray("TChain", sample_list_nokin_m500.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_nokin_m500.size() ; isample++)
	{
		new ((*chain_sample_nokin_m500)[isample])	TChain(sample_list_nokin_m500[isample].getName().c_str());
		((TChain*)chain_sample_nokin_m500->At(isample))->Add(sample_list_nokin_m500[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_nokin_m700 = new TClonesArray("TChain", sample_list_nokin_m700.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_nokin_m700.size() ; isample++)
	{
		new ((*chain_sample_nokin_m700)[isample])	TChain(sample_list_nokin_m700[isample].getName().c_str());
		((TChain*)chain_sample_nokin_m700->At(isample))->Add(sample_list_nokin_m700[isample].getFiles().c_str());
	}

	TClonesArray * chain_sample_nokin_m1000 = new TClonesArray("TChain", sample_list_nokin_m1000.size() - 1);
	for(unsigned int isample = 0; isample < sample_list_nokin_m1000.size() ; isample++)
	{
		new ((*chain_sample_nokin_m1000)[isample])	TChain(sample_list_nokin_m1000[isample].getName().c_str());
		((TChain*)chain_sample_nokin_m1000->At(isample))->Add(sample_list_nokin_m1000[isample].getFiles().c_str());
	}

	TCanvas *canvas = new TCanvas();
//	double integratedLumi = 19620.0;
	double integratedLumi = 19788.0;
//	double integratedLumi = -1.0;

	vector <string> cutflow;
	vector <string> cutflowname;
	cutflow.push_back("1");
	cutflowname.push_back("all_cat");
	cutflow.push_back("njets_kRadionID_and_CSVM == 1");
	cutflowname.push_back("1bjet");
	cutflow.push_back("njets_kRadionID_and_CSVM > 1");
	cutflowname.push_back("2bjet");
/*
	cutflow.push_back("gg_mass < 135 && gg_mass > 115");
	cutflowname.push_back("mggCut-115-135_all_cat");
	cutflow.push_back("njets_kRadionID_and_CSVM == 1 && gg_mass < 135 && gg_mass > 115");
	cutflowname.push_back("mggCut-115-135_1bjet");
	cutflow.push_back("njets_kRadionID_and_CSVM > 1 && gg_mass < 135 && gg_mass > 115");
	cutflowname.push_back("mggCut-115-135_2bjet");
*/
	cout << "##### DRAW #####" << endl;
	vector<string> altvarsjj;
		altvarsjj.push_back("regjj_mass");
		altvarsjj.push_back("regkinjj_mass");
	vector<string> altvarsggjj;
		altvarsggjj.push_back("regggjj_mass");
		altvarsggjj.push_back("regkinggjj_mass");
		
for(int icut = 0 ; icut < (int)cutflow.size() ; icut++)
{
// m300
	DrawMCPlot(chain_sample_nokin_m300, sample_list_nokin_m300, "jj_mass", "jj_mass_nokin_m300", "(45, 70, 250)", cutflow[icut], cutflowname[icut], "m_{jj} [GeV]", 0, canvas, integratedLumi, altvarsjj, false);
	DrawMCPlot(chain_sample_m300, sample_list_m300, "ggjj_mass", "ggjj_mass_m300", "(50, 200, 400)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
	DrawMCPlot(chain_sample_nokin_m300, sample_list_nokin_m300, "ggjj_mass", "ggjj_mass_nokin_m300", "(50, 200, 400)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
// m500 
	DrawMCPlot(chain_sample_nokin_m500, sample_list_nokin_m500, "jj_mass", "jj_mass_nokin_m500", "(45, 70, 250)", cutflow[icut], cutflowname[icut], "m_{jj} [GeV]", 0, canvas, integratedLumi, altvarsjj, false);
	DrawMCPlot(chain_sample_m500, sample_list_m500, "ggjj_mass", "ggjj_mass_m500", "(50, 400, 600)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
	DrawMCPlot(chain_sample_nokin_m500, sample_list_nokin_m500, "ggjj_mass", "ggjj_mass_nokin_m500", "(50, 400, 600)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
// m700
	DrawMCPlot(chain_sample_nokin_m700, sample_list_nokin_m700, "jj_mass", "jj_mass_nokin_m700", "(45, 70, 250)", cutflow[icut], cutflowname[icut], "m_{jj} [GeV]", 0, canvas, integratedLumi, altvarsjj, false);
	DrawMCPlot(chain_sample_m700, sample_list_m700, "ggjj_mass", "ggjj_mass_m700", "(50, 500, 900)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
	DrawMCPlot(chain_sample_nokin_m700, sample_list_nokin_m700, "ggjj_mass", "ggjj_mass_nokin_m700", "(50, 500, 900)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
// m1000
	DrawMCPlot(chain_sample_nokin_m1000, sample_list_nokin_m1000, "jj_mass", "jj_mass_nokin_m1000", "(45, 70, 250)", cutflow[icut], cutflowname[icut], "m_{jj} [GeV]", 0, canvas, integratedLumi, altvarsjj, false);
	DrawMCPlot(chain_sample_m1000, sample_list_m1000, "ggjj_mass", "ggjj_mass_m1000", "(50, 700, 1200)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
	DrawMCPlot(chain_sample_nokin_m1000, sample_list_nokin_m1000, "ggjj_mass", "ggjj_mass_nokin_m1000", "(50, 700, 1200)", cutflow[icut], cutflowname[icut], "m_{#gamma#gamma jj} [GeV]", 0, canvas, integratedLumi, altvarsggjj, false);
}

	delete canvas;
	canvas = 0;
	chain_sample_m300->Delete();
	sample_list_m300.clear();
	chain_sample_m500->Delete();
	sample_list_m500.clear();
	chain_sample_m700->Delete();
	sample_list_m700.clear();
	chain_sample_m1000->Delete();
	sample_list_m1000.clear();

	chain_sample_nokin_m300->Delete();
	sample_list_nokin_m300.clear();
	chain_sample_nokin_m500->Delete();
	sample_list_nokin_m500.clear();
	chain_sample_nokin_m700->Delete();
	sample_list_nokin_m700.clear();
	chain_sample_nokin_m1000->Delete();
	sample_list_nokin_m1000.clear();

	return 0;
}





// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************




void DrawMCPlot(TClonesArray* chain_sample, vector<Sample> sample_list, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi, vector<string> othervariable, bool computeEffSigma)
{
	string CMSPrivate = "CMS Private 2013     #sqrt{s} = 8 TeV";
//	string CMSPrivate = "CMS Private 2013     #sqrt{s} = 8 TeV     Parton regression";
	if(DEBUG) cout << endl << "##### INITIALIZATION #####" << endl;
	// ##### INITIALIZATION #####
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	// Get histos, set cuts
	TClonesArray * histos_temp = new TClonesArray("TH1F", sample_list.size() - 1);
	TClonesArray * histos = new TClonesArray("TH1F", sample_list.size() - 1);
	TClonesArray * superHistos = new TClonesArray("TH1F", sample_list.size() - 1);
	for(int isample = 0 ; isample < (int)sample_list.size() ; isample++)
	{
		if(DEBUG) sample_list[isample].print();
		new ((*histos_temp)[isample]) TH1F();
		string tmp_histname = "histo_" + sample_list[isample].getName() + "_temp" + to_string(isample);
		string var = variable + ">>" + tmp_histname + range;
		if(sample_list[isample].getUseAlternativeVariable() > 0) var = othervariable[sample_list[isample].getUseAlternativeVariable()-1] + ">>" + tmp_histname + range;
		string cut = "(" + cuts + " && " + sample_list[isample].getSpecificCuts() + ")";
		if( (sample_list[isample].getSpecificWeights()).find("manual") != std::string::npos )
		{
			std::ostringstream cutOSS;
			if(integratedLumi > 0.)
				cutOSS << (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)integratedLumi * (double)sample_list[isample].getKFactor();
			else
				cutOSS << (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)sample_list[isample].getKFactor();
			string cutString = cutOSS.str();
			cut += " * pu_weight * " + cutString;
		} else {
			std::ostringstream cutOSS;
			cutOSS << (double) sample_list[isample].getKFactor();
			string cutString = cutOSS.str();
			cut += " * pu_weight * " + sample_list[isample].getSpecificWeights() + " * " + cutString;
		}
		if(DEBUG) cout << cut << endl;
		((TChain*)chain_sample->At(isample))->Draw(var.c_str(), cut.c_str());
		if(DEBUG) canvas->Print("dump.pdf");
		if(DEBUG) cout << "tmp_histname= " << tmp_histname << endl;
		((*histos)[isample]) = (TH1F*)gDirectory->Get(tmp_histname.c_str());
		if(DEBUG) cout << "((TH1F*)histos->At(" << isample << "))->Integral()= " << ((TH1F*)histos->At(isample))->Integral() << endl;
		((*superHistos)[isample]) = (TH1F*)gDirectory->Get(tmp_histname.c_str());
		canvas->Clear();
	}
	if(DEBUG) cout << endl << "END OF INITIALIZATION" << endl;
		if(DEBUG) {unsigned int isample = 0; cout << "((TH1F*)histos->At(" << isample << "))->Integral()= " << ((TH1F*)histos->At(isample))->Integral() << endl; }

	if(DEBUG) cout << "##### SETUP STACK GROUPS #####" << endl;
	// ##### SETUP STACK GROUPS #####
	vector<string> stackGroups;
	vector<vector<int> > stackSamples;
	stackGroups.clear();
	stackSamples.clear();
	for(int isample = 0 ; isample < chain_sample->GetEntriesFast() ; isample++)
	{
		string stack = sample_list[isample].getStackGroup();
		if(DEBUG) cout << "sample_list[" << isample << "].getStackGroup()= " << sample_list[isample].getStackGroup() << endl;
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
	if(DEBUG) cout << "stackSamples.size()= " << stackSamples.size() << endl;
	for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
	{
		integrals.push_back(0.0);
		for(int jsample=0 ; jsample < (int)stackSamples[istack].size() ; jsample++)
		{
			int isample = stackSamples[istack][jsample];
			string cut = "(" + cuts + " && " + sample_list[isample].getSpecificCuts() + ")";
			((TChain*)chain_sample->At(isample))->Draw("pu_weight>>temp_pu(100,0,10)", cut.c_str());
			double pu_mean = (((TH1F*)gDirectory->Get("temp_pu"))->GetMean());
			canvas->Clear();
			if(DEBUG) cout << "pu_mean= " << pu_mean << endl;
			if(DEBUG) cout << "stack = " << stackGroups[istack] << "\tsample= " << sample_list[isample].getName() << endl;
			if(DEBUG) cout << "specific weight= " << (sample_list[isample].getSpecificWeights()) << endl;
			if(DEBUG) cout << "isMatching= " << (sample_list[isample].getSpecificWeights()).find("manual") << endl;
			if(DEBUG) cout << "((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str())= " << ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) << endl;
			if( (sample_list[isample].getSpecificWeights()).find("manual") != std::string::npos )
			{
				if(integratedLumi > 0.)
					integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)integratedLumi * sample_list[isample].getKFactor();
				else
					integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * sample_list[isample].getKFactor();
				if(DEBUG) cout << "manual weight, integrals[istack]+= " << integrals[istack] << endl;
			} else {
//				((TChain*)chain_sample->At(isample))->Draw("xsec_weight>>temp_xsec(100,0,10)", cut.c_str());
				((TChain*)chain_sample->At(isample))->Draw("weight>>temp_xsec(100,0,10)", cut.c_str());
				double xsec_mean = (((TH1F*)gDirectory->Get("temp_xsec"))->GetMean());
				integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * xsec_mean * sample_list[isample].getKFactor();
				if(DEBUG) cout << "integrals[istack]+= " << integrals[istack] << endl;
			}
			canvas->Clear();
			if(DEBUG) cout << "integrals[" << istack << "]= " << integrals[istack] << endl;
		}
	}
	// If normalisation to unity asked for, divide histo by integral
	if(integratedLumi < 0.0)
	{
		if(DEBUG) cout << "Will normalize to unity" << endl;
		if(DEBUG)
		{
			cout << "stackSamples.size()= " << stackSamples.size() << endl;
			for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
			{
				cout << "stackSamples[" << istack << "].size()= " << stackSamples[istack].size() << endl;
				for(int jsample=0 ; jsample < (int)stackSamples[istack].size() ; jsample++)
				{
					cout << "\tstackSamples[" << istack << "][" << jsample << "]= " << stackSamples[istack][jsample] << endl;
				}
				cout << "stackSamples[" << istack << "].back()= " << stackSamples[istack].back() << endl;
			}
		}
		for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
		{
			int isample = stackSamples[istack].back();
			if(DEBUG) cout << "isample= " << isample << endl;
			((TH1F*)histos->At(isample))->ComputeIntegral();
//			if(DEBUG) cout << "integral histogram= " << ((TH1F*)histos->At(isample))->Integral() << endl;
			if(DEBUG) cout << "((TH1F*)histos->At(" << isample << "))->Integral()= " << ((TH1F*)histos->At(isample))->Integral() << endl;
			if(DEBUG) cout << "max,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum() << endl;
			((TH1F*)histos->At(isample))->Scale((double)1.0/(double)integrals[istack]);
			if(DEBUG) cout << "integral stored= " << integrals[istack] << endl;
			if(DEBUG) cout << "max,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum(0.0) << endl;
		}
	}
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
	if(DEBUG) cout << "setup axis titles" << endl;
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


	if(DEBUG) cout << "setup canvas name and title" << endl;
	string canvas_name = variableFileName + "_" + cutsFileName;
	((TH1F*)histos->At(0))->SetName(canvas_name.c_str());
	canvas->SetName(canvas_name.c_str());
	canvas->SetTitle(canvas_name.c_str());

	if(DEBUG) cout << "setup legend" << endl;
	TLegend *legend = new TLegend(0.55, 0.82, 0.90, 0.93, "");
	if( computeEffSigma )
		legend->SetX1(0.45);
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
		if( computeEffSigma )
		{
			std::ostringstream tempString;
			tempString << setprecision(2) << fixed << effSigma((TH1F*)superHistos->At(isample));
			legendText += "   #sigma_{eff}= " + tempString.str() + " GeV";
		}
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
	latexLabel->DrawLatex(0.25, 0.96, CMSPrivate.c_str());
//	latexLabel->DrawLatex(0.50, 0.96, "#sqrt{s} = 8 TeV");
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

/*
	TLatex *latexEffSigma = new TLatex();
	if( computeEffSigma )
	{
		latexEffSigma->SetTextSize(0.03);
		latexEffSigma->SetNDC();
		double yCoordinate = 0.90;
		double yStep = .04;
		for(int isuperStack = 0 ; isuperStack < (int)superStackSamples.size() ; isuperStack++, yCoordinate-=yStep)
		{
			int isample = superStackSamples[isuperStack].back();
			std::ostringstream tempString;
//		legend->AddEntry(((TH1F*)superHistos->At(isample))->GetName(), legendText.c_str(), "f");
			tempString << setprecision(2) << fixed << effSigma((TH1F*)superHistos->At(isample));
			string tempText = "#sigma_{eff} (" + stackGroups[isample] + ")= " + tempString.str();
			latexEffSigma->DrawLatex(0.18, yCoordinate, tempText.c_str());
		}
	}
*/
	canvas->Update();
	canvas->Draw();

	string PicName = "";
	PicName="gif/" + canvas_name + (inLogScale?"_log":"_lin") + ".gif";
	canvas->Print(PicName.c_str());
	PicName="root/" + canvas_name + ".root";
	canvas->Print(PicName.c_str());
	PicName="pdf/" + canvas_name + ".pdf";
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

string to_string(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}


// --- Compute the effective sigma of a given histogram --- //
Double_t effSigma(TH1 * hist)
{

  TAxis *xaxis = hist->GetXaxis();
  Int_t nb = xaxis->GetNbins();
  if(nb < 10) {
    cout << "effsigma: Not a valid histo. nbins = " << nb << endl;
    return 0.;
  }
  
  Double_t bwid = xaxis->GetBinWidth(1);
  if(bwid == 0) {
    cout << "effsigma: Not a valid histo. bwid = " << bwid << endl;
    return 0.;
  }
//  Double_t xmax = xaxis->GetXmax();
  Double_t xmin = xaxis->GetXmin();
  Double_t ave = hist->GetMean();
  Double_t rms = hist->GetRMS();

  Double_t total=0.;
  for(Int_t i=0; i<nb+2; i++) {
    total+=hist->GetBinContent(i);
  }
  if(total < 100.) {
    cout << "effsigma: Too few entries " << total << endl;
    return 0.;
  }
  Int_t ierr=0;
  Int_t ismin=999;
  
  Double_t rlim=0.683*total;
  Int_t nrms=rms/(bwid);    // Set scan size to +/- rms
  if(nrms > nb/10) nrms=nb/10; // Could be tuned...

  Double_t widmin=9999999.;
  for(Int_t iscan=-nrms;iscan<nrms+1;iscan++) { // Scan window centre
    Int_t ibm=(ave-xmin)/bwid+1+iscan;
    Double_t x=(ibm-0.5)*bwid+xmin;
    Double_t xj=x;
    Double_t xk=x;
    Int_t jbm=ibm;
    Int_t kbm=ibm;
    Double_t bin=hist->GetBinContent(ibm);
    total=bin;
    for(Int_t j=1;j<nb;j++){
      if(jbm < nb) {
        jbm++;
        xj+=bwid;
        bin=hist->GetBinContent(jbm);
        total+=bin;
        if(total > rlim) break;
      }
      else ierr=1;
      if(kbm > 0) {
        kbm--;
        xk-=bwid;
        bin=hist->GetBinContent(kbm);
        total+=bin;
        if(total > rlim) break;
      }
      else ierr=1;
    }
    Double_t dxf=(total-rlim)*bwid/bin;
    Double_t wid=(xj-xk+bwid-dxf)*0.5;
    if(wid < widmin) {
      widmin=wid;
      ismin=iscan;
    }   
  }
  if(ismin == nrms || ismin == -nrms) ierr=3;
  if(ierr != 0) cout << "effsigma: Error of type " << ierr << endl;
  
  return widmin;
  
}
