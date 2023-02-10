#include "util.h"
#include "datastore.h"
#include <map>
#include <deque>

class MyDataStore : public DataStore 
{
	public:
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addToCart(std::string uName, Product* p);
	void viewCart(std::string uName);
	void buyCart(std::string uName);

	private:
	std::set<User*> users_;
	std::set<Product*> products_;
	std::map<User*, std::deque<Product*>> cart_;
	std::map<std::string, std::set<Product*>> keyMap_;
	std::map<std::string, User*> userMap_;
};