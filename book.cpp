#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;
Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
	Product(category, name, price, qty),
	ISBN_(ISBN),
	author_(author)
{}

Book::~Book(){}

set<std::string> Book::keywords() const{
	set<string> keywords;

	//name keyword
	for(string s : parseStringToWords(getName())){
		keywords.insert(s);
	}
	for(string s : parseStringToWords(getAuthor())){
		keywords.insert(s);
	}
	keywords.insert(getISBN());
	return keywords;
}

void Book::dump(std::ostream& os) const{
	Product::dump(os);
	os << ISBN_ << "\n" << author_ << endl;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
	set<string> kw = keywords();
	for(string s : searchTerms){
		if(kw.find(s) != kw.end()){
			return true;
		}
	}
	return false;
}

std::string Book::displayString() const{
	stringstream ss;
	ss << getName() << "\n";
	ss << "Author: " << author_ << " ISBN: " << ISBN_ << "\n";
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
string Book::getAuthor() const{
	return author_;
}
string Book::getISBN() const{
	return ISBN_;
}