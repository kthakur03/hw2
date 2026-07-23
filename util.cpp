#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> words;
    string current;
    for(size_t i = 0; i <= rawWords.size(); ++i) {
        if(i < rawWords.size() && isalnum(static_cast<unsigned char>(rawWords[i]))) {
            current += static_cast<char>(tolower(static_cast<unsigned char>(rawWords[i])));
        }
        else {
            if(current.size() >= 2) words.insert(current);
            current.clear();
        }
    }
    return words;
}

std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
std::string &trim(std::string &s) { return ltrim(rtrim(s)); }
