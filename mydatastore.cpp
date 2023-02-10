#include "mydatastore.h"

using namespace std;
MyDataStore::~MyDataStore(){
	while(!users_.empty()){
		delete *users_.begin();
		users_.erase(users_.begin());
	}
	while(!products_.empty()){
		delete *products_.begin();
		products_.erase(products_.begin());
	}
}

void MyDataStore::addProduct(Product* p){
	products_.insert(p);

	for(string s : p->keywords()){
		keyMap_[s].insert(p);
	}

}

void MyDataStore::addUser(User* u){
	users_.insert(u);
	userMap_[u->getName()] = u;
}

void MyDataStore::addToCart(string uName, Product* p){
	if(!userMap_.count(uName)){
		cout << "Invalid request" << endl;
	}
	else{
		cart_[userMap_[uName]].push_back(p);
	}
}

void MyDataStore::viewCart(string uName){
	if(!userMap_.count(uName)){
		cout << "Invalid username" << endl;
	}
	else{
		for(size_t i = 0; i < cart_[userMap_[uName]].size(); i++){
			cout << "Item " << i+1 << ": " << endl;
			cout << cart_[userMap_[uName]][i]->displayString();
			cout << endl;
		}
	}
}

void MyDataStore::buyCart(string uName){
	size_t popCount = 0;
	if(!userMap_.count(uName)){
		cout << "Invalid username" << endl;
	}
	else{
		for(size_t i = 0; i < cart_[userMap_[uName]].size() + popCount; i++){
			if(userMap_[uName]->getBalance() > cart_[userMap_[uName]][i-popCount]->getPrice() and cart_[userMap_[uName]][i-popCount]->getQty() > 0){
				userMap_[uName]->deductAmount(cart_[userMap_[uName]][i-popCount]->getPrice());
				cart_[userMap_[uName]][i-popCount]->subtractQty(1);
				cart_[userMap_[uName]].pop_front();
				popCount++;
			}
		}
	}
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	vector<Product*> retvec;
	set<Product*> duplicate;
	Product* removal;
	vector<Product*>::iterator count;
	//OR
	if(type){
		for(string s: terms){
			if(keyMap_.count(s)){
				for(Product* p : keyMap_[s]){
					if(duplicate.find(p) == duplicate.end()){
						retvec.push_back(p);
						duplicate.insert(p);
					}
				}
			}
		}
	}
	//AND
	else{
		for(string s : terms){
			if(retvec.empty()){
				if(keyMap_.count(s)){
					for(Product* p : keyMap_[s]){
						retvec.push_back(p);
					}
				}
			}
			else{
				if(keyMap_.count(s)){
					for(Product* p : retvec){
						count = retvec.begin() - 1;
						if(keyMap_[s].find(p) == keyMap_[s].end()){
							removal = *(count + 1);
							while(removal != p){
								count++;
								removal = *count;
							}
							retvec.erase(count);
						}
					}
				}
			}
		}
	}

	return retvec;
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << "\n";
	for(Product* p : products_){
		p->dump(ofile);
	}
	ofile << "</products>" << "\n";
	ofile << "<users>" << "\n";
	for(User* p : users_){
		p->dump(ofile);
	}
	ofile << "</users>" << "\n";
}