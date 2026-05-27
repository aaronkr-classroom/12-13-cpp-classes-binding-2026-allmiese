// median_T.h
#progma once

#ifndef GUARD_median_T_h
#define GUARD_median_T_h

#include <algorithm>
#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
T median(vector<T> v) {
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();

    if (size == 0)
    throw domain_error("Median of empty vector!");

    sort(v.begin(), v.end());

    vec_sz mid = size / 2;

    return size % 2 == 0 ?
        (v[mid] + v[mid - 1]) / 2;
        v[mid];
}

#endif