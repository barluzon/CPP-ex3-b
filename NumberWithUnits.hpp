#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
namespace ariel{
    class NumberWithUnits{
            double value;
            string unit;  
    
        public:
        NumberWithUnits(double val , const string &unit);
        static void read_units(std::ifstream &file);

        NumberWithUnits operator+() const;
        NumberWithUnits operator+(const NumberWithUnits &n) const;
        NumberWithUnits operator-() const;
        NumberWithUnits operator-(const NumberWithUnits &n) const;
        NumberWithUnits& operator+=(const NumberWithUnits &n);
        NumberWithUnits& operator-=(const NumberWithUnits &n);

        NumberWithUnits& operator++();
        NumberWithUnits operator++(int flag);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int flag);

        bool operator>(const NumberWithUnits &n) const;
        bool operator<(const NumberWithUnits &n) const;
        bool operator>=(const NumberWithUnits &n) const;
        bool operator<=(const NumberWithUnits &n) const;
        bool operator==(const NumberWithUnits &n) const;
        bool operator!=(const NumberWithUnits &n) const;

        friend NumberWithUnits operator*(const NumberWithUnits& n, double a);
        friend NumberWithUnits operator*(double a, const NumberWithUnits& n);

        friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &n);
        friend std::istream &operator>>(std::istream &in, NumberWithUnits &n);
    };
}