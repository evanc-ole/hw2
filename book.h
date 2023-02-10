#include <sstream>
#include <iomanip>
#include "product.h"


class Book : public Product {

	public:
	Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);

	~Book();

	std::set<std::string> keywords() const;

	void dump(std::ostream& os) const;

	bool isMatch(std::vector<std::string>& searchTerms) const;

	std::string displayString() const;

	//Accessors
	std::string getAuthor() const;
	std::string getISBN() const;

	private:
	std::string ISBN_, author_;
};