namespace itertools
{


template <class T>
/*
* _range class, using two values to iterate between them.
* the values must be a primitive type or an object, if its an object
* then it must implement the following operators: != (not equal), ++ (prefix increment).
* the _range class contains inner iterator.
* Note: calling the range(T,T) function instead of the class _range is recommended.
*/
class _range
{

// Private variables and methods
private:
    const T _from; // starting point
    const T _to;   // stopping point.

    // Inner class (iterator)
    class iterator
    {

    public:
        // variables
        T val;

        //constructor
        iterator(T vall) : val(vall){}

        // operators
        bool operator!=(_range::iterator const &other) const
        { 
            return val != (other.val);
        }

        T operator*() const
        {
            return val;
        }


        _range::iterator &operator++()
        {
            ++val;
            return *this;
        }
    };

public:
    _range(const T from,const T to) : _from(from), _to(to) {}                      // constructor
    _range::iterator begin() const { return _range::iterator(_from); }  // iteratable object
    _range::iterator end() const { return _range::iterator(_to); }      // iteratable object
}; // class



template <typename T>
/*
* range function, use in loops to iterate between two values.
* Example use case: 
* for(int i : range(1,5))
*   // do somethin...
*/
_range<T> range(T from, T to)
{
    return _range<T>(from, to);
}

} // namespace itertools