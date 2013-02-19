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
	gROOT->ProcessLine(".x setTDRStyle.C");
	TGaxis::SetMaxDigits(3);
	vector<Sample> sample_list;

	Sample sig_vbf("vbf_m125_8TeV", "VBF (125 GeV)", -1, 1.0);
	sig_vbf.setFiles("datastore/histograms_CMS-HGG_ALL.root");
	sig_vbf.setStyle(kGreen, 3, 3004, "");
	sig_vbf.setXSection((1.578 * 2.28 * 0.001));
	sig_vbf.setInitialNumberOfEvents(79784.0);
	sig_vbf.setSpecificWeights("manual");
	sig_vbf.setStackGroup("SM Higgs (125GeV)");
	sig_vbf.setSubStackGroup("VBF");

	Sample sig_ggh("ggh_m125_8TeV", "ggH (125 GeV)", -1, 1.0);
	sig_ggh.setFiles("datastore/histograms_CMS-HGG_ALL.root");
	sig_ggh.setStyle(kRed, 3, 3004, "");
	sig_ggh.setXSection((19.52 * 2.28 * 0.001));
	sig_ggh.setInitialNumberOfEvents(69036.0);
	sig_ggh.setSpecificWeights("manual");
	sig_ggh.setStackGroup("SM Higgs (125GeV)");
	sig_ggh.setSubStackGroup("GGF");

	Sample bkg_diphojet("diphojet_8TeV", "#gamma#gamma + jets", 1, 1.0);
	bkg_diphojet.setFiles("datastore/histograms_CMS-HGG_ALL.root");
	bkg_diphojet.setStyle(kAzure+1, 1, 3001, "");
	bkg_diphojet.setSpecificWeights("xsec_weight");

// prodXsection@125GeV
//{'vbf_m120_8TeV': 1.649 * 2.23 10-3, 'vbf_m125_8TeV': 1.578 * 2.28 10-3, 'ggh_m125_8TeV': 19.52 * 2.28 10-3}
// number of initial events
//{'vbf_m120_8TeV': 79376.0, 'diphojet_8TeV': 639312.0, 'vbf_m125_8TeV': 79784.0, 'ggh_m125_8TeV': 69036.0}

	sample_list.push_back(sig_vbf);
	sample_list.push_back(sig_ggh);
	sample_list.push_back(bkg_diphojet);

	TClonesArray * chain_sample = new TClonesArray("TChain", sample_list.size() - 1);
	for(unsigned int isample = 0; isample < sample_list.size() ; isample++)
	{
		new ((*chain_sample)[isample])	TChain(sample_list[isample].getName().c_str());
		((TChain*)chain_sample->At(isample))->Add(sample_list[isample].getFiles().c_str());
	}

	TCanvas *canvas = new TCanvas();
//	double integratedLumi = 5000.0;
	double integratedLumi = -1.0;

	cout << "##### DRAW #####" << endl;
	DrawMCPlot(chain_sample, sample_list, "mass", "mass", "(80, 100, 180)", "100 < mass && mass < 180 && category == 0", "cat0", "m_{#gamma#gamma} [GeV]", 0, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "mass", "mass", "(80, 100, 180)", "100 < mass && mass < 180 && category == 0", "cat0", "m_{#gamma#gamma} [GeV]", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoCosThetaStar_altDef", "diphoCosThetaStar_altDef", "(20, 0.0, 1.0)", "100 < mass && mass < 180 && category == 0", "cat0", "|tanh(Y^{*})|", 0, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoCosThetaStar_altDef", "diphoCosThetaStar_altDef", "(20, 0.0, 1.0)", "100 < mass && mass < 180 && category == 0", "cat0", "|tanh(Y^{*})|", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoCosThetaStar", "diphoCosThetaStar", "(20, 0.0, 1.0)", "100 < mass && mass < 180 && category == 0", "cat0", "|cos(#theta^{*})|", 0, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoCosThetaStar", "diphoCosThetaStar", "(20, 0.0, 1.0)", "100 < mass && mass < 180 && category == 0", "cat0", "|cos(#theta^{*})|", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoRapidity", "diphoRapidity", "(200, -3.0, 3.0)", "100 < mass && mass < 180 && category == 0", "cat0", "Y_{#gamma#gamma}", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoRapidity", "diphoRapidity", "(200, -3.0, 3.0)", "100 < mass && mass < 180 && category == 0", "cat0", "Y_{#gamma#gamma}", 0, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoPt", "diphoPt", "(200, 0.0, 500.0)", "100 < mass && mass < 180 && category == 0", "cat0", "p_{T}^{#gamma#gamma}", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoPt", "diphoPt", "(200, 0.0, 500.0)", "100 < mass && mass < 180 && category == 0", "cat0", "p_{T}^{#gamma#gamma}", 0, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoEta", "diphoEta", "(200, -10.0, 10.0)", "100 < mass && mass < 180 && category == 0", "cat0", "#eta^{#gamma#gamma}", 1, canvas, integratedLumi);
	DrawMCPlot(chain_sample, sample_list, "diphoEta", "diphoEta", "(200, -10.0, 10.0)", "100 < mass && mass < 180 && category == 0", "cat0", "#eta^{#gamma#gamma}", 0, canvas, integratedLumi);


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
		canvas->Clear();
	}

	if(DEBUG) cout << "##### SETUP STACK GROUPS #####" << endl;
	// ##### SETUP STACK GROUPS #####
	vector<string> stackGroups;
	vector<string> substackGroups;
	vector<vector<int> > stackSamples;
	vector<vector<int> > substackSamples;
	stackGroups.clear();
	substackGroups.clear();
	stackSamples.clear();
	substackSamples.clear();
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
	// effective stack
	for( int istack = 0 ; istack < (int)stackSamples.size() ; istack++ )
	{
		for( int isample = 1 ; isample < (int)stackSamples[istack].size() ; isample++ )
		{
			((TH1F*)histos->At( stackSamples[istack][isample]) )->Add(   ((TH1F*)histos->At( stackSamples[istack][isample-1 ]))   );
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
			((TChain*)chain_sample->At(isample))->Draw("pu_weight>>temp_pu(100,0,10)", cut.c_str());
			double pu_mean = (((TH1F*)gDirectory->Get("temp_pu"))->GetMean());
			canvas->Clear();
			if(DEBUG) cout << "stack = " << stackGroups[istack] << "\tsample= " << sample_list[isample].getName() << endl;
			if(DEBUG) cout << "specific weight= " << (sample_list[isample].getSpecificWeights()) << endl;
			if(DEBUG) cout << "isMatching= " << (sample_list[isample].getSpecificWeights()).find("manual") << endl;
			if( (sample_list[isample].getSpecificWeights()).find("manual") != std::string::npos )
			{
				integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * (double)sample_list[isample].getXSection() / (double)sample_list[isample].getInitialNumberOfEvents() * (double)integratedLumi * sample_list[isample].getKFactor();
			} else {
				((TChain*)chain_sample->At(isample))->Draw("xsec_weight>>temp_xsec(100,0,10)", cut.c_str());
				double xsec_mean = (((TH1F*)gDirectory->Get("temp_xsec"))->GetMean());
				integrals[istack] += ((TChain*)chain_sample->At(isample))->GetEntries(cut.c_str()) * pu_mean * xsec_mean * sample_list[isample].getKFactor();
			}
			canvas->Clear();
			if(DEBUG) cout << "integrals[" << istack << "]= " << integrals[istack] << endl;
		}
	}
	// If normalisation to unity asked for, divide histo by integral
	if(integratedLumi < 0.0)
	{
		for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
		{
			int isample = stackSamples[istack].back();
			if(DEBUG) cout << "integral histogram= " << ((TH1F*)histos->At(isample))->Integral() << endl;
			if(DEBUG) cout << "max,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum() << endl;
			((TH1F*)histos->At(isample))->Scale((double)1.0/(double)integrals[istack]);
			if(DEBUG) cout << "integral stored= " << integrals[istack] << endl;
			if(DEBUG) cout << "max,min= " << ((TH1F*)histos->At(isample))->GetMaximum() << " , " << ((TH1F*)histos->At(isample))->GetMinimum(0.0) << endl;
		}
	}

	if(DEBUG) cout << "##### SET THE Y RANGE #####" << endl;
	// ##### SET THE Y RANGE #####
	// to keep some space for the legend
	double YMax = -INFINITY;
	double YMin = INFINITY;
	if(DEBUG) cout << "YMax= " << YMax << "\tYMin= " << YMin << endl;

	for(int istack = 0 ; istack < (int)stackSamples.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		double max_sample = ((TH1F*)histos->At(isample))->GetMaximum();
		YMax = max(max_sample, YMax);
		double min_sample = ((TH1F*)histos->At(isample))->GetMinimum(0.0);
		YMin = min(min_sample, YMin);
	}

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
	((TH1F*)histos->At(stackSamples[0].back()))->GetXaxis()->SetTitle(xAxisTitle.c_str());
	((TH1F*)histos->At(stackSamples[0].back()))->GetYaxis()->SetTitle(yAxisTitle.c_str());

	if( inLogScale ) canvas->SetLogy(1);
	else canvas->SetLogy(0);

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

	// Redraw signal on top
	for(int istack=0 ; istack < (int)stackSamples.size() ; istack++)
	{
		int isample = stackSamples[istack].back();
		if( sample_list[isample].getType() < 0 )
			((TH1F*)histos->At(isample))->Draw("same");
	}


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

