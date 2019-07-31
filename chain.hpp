
namespace itertools
{

template <class T, class E>
/*
* _chain class, using two iteratables to iterate over them.
* the values given to the constructor must be a iteratable objects (implementing begin() and end() functions).
* and an iterator (ofcourse) which implements the following operators: != (not equal), ++ (prefix increment).
* the _chain class contains inner iterator.
* Note: calling the chain(T,E) function instead of the class _chain is recommended.
*/
class _chain
{
    // Private variables and methods
private:
    const T& _iteratable_A;    // first iteratable - should be an iteratable
    const E& _iteratable_B;    // second iteratable - should be an iteratable

    // Inner class (iterator)
    template <typename U, typename V>
    class iterator
    {
    public:
        // variables
        U _iterator_A; //  should be an iterator
        V _iterator_B; //  should be an iterator

        bool iterateA;

        //constructor
        iterator(U iteratable_A, V iteratable_B) : _iterator_A(iteratable_A), _iterator_B(iteratable_B), iterateA(true) {}

        // operators
        bool operator!=(_chain::iterator<U,V> const &other) 
        {
            if (iterateA && !(_iterator_A != (other._iterator_A))) // if reached the end of the first iterator.
            // switch to the other iterator by setting the flag "iterateA" to false.
                iterateA = false;

            if(iterateA)
                return (_iterator_A != (other._iterator_A));
            else 
                return (_iterator_B != (other._iterator_B));

            
        }

        decltype(*_iterator_A) operator*() const
        {
            if(iterateA)
                return *_iterator_A;
            else
                return *_iterator_B;
        }

        _chain::iterator<U,V> &operator++()
        {
            if(iterateA)
                ++_iterator_A;
            else 
                ++_iterator_B;
            
            return *this;
        }
    };

public:
    _chain(const T& from, const E& to) : _iteratable_A(from), _iteratable_B(to) {} // constructor

    auto begin() const{ 
        return  _chain::iterator<decltype(_iteratable_A.begin()),decltype(_iteratable_B.begin())>(_iteratable_A.begin(), _iteratable_B.begin()); }  // iteratable object

    auto end() const {
        return _chain::iterator<decltype(_iteratable_A.end()),decltype(_iteratable_B.end())>(_iteratable_A.end(), _iteratable_B.end()); }  // iteratable object  
};  // class

template <typename T, typename E>
/*
* chain function, use in loops to iterate over two iteratables.
* Example use case: 
* for(int i : chain(range('A','D'), string("NIKOLAI")))
*   // do somethin...
*/
_chain<T, E> chain(const T& first, const E& second)
{
    return _chain<T, E>(first, second);
}

} // namespace itertools