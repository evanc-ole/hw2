#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;
	Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{}

Movie::~Movie(){}

set<std::string> Movie::keywords() const{
	set<string> keywords;
	string genre;
	//name keyword
	for(string s : parseStringToWords(getName())){
		keywords.insert(s);
	}
	for(char c : genre_){
		genre += tolower(c);
	}

	keywords.insert(genre);

	return keywords;
}

void Movie::dump(std::ostream& os) const{
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
	set<string> kw = keywords();
	for(string s : searchTerms){
		if(kw.find(s) != kw.end()){
			return true;
		}
	}
	return false;
}

std::string Movie::displayString() const{
	stringstream ss;
	ss << getName() << "\n";
	ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
	ss << getPrice() << " " << getQty() << " left. \n";
	string retval, line;

	for(unsigned i = 0; i < 3; i++){
		getline(ss, line);
		retval += line;
		retval += "\n";
	}
	
	return retval;
}

std::string Movie::getGenre() const{
	return genre_;
}