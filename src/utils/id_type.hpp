#ifndef INCLUDE_ID_TYPE_HPP
#define INCLUDE_ID_TYPE_HPP

template<typename T>
struct id_type
{
    typedef T type;
    T _val;


    id_type(T const& v) :
        _val(v)
    { }


    operator T () const
    {
        return _val;
    }

    operator T& ()
    {
        return _val;
    }

    T& operator = (T const& v)
    {
        _val = v;
        return _val;
    }


    T& operator ++ ()
    {
        return ++_val;
    }

    T operator ++ (int)
    {
        return _val++;
    }
};

#endif // INCLUDE_ID_TYPE_HPP
