#include <sstream>
#include <iomanip>
#include "product.h"


class Movie : public Product {

	public:
	Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);

	~Movie();

	std::set<std::string> keywords() const;

	void dump(std::ostream& os) const;

	bool isMatch(std::vector<std::string>& searchTerms) const;

	std::string displayString() const;

	//Accessors
	std::string getGenre() const;
	std::string getRating() const;

	private:
	std::string genre_, rating_;
};