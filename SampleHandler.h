// to handle somewhat more cleanly metadata
// Olivier Bondu, February 2013
class Sample
{
	private:
		string name;
		string displayName;
		int type; // negatives for signal, positives for background, 0 for data
		double xSection; // in pb
		double kFactor;
	public:
		Sample(string name_, string displayName_);

		string getName();
		void setName(string name_);
		string getDisplayName();
		void setDisplayName(string displayName_);
		int getType();
		void setType(int type_);
		double getXSesction();
		void setXSection(double xSection_);
		double getKFactor();
		void setKFactor(double kFactor_);

		~Sample();
}

Sample::Sample(string name_, string displayName_)
{
	name = name_;
	displayName = displayName_;
	type = 0;
	xSection = 1.0;
	kFactor = 1.0;
	
}

string Sample::getName();
void Sample::setName(string name_);
string Sample::getDisplayName();
void Sample::setDisplayName(string displayName_);
int Sample::getType();
void Sample::setType(int type_);
double Sample::getXSesction();
void Sample::setXSection(double xSection_);
double Sample::getKFactor();
void Sample::setKFactor(double kFactor_);

Sample::~Sample();

