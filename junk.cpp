#include "range.hpp"
#include "chain.hpp"
#include "zip.hpp"
#include "product.hpp"
#include "powerset.hpp"
#include <iostream>
#include <string>
#include <utility>

#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl
using namespace itertools;
using std::string, std::pair;

int main() {

    // RANGE
    for(char c : range('A','E'))
        println(c);

    for(char c : range('A','A'))
        println(c);

    for(char c : range(3,3))
        print(c << " ");

    for(int i : range(1,5))
        println(i);

    for(double i : range(1.35,5.35))
        println(i);

    // CHAIN
    for(int i : chain(range(1,3),range(7,11)))
        println(i);

    for(char c : chain(range('A','D'),string("niko")))
        println(c);

    // ZIP
    for (pair<char,char> p : zip(range('A','E'),string("niko")))
        println(p.first << "," << p.second);

    // PRODUCT
    for (pair<char,char> p : product(range('A','E'),string("niko")))
       println(p.first << "," << p.second);

       for (auto i : product(range(1,3), range(5,5)))
        println(i);
    
    // POWERSET


    return 0;
}