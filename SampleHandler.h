#ifndef __SAMPLE_HANDLER_H__
#define __SAMPLE_HANDLER_H__
// to handle somewhat more cleanly metadata
// Olivier Bondu, February 2013
// C++ headers
#include <string>
#include <iostream>
// ROOT headers
#include "TROOT.h"
// namespaces
using namespace std;

class Sample
{
	private:
		string name;
		string displayName;
		int type; // negatives for signal, positives for background, 0 for data
		double xSection; // in pb
		double kFactor;
		double initialNumberOfEvents;
		string files;
		Color_t color;
		int lineWidth;
		int fillStyle;
		string drawStyle;
		string specificCuts;
		string specificWeights;
		string stackGroup;
		string superStackGroup;
	public:
//		Sample(string name_, string displayName_, int type_, double xSection_, double initialNumberOfEvents_, double kFactor_);
		Sample(string name_, string displayName_, int type_ = 0, double xSection_ = 1.0, double initialNumberOfEvents_ = 1, double kFactor_ = 1.0);
		Sample(const Sample &);

		string getName() const;
		void setName(string name_);
		string getDisplayName() const;
		void setDisplayName(string displayName_);
		int getType() const;
		void setType(int type_);
		double getXSection() const;
		void setXSection(double xSection_);
		double getKFactor() const;
		void setKFactor(double kFactor_);
		double getInitialNumberOfEvents() const;
		void setInitialNumberOfEvents(double initialNumberOfEvents_);
		string getFiles() const;
		void setFiles(string files_);
		Color_t getColor() const;
		void setColor(Color_t color_);
		int getLineWidth() const;
		void setLineWidth(int lineWidth_);
		int getFillStyle() const;
		void setFillStyle(int fillStyle_);
		string getDrawStyle() const;
		void setDrawStyle(string drawStyle_);
		string getSpecificCuts() const;
		void setSpecificCuts(string specificCuts_);
		string getSpecificWeights() const;
		void setSpecificWeights(string specificWeights_);
		string getStackGroup() const;
		void setStackGroup(string stackGroup_);
		string getSuperStackGroup() const;
		void setSuperStackGroup(string superStackGroup_);
		void setStyle(Color_t color_, int lineWidth_, int fillStyle_, string drawStyle_);

		void print() const;

};

void getStackGroups(vector<Sample> sample_list, vector<string> & stackGroups, vector<vector<int> > & stackSamples);
void printStackGroups(vector<Sample> sample_list, vector<string> stackGroups, vector<vector<int> > stackSamples);

void getSuperStackGroups(vector<Sample> sample_list, vector<vector<int> > stackSamples, vector<string> & superStackGroups, vector<vector<int> > & superStackSamples, vector<vector<int> > & superStackStacks);
void printSuperStackGroups(vector<Sample> sample_list, vector<string> superStackGroups, vector<vector<int> > superStackSamples, vector<vector<int> > superStackStacks);


#endif
