#include "iteroutput.hpp"
#include <cmath>

namespace itertools
{

template <class T>
/*
* _powerset class, using two values to iterate between them.
* the values must be a primitive type or an object, if its an object
* then it must implement the following operators: != (not equal), ++ (prefix increment).
* the _powerset class contains inner iterator.
* Note: calling the powerset(T,T) function instead of the class _powerset is recommended.
*/
class _powerset
{

    // Private variables and methods
private:
    T _from; // starting point

    template <class E>
    // Inner class (iterator)
    class iterator
    {

    public:
        // variables

        const E _element_iterator_begin;
        const E _element_iterator_end;
        unsigned int index;
        unsigned int num_of_elements;

        //constructor
        iterator(E element_it_begin, E element_it_end) : _element_iterator_begin(element_it_begin),
                                                         _element_iterator_end(element_it_end),
                                                         index(0),
                                                         num_of_elements(0)
        {
            E _element_iterator = _element_iterator_begin;
            while (_element_iterator != _element_iterator_end)
            {
                ++num_of_elements;
                ++_element_iterator;
            }

            num_of_elements = std::pow(2, num_of_elements);
        }

        // operators
        bool operator!=(_powerset::iterator<E> const &other) const
        {
            return ((num_of_elements - index) != (other.num_of_elements - other.index - 1));
        }

        auto operator*() const
        {
            E _element_iterator = _element_iterator_begin;
            std::vector<typename std::remove_const<typename std::remove_reference<decltype(*_element_iterator_begin)>::type>::type> S;
           
            unsigned int i = index;
            while (i != 0 && _element_iterator != _element_iterator_end)
            { // convert to binary, each '1' digit is an index of an element.
                unsigned int r = i % 2;
                i = i >> 1; //divide by 2.

                if (r == 1)
                    S.emplace_back(*_element_iterator);

                ++_element_iterator;
            }

            return S;
        }

        _powerset::iterator<E> &operator++()
        {
            ++index;
            return *this;
        }
    };

public:
    _powerset(const T from) : _from(from) {}  // constructor
    auto begin() const { return _powerset::iterator<decltype(_from.begin())>(_from.begin(), _from.end()); } // iteratable object
    auto end() const { return _powerset::iterator<decltype(_from.begin())>(_from.end(), _from.end()); }  // iteratable object
};                                                                                                                                                  // class

template <typename T>
/*
* powerset function, use in loops to iterate between two values.
* Example use case: 
* for(int i : powerset(1,5))
*   // do somethin...
*/
_powerset<T> powerset(T from)
{
    return _powerset<T>(from);
}

} // namespace itertools