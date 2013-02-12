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
// local files
#include "CMSStyle.C"
#include "SampleHandler.h"
// defines
#define DEBUG 0

// namespaces
using namespace std;

void DrawMCPlot(TChain * chain_signal, TChain * chain_background, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi);

int main()
{
	gROOT->ProcessLine(".x setTDRStyle.C");
	vector<Sample> sample_list;
	Sample sig_vbf("vbf_m125_8TeV", "VBF, m_{H}=125 GeV", -1, 1.0);
	sig_vbf.setFiles("datastore/histograms_CMS-HGG_ALL.root");
	Sample bkg_diphojet("diphojet_8TeV", "#gamma#gamma + jets", 1, 1.0);
	bkg_diphojet.setFiles("datastore/histograms_CMS-HGG_ALL.root");

	sample_list.push_back(sig_vbf);
	sample_list.push_back(bkg_diphojet);

	TClonesArray chain_sample("TChain", sample_list.size() - 1);
	for(unsigned int isample = 0; isample < sample_list.size() - 1 ; isample++)
	{
		new (chain_sample[isample])	TChain(sample_list[isample].getName().c_str());
		((TChain*)chain_sample.At(isample))->Add(sample_list[isample].getFiles().c_str());
	}

	TChain *chain_signal = new TChain("vbf_m125_8TeV");
	TChain *chain_background = new TChain("diphojet_8TeV");
	TCanvas *canvas = new TCanvas();
	double integratedLumi = 5000.0;

	chain_signal->Add("datastore/histograms_CMS-HGG_ALL.root");	
	chain_background->Add("datastore/histograms_CMS-HGG_ALL.root");	

	DrawMCPlot(chain_signal, chain_background, "mass", "mass", "(160, 100, 180)", "100 < mass && mass < 180 && category < 4", "100_mass_180", "m_{#gamma#gamma}", 0, canvas, integratedLumi);
	
	delete chain_signal;
	chain_signal = 0;
	delete chain_background;
	chain_background = 0;
	delete canvas;
	canvas = 0;

return 0;
}

void DrawMCPlot(TChain * chain_signal, TChain * chain_background, string variable, string variableFileName, string range, string cuts, string cutsFileName, string xAxisTitle, bool inLogScale, TCanvas *canvas, double integratedLumi)
{
	if(DEBUG) cout << "##### INITIALIZATION #####" << endl;
	// ##### INITIALIZATION #####
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);

	// Get signal histo from signal tree
	TH1F *histo_signal_temp = new TH1F();
	string var_signal = variable + ">>histo_signal_temp" + range;
	string cut_signal = "(" + cuts + ") * xsec_weight";
	chain_signal->Draw(var_signal.c_str(), cut_signal.c_str());
	TH1F *histo_signal = (TH1F*)gDirectory->Get("histo_signal_temp");
	canvas->Clear();

	// Get background histo from background tree
	TH1F *histo_background_temp = new TH1F();
	string var_background = variable + ">>histo_background_temp" + range;
	string cut_background = "(" + cuts + ") * xsec_weight";
	chain_background->Draw(var_background.c_str(), cut_background.c_str());
	TH1F *histo_background = (TH1F*)gDirectory->Get("histo_background_temp");
	canvas->Clear();

	if(DEBUG) cout << "##### GET INTEGRALS #####" << endl;
	// ##### GET INTEGRALS #####
	// to cope with under and overflow
	double integral_signal = chain_signal->GetEntries(cut_signal.c_str());
	double integral_background = chain_background->GetEntries(cut_background.c_str());
	canvas->Clear();

	if(DEBUG) cout << "##### SET THE Y RANGE #####" << endl;
	// ##### SET THE Y RANGE #####
	// to keep some space for the legend
	double YMax = 0.0;
	double YMin = 0.0;
	if(DEBUG) cout << "YMax= " << YMax << "\tYMin= " << YMin << endl;

	double max_signal = histo_signal->GetMaximum();
	double max_background = histo_background->GetMaximum();
	if(DEBUG) cout << "max_signal= " << max_signal << "\tmax_background= " << max_background << endl;
	YMax = max(max_signal, max_background);

	YMin = YMax;
	double min_signal = YMin;
	double min_background = YMin;

	for( int ibin=1 ; ibin<histo_signal->GetNbinsX() ; ibin++)
	{
		unsigned int bincontent = histo_signal->GetBinContent(ibin);
		if( (bincontent != 0) && (bincontent < min_signal) )
		{
			min_signal = bincontent;
		}
	}

	for( int ibin=1 ; ibin<histo_background->GetNbinsX() ; ibin++)
	{
		unsigned int bincontent = histo_background->GetBinContent(ibin);
		if( (bincontent != 0) && (bincontent < min_background) )
		{
			min_background = bincontent;
		}
	}
	YMin = min(min_signal, min_background);

	double YMin_lin = (double)YMin / (double)10.0;
	double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
	double YMax_lin = 0.2*Range_lin + YMax;
	if(DEBUG) cout << "YMin_lin= " << YMin_lin << "\tRange_lin= " << Range_lin << "\tYMax_lin= " << YMax_lin << endl;

	double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
	double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
	double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);

	if(DEBUG) cout << "##### SET UP NAMES, TITLES, LEGEND #####" << endl;
	// ##### SET UP NAMES, TITLES, LEGEND #####
	string mc_name = "MC_" + variableFileName + "_" + cutsFileName;
	string canvas_name = "MC_" + variableFileName + "_" + cutsFileName;
	std::ostringstream binWidthOSS;
	binWidthOSS << (double)histo_signal->GetBinWidth(1);
	string binWidth = binWidthOSS.str();
	string yAxisTitle = "";
	if( (xAxisTitle.rfind("[") < xAxisTitle.size()) && (xAxisTitle.rfind("]") < xAxisTitle.size()) )
	{
		string unit = xAxisTitle.substr(xAxisTitle.rfind("[")+1, xAxisTitle.rfind("]")-xAxisTitle.rfind("[")-1);
		yAxisTitle = "Events / " + binWidth + " " + unit;
	} else {
		yAxisTitle = "Events / " + binWidth;
	}

	histo_signal->SetName(mc_name.c_str());
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
	histo_signal->GetXaxis()->SetTitle(xAxisTitle.c_str());
	histo_signal->GetYaxis()->SetTitle(yAxisTitle.c_str());
	histo_signal->SetLineColor(kRed);
	histo_signal->SetLineWidth(3);
	histo_signal->SetFillColor(kRed);
	histo_signal->SetFillStyle(3004);
	histo_signal->SetMaximum(YMax_lin);
	histo_signal->SetMinimum(YMin_lin);

	histo_background->SetLineColor(kAzure+1);
	histo_background->SetFillColor(kAzure+1);
	histo_background->SetFillStyle(3001);
	histo_background->SetMaximum(YMax_lin);
	histo_background->SetMinimum(YMin_lin);

	histo_signal->Draw("");
	legend->AddEntry(histo_signal->GetName(), "signal", "f");
	histo_background->Draw("same");	
	legend->AddEntry(histo_background->GetName(), "background", "f");
	histo_signal->Draw("same");

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
	latexLabel->DrawLatex(0.67, 0.96, intLumiText.c_str());

	TLatex *latexYields = new TLatex();
	latexYields->SetTextSize(0.03);
	latexYields->SetNDC();
	std::ostringstream tempString;
	tempString << setprecision(2) << fixed << integral_signal;
	string tempText = "N_{signal}= " + tempString.str();
	latexYields->DrawLatex(0.18, 0.90, tempText.c_str());
	std::ostringstream tempString2;
	tempString2 << setprecision(2) << fixed << integral_background;
	string tempText2 = "N_{background}= " + tempString2.str();
	latexYields->DrawLatex(0.18, 0.86, tempText2.c_str());

	canvas->Update();
	canvas->Draw();

	string PicName = "";
	PicName="gif/" + canvas_name + ".gif";
	canvas->Print(PicName.c_str());
	PicName="root/" + canvas_name + ".root";
	canvas->Print(PicName.c_str());
	PicName="pdf/" + canvas_name + ".pdf";
	canvas->Print(PicName.c_str());

	delete histo_signal_temp;
	histo_signal_temp = 0;
	delete histo_background_temp;
	histo_background_temp = 0;
	delete legend;
	legend = 0;
	delete latexLabel;
	latexLabel = 0;
	delete latexYields;
	latexYields = 0;

	return;
}
