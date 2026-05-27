// Student_info.h
#progma once

#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <iostream>
#include <vector>
#include <string>
#include "Core.h"
#include "Grad.h"

using namespace std;

class Student_info {
private:
        Core* cp;

public: 
        Student_info() : cp(0) { }
        Student_info(istream& is) : cp(0) {read(is); }

        string getName() const { return cp->getName(); }
        void setName(string n) { cp->setName(n); }

        double getMidterm() const { return cp->getMidterm(); }
        double getFinal() const { return cp->getFinal(); }
        vector<double> getHw() const { return cp->getHW(); }

        // bool valid() const { return !homework.empty(); }

        istream& read(istream&);
        double grade() const {
                if (cp) return cp->grade();
                else throw runtime_error("Uninitialized Student!");
        }
};

static bool compare(const Student_info& x, const Student_info& y) {
        return x.getName() < y.getName();
}

#endif
