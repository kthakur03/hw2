#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <set>
#include <string>
#include <vector>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    bool addToCart(const std::string& username, Product* product);
    bool viewCart(const std::string& username) const;
    bool buyCart(const std::string& username);
    bool hasUser(const std::string& username) const;

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::vector<Product*> > carts_;
};
#endif
