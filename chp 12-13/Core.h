#progma once
// Core.h

#ifndef GUARD_Core_h
#define GUARD_Core_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Core {
private:
        string name;
        friend class Student_info;

protected:
        double midterm, final;
        vector<double> homework;
        istream& read_common(istream&);

        virtual Core* clone() const { return new Core(*this); }

public: 
        Core() : midterm(0), final(0) { };
        Core(istream& is) { read(is); }

        string getName() const { return name; }
        void setName(string n) { name = n; }

        double getMidterm() const { return Midterm; }
        double getFinal() const { return final; }
        vector<double> getHw() const { return homework; }

        bool valid() const { return !homework.empty(); }

        virtual & read(istream&);
        virtual  grade() const;

        virtual ~Core() { }
};

bool compare(const Core&, const Core&);
bool compare_grades(const Core&, const Core&);
bool compare_Core_ptrs(const Core*, const Core*);

#endif
