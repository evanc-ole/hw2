#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{}

Clothing::~Clothing(){}

set<std::string> Clothing::keywords() const{
	set<string> keywords;

	//name keyword
	for(string s : parseStringToWords(getName())){
		keywords.insert(s);
	}
	for(string s : parseStringToWords(getBrand())){
		keywords.insert(s);
	}
	return keywords;
}

void Clothing::dump(std::ostream& os) const{
	Product::dump(os);
	os << size_ << "\n" << brand_ << endl;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
	set<string> kw = keywords();
	for(string s : searchTerms){
		if(kw.find(s) != kw.end()){
			return true;
		}
	}
	return false;
}

std::string Clothing::displayString() const{
	stringstream ss;
	ss << getName() << "\n";
	ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
	ss << getPrice() << " " << getQty() << " left. \n";
	string retval, line;

	for(unsigned i = 0; i < 3; i++){
		getline(ss, line);
		retval += line;
		retval += "\n";
	}
	
	return retval;
}

//Accessors
string Clothing::getBrand() const{
	return brand_;
}
string Clothing::getSize() const{
	return size_;
}
