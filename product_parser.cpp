#include <iostream>
#include <sstream>
#include "product_parser.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
using namespace std;

ProductParser::ProductParser() {}
ProductParser::~ProductParser() {}
Product* ProductParser::parse(string category, istream& is, bool& error, string& errorMsg, int& lineno)
{
    parseCommonProduct(is, error, errorMsg, lineno);
    if(error) return NULL;
    return parseSpecificProduct(category, is, error, errorMsg, lineno);
}
void ProductParser::parseCommonProduct(istream& is, bool& error, string& errorMsg, int& lineno)
{
    string myline;
    getline(is, myline); myline = trim(myline);
    if(myline.size() == 0) { error = true; errorMsg = "Unable to find a product name"; return; }
    prodName_ = myline;
    lineno++; getline(is, myline);
    if(is.fail()) { error = true; errorMsg = "Expected another line with the price"; return; }
    stringstream ss1(myline); ss1 >> price_;
    if(ss1.fail()) { error = true; errorMsg = "Unable to read price"; return; }
    lineno++; getline(is, myline);
    if(is.fail()) { error = true; errorMsg = "Expected another line with the quantity"; return; }
    stringstream ss2(myline); ss2 >> qty_;
    if(ss2.fail()) { error = true; errorMsg = "Unable to read quantity"; return; }
    lineno++;
}
ProductBookParser::ProductBookParser() : ProductParser() {}
Product* ProductBookParser::parseSpecificProduct(string category, istream& is, bool& error, string& errorMsg, int& lineno)
{
    string myline; getline(is, myline); stringstream ss3(myline); ss3 >> isbn_;
    if(ss3.fail()) { error = true; errorMsg = "Unable to read ISBN"; return NULL; }
    lineno++; getline(is, author_);
    if(is.fail()) { error = true; errorMsg = "Unable to read author"; return NULL; }
    lineno++; if(error) return NULL; return makeProduct();
}
string ProductBookParser::categoryID() { return "book"; }
Product* ProductBookParser::makeProduct() { return new Book(prodName_, price_, qty_, isbn_, author_); }

ProductClothingParser::ProductClothingParser() {}
Product* ProductClothingParser::parseSpecificProduct(string category, istream& is, bool& error, string& errorMsg, int& lineno)
{
    string myline; getline(is, myline); stringstream ss3(myline); ss3 >> size_;
    if(ss3.fail()) { error = true; errorMsg = "Unable to read size"; return NULL; }
    lineno++; getline(is, brand_);
    if(is.fail() || brand_.size() == 0) { error = true; errorMsg = "Unable to read brand"; return NULL; }
    lineno++; if(error) return NULL; return makeProduct();
}
string ProductClothingParser::categoryID() { return "clothing"; }
Product* ProductClothingParser::makeProduct() { return new Clothing(prodName_, price_, qty_, size_, brand_); }

ProductMovieParser::ProductMovieParser() {}
Product* ProductMovieParser::parseSpecificProduct(string category, istream& is, bool& error, string& errorMsg, int& lineno)
{
    string myline; getline(is, myline); stringstream ss3(myline); ss3 >> genre_;
    if(ss3.fail()) { error = true; errorMsg = "Unable to read genre"; return NULL; }
    lineno++; getline(is, myline); stringstream ss4(myline); ss4 >> rating_;
    if(ss4.fail()) { error = true; errorMsg = "Unable to read rating"; return NULL; }
    lineno++; if(error) return NULL; return makeProduct();
}
string ProductMovieParser::categoryID() { return "movie"; }
Product* ProductMovieParser::makeProduct() { return new Movie(prodName_, price_, qty_, genre_, rating_); }
