#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result;
    typename std::set<T>::iterator it;
    for(it = s1.begin(); it != s1.end(); ++it) {
        if(s2.find(*it) != s2.end()) result.insert(*it);
    }
    return result;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result = s1;
    typename std::set<T>::iterator it;
    for(it = s2.begin(); it != s2.end(); ++it) result.insert(*it);
    return result;
}

std::string convToLower(std::string src);
std::set<std::string> parseStringToWords(std::string line);
std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);
#endif
