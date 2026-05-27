#progma once
// Vec.h 
#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <memory>
#include <algorithm>
#include <cstddef> // ptrdiff_t

using namespace std; 

template <class T> class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference; // const &

    /*
    Vec<int> grades;
    Vec<int> pass;
    pass = grades;
    1. operator=
    2. Vec()
    */

    Vec() { create(); }
    explicit Vec (size_type n, const T& val = T()) { create(n, val); }
    Vec (const Vec& v ) {create ( v.begin(), v.end()); };

    size_type size() const { return avail - data; }
    T& operator[](size_type i) {return data[i]; }
    const T& operator[](size_type i) const {return data[i]; }

    Vec& operator=(const Vec&);

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    template<class In> iterator insert(iterator, In, In);
    void assign(itertor, iterator);

    void push_back(const T val) {
        if (avail == limit )
            grow();

        unchecked_append(val);
    }

    void push_back_grow_once(const T& t) {
        grow_once();
        unchecked_append(t);
    }

    Vec();
    Vec(T data);

    ~Vec() { uncreate(); };
    void clear() { uncreate(); };
    bool empty() const {return data == avail; } // 0 == 0? True

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void grow_once();
    void unchecked_append(const T&);
};


template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    // int i = 0;
    // lhs = left-hand side (i) 
    // rhs = right-hand side (0)
    if (&rhs != this) {
        uncreate();

        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> void Vec<T>::create() {
    data = avail = limit = 0;
}

template <class T> 
void Vec<T>::create(size_type n, const T& val) {
    data = alloc.allocate(); // #include<memory>
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_fill(i, j, data);
}

template <class T>
void Vec<T>::uncreate() {
    if (data) {
        iterator it = avail;
        while ( it != data)
            alloc.destroy(--it);

        alloc.deallocate(data, limit - data);
    }

    data = limit = avail = 0;
}

template <class T>
void Vec<T>::unckecked_append(const T& val) {
    alloc.construct(avail++, val);
}

template <class T>
void vec<T>::grow() {
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

uncreate();

data = new_data;
avail = new_avail;
limit = data + new_size;
}

template <class T>
void vec<T>::grow_once() {
    size_type new_size = limit - data + ptrdiff_t(1);

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

uncreate();

data = new_data;
avail = new_avail;
limit = data + new_size;
}

template<class T>
template<class In>
typename Vec<t>::iterator Vec<T>::insert(iterator d, In b, In e) {
    Vec<T> end(d, avail);
    ptrdiff_t diff = d - data;

    if (d) {
        while(avail != d)
            alloc.destroy(--avail);
    }

    while (b != e)
        push_back(*b++);

    for (Vec<T>::const_iterator it = end.begin();
        it != end.end(); ++it)
        push_back(*it);

    return data + diff;
}

template<class T> 
void Vec<T>::assign(iterator b, iterator e) {
    uncreate();

    while ( b != e)
        push_back(*b++);
}

#endif