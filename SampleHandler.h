// to handle somewhat more cleanly metadata
// Olivier Bondu, February 2013
// C++ headers
#include <string>
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
		int initialNumberOfEvents;
		string files;
		Color_t color;
		int lineWidth;
		int fillStyle;
		string drawStyle;
		string specificCuts;
		string specificWeights;
	public:
		Sample(string name_, string displayName_, int type_, double xSection_, int initialNumberOfEvents_, double kFactor_);
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
		int getInitialNumberOfEvents() const;
		void setInitialNumberOfEvents(int initialNumberOfEvents_);
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
		void setStyle(Color_t color_, int lineWidth_, int fillStyle_, string drawStyle_);

		void print() const;
};


Sample::Sample(string name_, string displayName_, int type_ = 0, double xSection_ = 1.0, int initialNumberOfEvents_ = 1, double kFactor_ = 1.0)
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
	specificCuts = "";
	specificWeights = "1.0";
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
int Sample::getInitialNumberOfEvents() const{ return initialNumberOfEvents; }
void Sample::setInitialNumberOfEvents(int initialNumberOfEvents_){ initialNumberOfEvents = initialNumberOfEvents_; }
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
	<< endl;
}

