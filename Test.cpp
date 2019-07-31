// CHECK_OK(actual) check_ok([&](){actual;}, __FILE__+string(":")+to_string(__LINE__))
// CHECK_THROWS(actual) check_throws([&](){actual;}, __FILE__+string(":")+to_string(__LINE__))
// CHECK_EQUAL(actual,expected) check_equal([&](){return actual;}, expected, __FILE__+string(":")+to_string(__LINE__))
// CHECK_OUTPUT(actual,expected) check_equal([&](){ostringstream ostr; ostr<<"'"<<actual<<"'"; return ostr.str();}, "'"+string(expected)+"'", __FILE__+string(":")+to_string(__LINE__))
// CHECK_INPUT(actual,expected) check_input(actual


#include <iostream>
#include <string>
#include "chain.hpp"
#include "powerset.hpp"
#include "product.hpp"
#include "range.hpp"
#include "zip.hpp"
#include "badkan.hpp"
using namespace std;
using namespace itertools;
// TODO: implement tests using the badkan.hpp

int main()
{
    badkan::TestCase testcase;
    int grade = 0;
    int signal = setjmp(badkan::longjmp_buffer);

    if (signal == 0)
    {

        //          ~~~~~~~~~ TEST RANGE ~~~~~~~~~
        std::ostringstream intRange, charRange1, doubleRange1, doubleRange2, charRange2;
        for (char c : range('A', 'D'))
            charRange1 << c;
        for (char c : range('a', 'g'))
            charRange2 << c;
        for (int i : range(20, 22))
            intRange << i << ",";
        for (double d : range(3.5, 5.5))
            doubleRange1 << d << ",";
        for (double d : range(3.2, 9.2)) // WHAT SHOULD IT PRINT ??
            doubleRange2 << d << ",";

        testcase.setname("Test range")
            .CHECK_OUTPUT(charRange1.str(), "ABC")
            .CHECK_OUTPUT(charRange2.str(), "abcdef")
            .CHECK_OUTPUT(intRange.str(), "20,21,")
            .CHECK_OUTPUT(doubleRange1.str(), "3.5,4.5,")
            .CHECK_OUTPUT(doubleRange2.str(), "3.2,4.2,5.2,6.2,7.2,8.2,");

        //          ~~~~~~~~~ TEST CHAIN ~~~~~~~~~
        // MARK : can you chain string\char to double\int ?
        std::ostringstream charChain, doubleChain, intChain, str_charChain, double_intChain;
        for (char c : chain(range('A', 'D'), range('a', 'b')))
            charChain << c;
        for (char c : chain(range('a', 'g'), string("HelloWorld")))
            str_charChain << c;
        for (int i : chain(range(20, 22), range(40, 43)))
            intChain << i << ",";
        for (double d : chain(range(3.5, 5.5), range(7.3, 10.3)))
            doubleChain << d << ",";
        for (auto d : chain(range(3.2, 9.2), range(10, 13))) //WHAT SHOULD IT PRINT ??
            double_intChain << d << ",";

        testcase.setname("Test chain")
            .CHECK_OUTPUT(charChain.str(), "ABCa")
            .CHECK_OUTPUT(str_charChain.str(), "abcdefHelloWorld")
            .CHECK_OUTPUT(intChain.str(), "20,21,40,41,42,")
            .CHECK_OUTPUT(doubleChain.str(), "3.5,4.5,7.3,8.3,9.3,")
            .CHECK_OUTPUT(double_intChain.str(), "3.2,4.2,5.2,6.2,7.2,8.2,10,11,12,") //VALID TEST??
            ;

        //          ~~~~~~~~~ TEST PRODUCT ~~~~~~~~~

        std::ostringstream intProduct, doubleProduct, str_doubleProduct, str_intProduct, int_charProduct;

        for (auto p : product(range(3, 5), range(6, 8)))
            intProduct << p << " ";

        for (auto p : product(range(1.2, 3.2), range(3.2, 5.2)))
            doubleProduct << p << " ";

        for (auto p : product(range('a', 'c'), range(1.3, 2.3)))
            str_doubleProduct << p << " ";

        for (auto p : product(range('a', 'c'), range(1, 3)))
            str_intProduct << p << " ";

        for (auto p : product(range(1, 3), range('a', 'c')))
            int_charProduct << p << " ";

        testcase.setname("Test product")
            .CHECK_OUTPUT(intProduct.str(), "3,6 3,7 4,6 4,7 ")
            .CHECK_OUTPUT(doubleProduct.str(), "1.2,3.2 1.2,4.2 2.2,3.2 2.2,4.2 ")
            .CHECK_OUTPUT(str_doubleProduct.str(), "a,1.3 b,1.3 ")
            .CHECK_OUTPUT(str_intProduct.str(), "a,1 a,2 b,1 b,2 ")
            .CHECK_OUTPUT(int_charProduct.str(), "1,a 1,b 2,a 2,b ");

        //          ~~~~~~~~~ TEST POWERSET ~~~~~~~~~
        std::ostringstream stringPowerset, intPowerset, doublePowerset, chainPowerset_1,charPowerset;

        for (auto s : powerset(string("snir")))
        stringPowerset << s << " ";

        for (auto s : powerset(range(1, 3)))
            intPowerset << s << " ";
        for(auto s : powerset(range(1.3,3.3)))
            doublePowerset<<s<<" ";
        for(auto s : powerset(range('a','c')))
            charPowerset<<s<<" ";    
        for(auto s : powerset(chain(range('a','b'),range('b','d'))))
            chainPowerset_1<<s<<" "; 

        testcase.setname("Test powerset")
            .CHECK_OUTPUT(stringPowerset.str(), "{} {s} {n} {s,n} {i} {s,i} {n,i} {s,n,i} {r} {s,r} {n,r} {s,n,r} {i,r} {s,i,r} {n,i,r} {s,n,i,r} ")
            .CHECK_OUTPUT(intPowerset.str(), "{} {1} {2} {1,2} ")
            .CHECK_OUTPUT(doublePowerset.str(), "{} {1.3} {2.3} {1.3,2.3} ")
            .CHECK_OUTPUT(chainPowerset_1.str(), "{} {a} {b} {a,b} {c} {a,c} {b,c} {a,b,c} ")
            .CHECK_OUTPUT(charPowerset.str(), "{} {a} {b} {a,b} ");

        //          ~~~~~~~~~ TEST ZIP ~~~~~~~~~

        std::ostringstream intZip, doubleZip, charZip, str_doubleZip, str_strZip;
        for (auto p : zip(range(1, 3), range(1, 3)))
            intZip << p << " ";

        for (auto p : zip(range(1.2, 4.2), range(2.2, 5.2)))
            doubleZip << p << " ";

        for (auto p : zip(range('a', 'c'), range('c', 'e')))
            charZip << p << " ";

        for (auto p : zip(range('a', 'c'), range(1.2, 3.2)))
            str_doubleZip << p << " ";

        for (auto p : zip(string("hey"), string("hey")))
            str_strZip << p << " ";

        testcase.setname("Test zip")
            .CHECK_OUTPUT(intZip.str(), "1,1 2,2 ")
            .CHECK_OUTPUT(doubleZip.str(), "1.2,2.2 2.2,3.2 3.2,4.2 ")
            .CHECK_OUTPUT(charZip.str(), "a,c b,d ")
            .CHECK_OUTPUT(str_doubleZip.str(), "a,1.2 b,2.2 ")
            .CHECK_OUTPUT(str_strZip.str(), "h,h e,e y,y ");


        // //         ~~~~~~~~~ MIXED TESTS ~~~~~~~~~
        std::ostringstream mixed_0,mixed_1,mixed_2,mixed_3,mixed_4,mixed_5,mixed_6,mixed_7,mixed_8,mixed_9;


        //COMBINATIONS : ZIP && PRODUCT
        for(auto s : product(zip(range(1,3),range(5,7)),zip(range(11,13),range(15,17)))) //(1,5 2,7) (11,15 13,16) 
            mixed_0<<s<<" "; 

        //COMBINATIONS :  PRODUCT &&  CHAIN   
        for(auto s : product(chain(range(3,4),range(8,9)),chain(range(11,12),range(15,16)))) //(3,8) (11,15)
            mixed_1<<s<<" ";

        //COMBINATIONS :  POWERSET && CHAIN   
        for(auto s : powerset(chain(range(1,2),range(1,2)))) // (1,1)
            mixed_2<<s<<" ";

        //COMBINATIONS : POWERSET && CHAIN && PRODUCT   
        for(auto s : powerset(product(chain(range(3,4),range(8,9)),chain(range(11,12),range(15,16)))))
            mixed_3<<s<<" ";

        //COMBINATIONS : POWERSET && PRODUCT   
        for(auto s : powerset(product(range('a','c'),range('e','f')))) //(a ,b , e )
            mixed_4<<s<<" "; 

        //COMBINATIONS :  POWERSET && ZIP  
        for(auto s : powerset(zip(range(1,3),range(2,4)))) // (1,2) (2,3)
            mixed_5<<s<<" "; 

        //COMBINATIONS : ZIP && CHAIN   
        for(auto s : zip(chain(range(1,2),range(2,3)),chain(range(3,4),range(4,5))))// (1,3) (2,4)--> (1,3 2,4)
            mixed_6<<s<<" "; 

        //COMBINATIONS : POWERSET && ZIP && CHAIN    
        for(auto s : powerset(zip(chain(range(1,2),range(2,3)),chain(range(3,4),range(4,5)))))
            mixed_7<<s<<" "; 

        // //COMBINATIONS :    
        // for(auto s : )
        //     mixed_8<<s;

        // //COMBINATIONS :    
        // for(auto s : )
        //     mixed_9<<s; 

        testcase.setname("mixed tests")
            .CHECK_OUTPUT(mixed_0.str(),"1,5,11,15 1,5,12,16 2,6,11,15 2,6,12,16 ")
            .CHECK_OUTPUT(mixed_1.str(),"3,11 3,15 8,11 8,15 ") 
            .CHECK_OUTPUT(mixed_2.str(),"{} {1} {1} {1,1} ")
            .CHECK_OUTPUT(mixed_3.str(),"{} {3,11} {3,15} {3,11,3,15} {8,11} {3,11,8,11} {3,15,8,11} {3,11,3,15,8,11} {8,15} {3,11,8,15} {3,15,8,15} {3,11,3,15,8,15} {8,11,8,15} {3,11,8,11,8,15} {3,15,8,11,8,15} {3,11,3,15,8,11,8,15} ")
            .CHECK_OUTPUT(mixed_4.str(),"{} {a,e} {b,e} {a,e,b,e} ") 
            .CHECK_OUTPUT(mixed_5.str(),"{} {1,2} {2,3} {1,2,2,3} ")
            .CHECK_OUTPUT(mixed_6.str(),"1,3 2,4 ")
            .CHECK_OUTPUT(mixed_7.str(),"{} {1,3} {2,4} {1,3,2,4} ")
            // .CHECK_OUTPUT(mixed_8.str(),"")
            // .CHECK_OUTPUT(mixed_9.str(),"")
            ;

        grade = testcase.grade();
    }
    else
    {
        testcase.print_signal(signal);
        grade = 0;
    }

    cout << "Your grade is: " << grade << endl;
    return 0;
}
