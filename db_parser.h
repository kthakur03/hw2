#ifndef DB_PARSER_H
#define DB_PARSER_H
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "datastore.h"
#include "product_parser.h"

class SectionParser {
public:
    virtual ~SectionParser() {}
    virtual bool parse(std::istream& is, DataStore& ds, int& lineno, std::string& errorMsg) = 0;
    virtual void reportItemsRead(std::ostream& os) = 0;
};

class DBParser {
public:
    DBParser();
    ~DBParser();
    void addSectionParser(const std::string& sectionName, SectionParser* parser);
    bool parse(std::string db_filename, DataStore& ds);
private:
    enum PState { FIND_SECTION, IN_SECTION };
    std::map<std::string, SectionParser*> parsers_;
    int lineno_;
    bool error_;
    std::string errorMsg_;
};

class ProductSectionParser : public SectionParser {
public:
    ProductSectionParser();
    ~ProductSectionParser();
    void addProductParser(ProductParser* p);
    bool parse(std::istream& is, DataStore& ds, int& lineno, std::string& errorMsg);
    void reportItemsRead(std::ostream& os);
private:
    Product* parseProduct(const std::string& category, std::istream& is, int& lineno, std::string& errorMsg);
    std::map<std::string, ProductParser*> prodParsers_;
    int numRead_;
};

class UserSectionParser : public SectionParser {
public:
    UserSectionParser();
    bool parse(std::istream& is, DataStore& ds, int& lineno, std::string& errorMsg);
    void reportItemsRead(std::ostream& os);
private:
    User* parseUser(std::istream& is, DataStore& ds, std::string& errorMsg);
    int numRead_;
};
#endif
