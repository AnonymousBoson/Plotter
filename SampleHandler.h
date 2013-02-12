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
	<< endl;
}

