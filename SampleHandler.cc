// to handle somewhat more cleanly metadata
// Olivier Bondu, February 2013
// C++ headers
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

