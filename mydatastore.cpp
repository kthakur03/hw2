#include <iostream>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore()
{
    for(size_t i = 0; i < products_.size(); ++i) delete products_[i];
    for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) delete it->second;
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
    set<string> keys = p->keywords();
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
        keywordMap_[convToLower(*it)].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string name = convToLower(u->getName());
    users_[name] = u;
    carts_[name] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> result;
    if(terms.empty()) return result;

    set<Product*> matches;
    string first = convToLower(terms[0]);
    map<string, set<Product*> >::iterator firstIt = keywordMap_.find(first);
    if(firstIt != keywordMap_.end()) matches = firstIt->second;

    for(size_t i = 1; i < terms.size(); ++i) {
        string term = convToLower(terms[i]);
        set<Product*> current;
        map<string, set<Product*> >::iterator it = keywordMap_.find(term);
        if(it != keywordMap_.end()) current = it->second;
        if(type == 0) matches = setIntersection(matches, current);
        else matches = setUnion(matches, current);
    }

    for(set<Product*>::iterator it = matches.begin(); it != matches.end(); ++it) result.push_back(*it);
    return result;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for(size_t i = 0; i < products_.size(); ++i) products_[i]->dump(ofile);
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) it->second->dump(ofile);
    ofile << "</users>" << endl;
}

bool MyDataStore::hasUser(const string& username) const
{
    return users_.find(convToLower(username)) != users_.end();
}

bool MyDataStore::addToCart(const string& username, Product* product)
{
    string name = convToLower(username);
    if(users_.find(name) == users_.end() || product == NULL) return false;
    carts_[name].push_back(product);
    return true;
}

bool MyDataStore::viewCart(const string& username) const
{
    string name = convToLower(username);
    map<string, User*>::const_iterator uit = users_.find(name);
    if(uit == users_.end()) return false;
    map<string, vector<Product*> >::const_iterator cit = carts_.find(name);
    if(cit != carts_.end()) {
        for(size_t i = 0; i < cit->second.size(); ++i) {
            cout << "Item " << i + 1 << endl;
            cout << cit->second[i]->displayString() << endl;
            cout << endl;
        }
    }
    return true;
}

bool MyDataStore::buyCart(const string& username)
{
    string name = convToLower(username);
    map<string, User*>::iterator uit = users_.find(name);
    if(uit == users_.end()) return false;

    vector<Product*>& cart = carts_[name];
    vector<Product*> remaining;
    for(size_t i = 0; i < cart.size(); ++i) {
        Product* p = cart[i];
        if(p->getQty() > 0 && uit->second->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            uit->second->deductAmount(p->getPrice());
        }
        else remaining.push_back(p);
    }
    cart = remaining;
    return true;
}
