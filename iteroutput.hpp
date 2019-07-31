#pragma once
#include <iostream>
#include <vector>
#include <utility> // pair


// C++ template to print pair<> 
// class by using template 
template <typename T,typename E>
std::ostream &operator<<(std::ostream &os, const std::pair<T,E>&p)
{
    os << p.first << ',' << p.second;

    return os;
}



// C++ template to print std::set
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &S)
{
    os << "{";

    auto it = S.begin();
    if(it != S.end())
    { // first element is without comma seperator.
        os << *it; 
        ++it;
    }

    while (it != S.end())
    {
        os << ',' << *it;
        ++it;
    }

    os << "}";

    return os;
}

