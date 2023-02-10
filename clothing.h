#include <sstream>
#include <iomanip>
#include "product.h"


class Clothing : public Product {

	public:
	Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);

	~Clothing();

	std::set<std::string> keywords() const;

	void dump(std::ostream& os) const;

	bool isMatch(std::vector<std::string>& searchTerms) const;

	std::string displayString() const;

	//Accessors
	std::string getSize() const;
	std::string getBrand() const;

	private:
	std::string size_, brand_;
};