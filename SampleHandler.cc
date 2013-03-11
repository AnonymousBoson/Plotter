// to handle somewhat more cleanly metadata
// Olivier Bondu, February 2013
// C++ headers
//#include <iostream>
#include <string>
// local files
#include "SampleHandler.h"
// namespaces
using namespace std;



//Sample::Sample(string name_, string displayName_, int type_ = 0, double xSection_ = 1.0, double initialNumberOfEvents_ = 1, double kFactor_ = 1.0)
Sample::Sample(string name_, string displayName_, int type_, double xSection_, double initialNumberOfEvents_, double kFactor_)
{
	name = name_;
	displayName = displayName_;
	type = type_;
	xSection = xSection_;
	kFactor = kFactor_;
	initialNumberOfEvents = initialNumberOfEvents_;
	files = "";
	color = kBlue;
	lineWidth = 1;
	fillStyle = 3001;
	drawStyle = "";
	specificCuts = "1.0";
	specificWeights = "1.0";
	stackGroup = "";
	superStackGroup = "";
}

Sample::Sample(const Sample & s)
{
	name = s.getName();
	displayName = s.getDisplayName();
	type = s.getType();
	xSection = s.getXSection();
	kFactor = s.getKFactor();
	initialNumberOfEvents = s.getInitialNumberOfEvents();
	files = s.getFiles();
	color = s.getColor();
	lineWidth = s.getLineWidth();
	fillStyle = s.getFillStyle();
	drawStyle = s.getDrawStyle();
	specificCuts = s.getSpecificCuts();
	specificWeights = s.getSpecificWeights();
	stackGroup = s.getStackGroup();
	superStackGroup = s.getSuperStackGroup();
}

string Sample::getName() const{ return name; }
void Sample::setName(string name_){ name = name_; }
string Sample::getDisplayName() const{ return displayName; }
void Sample::setDisplayName(string displayName_){ displayName = displayName_;}
int Sample::getType() const{ return type; }
void Sample::setType(int type_){ type = type_; }
double Sample::getXSection() const{ return xSection; }
void Sample::setXSection(double xSection_){ xSection = xSection_; }
double Sample::getKFactor() const{ return kFactor; }
void Sample::setKFactor(double kFactor_){ kFactor = kFactor_; }
double Sample::getInitialNumberOfEvents() const{ return initialNumberOfEvents; }
void Sample::setInitialNumberOfEvents(double initialNumberOfEvents_){ initialNumberOfEvents = initialNumberOfEvents_; }
string Sample::getFiles() const{ return files; }
void Sample::setFiles(string files_){ files = files_; }
Color_t Sample::getColor() const{ return color; }
void Sample::setColor(Color_t color_){ color = color_; }
int Sample::getLineWidth() const{ return lineWidth; }
void Sample::setLineWidth(int lineWidth_){ lineWidth = lineWidth_; }
int Sample::getFillStyle() const{ return fillStyle; }
void Sample::setFillStyle(int fillStyle_){ fillStyle = fillStyle_; }
string Sample::getDrawStyle() const{ return drawStyle; }
void Sample::setDrawStyle(string drawStyle_){ drawStyle = drawStyle_; }
string Sample::getSpecificCuts() const{ return specificCuts; }
void Sample::setSpecificCuts(string specificCuts_){ specificCuts = specificCuts_; }
string Sample::getSpecificWeights() const{ return specificWeights; }
void Sample::setSpecificWeights(string specificWeights_){ specificWeights = specificWeights_; }
string Sample::getStackGroup() const{ return stackGroup; }
void Sample::setStackGroup(string stackGroup_){ stackGroup = stackGroup_; }
string Sample::getSuperStackGroup() const{ return superStackGroup; }
void Sample::setSuperStackGroup(string superStackGroup_){ superStackGroup = superStackGroup_; }
void Sample::setStyle(Color_t color_, int lineWidth_, int fillStyle_, string drawStyle_)
{
	color = color_;
	lineWidth = lineWidth_;
	fillStyle = fillStyle_;
	drawStyle = drawStyle_;
}


void Sample::print() const
{
	cout
	<< "name= " << name
	<< "\tdisplayName= " << displayName
	<< "\ttype= " << type
	<< "\txSection= " << xSection
	<< "\tkFactor= " << kFactor
	<< "\tinitialNumberOfEvents= " << initialNumberOfEvents
	<< "\tfiles= " << files
	<< "\tcolor= " << color
	<< "\tlineWidth= " << lineWidth
	<< "\tfillStyle= " << fillStyle
	<< "\tdrawStyle= " << drawStyle
	<< "\tspecificCuts= " << specificCuts
	<< "\tspecificWeights= " << specificWeights
	<< "\tstackGroup= " << stackGroup
	<< "\tsuperStackGroup= " << superStackGroup
	<< endl;
}


void getStackGroups(vector<Sample> sample_list, vector<string> &stackGroups, vector<vector<int> > & stackSamples)
{
//	vector<string> stackGroups;
	stackGroups.clear();
	stackSamples.clear();

	for(int isample = 0 ; isample < (int)sample_list.size() ; isample++)
	{
		string stack = sample_list[isample].getStackGroup();
		bool stackAlreadyProcessed = false;
		for(int istack = 0 ; istack < (int)stackGroups.size() ; istack++)
		{ // check if this stack group has already been processed
			if( (stack == stackGroups[istack]) && (stack != "") )
			{
				stackAlreadyProcessed = true;
				continue;
			}
		}
		if( (sample_list[isample].getStackGroup() != "") && !stackAlreadyProcessed )
		{ // if the sample is to be stacked, look for similar samples it is to be stacked with
			stackGroups.push_back(sample_list[isample].getStackGroup());
			vector<int> samples;
			samples.clear();
			samples.push_back(isample);
			for(int jsample = isample+1 ; jsample < (int)sample_list.size() ; jsample++)
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

	return;
}

void getSuperStackGroups(vector<Sample> sample_list, vector<vector<int> > stackSamples, vector<string> & superStackGroups, vector<vector<int> > & superStackSamples, vector<vector<int> > & superStackStacks)
{
	superStackGroups.clear();
	superStackSamples.clear();
	superStackStacks.clear();

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
			vector<int> stacks;
			samples.clear();
			stacks.clear();
			samples.push_back(isample);
			stacks.push_back(istack);
			for(int jstack = istack+1 ; jstack < (int)stackSamples.size() ; jstack++)
			{
				int jsample = stackSamples[jstack].back();
				if( sample_list[isample].getSuperStackGroup() == sample_list[jsample].getSuperStackGroup() )
				{
					samples.push_back(jsample);
					stacks.push_back(jstack);
				}
			}
			superStackSamples.push_back(samples);
			superStackStacks.push_back(stacks);
		} else if(sample_list[isample].getSuperStackGroup() == "") {
			if(sample_list[isample].getStackGroup() == "")
				superStackGroups.push_back(sample_list[isample].getDisplayName());
			else
				superStackGroups.push_back(sample_list[isample].getStackGroup());
			vector<int> samples;
			vector<int> stacks;
			samples.clear();
			stacks.clear();
			samples.push_back(isample);
			stacks.push_back(istack);
			superStackSamples.push_back(samples);
			superStackStacks.push_back(stacks);
		}
	}
	return;
}

void printStackGroups(vector<Sample> sample_list, vector<string> stackGroups, vector<vector<int> > stackSamples)
{
	cout << "stackGroups.size()= " << stackGroups.size() << "\t\tstackSamples.size()= " << stackSamples.size() << endl;
	for(int is = 0 ; is < (int)stackGroups.size() ; is++)
	{
		cout << "stackGroups[" << is << "]= " << stackGroups[is] << endl;
		for(int js = 0 ; js < (int)stackSamples[is].size() ; js++)
			cout << "\tstackSamples[" << is << "][" << js << "]= " << stackSamples[is][js] << "\tname= " << sample_list[stackSamples[is][js]].getName() << endl;
	}
	return;
}

void printSuperStackGroups(vector<Sample> sample_list, vector<string> superStackGroups, vector<vector<int> > superStackSamples, vector<vector<int> > superStackStacks)
{
	cout << "superStackGroups.size()= " << superStackGroups.size() << "\t\tsuperStackSamples.size()= " << superStackSamples.size() << "\t\tsuperStackStacks.size()= " << superStackStacks.size() << endl;
	for(int is = 0 ; is < (int)superStackGroups.size() ; is++)
	{
		cout << "superStackGroups[" << is << "]= " << superStackGroups[is] << endl;
		for(int js = 0 ; js < (int)superStackSamples[is].size() ; js++)
			cout << "\tsuperStackSamples[" << is << "][" << js << "]= " << superStackSamples[is][js] << "\tname= " << sample_list[superStackSamples[is][js]].getName() << "\tsuperStackStacks= " << superStackStacks[is][js] << endl;
	}
	return;
}

