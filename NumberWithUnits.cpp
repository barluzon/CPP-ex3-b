#include "NumberWithUnits.hpp"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

namespace ariel{
    static map<string, map<string, double>> convertor;
    const double EPS = 0.0001;

    NumberWithUnits::NumberWithUnits(double val, const string &unit){
       if (convertor.count(unit) == 0){
            throw invalid_argument("Invalid unit");}
        this->value = val;
        this->unit = unit;
    }

    void NumberWithUnits::read_units(ifstream &file){
        double v1=0, v2=0;
        string u1, u2, e;

        while (!(file.eof())){
            file >> v1 >> u1 >> e >> v2 >> u2;
            convertor[u1][u2] = v2;
            convertor[u2][u1] = 1 / v2;
            for (auto &run : convertor[u2]){
                convertor[u1][run.first] = convertor[u1][u2] * run.second;
                convertor[run.first][u1] = 1 / (convertor[u1][u2] * run.second);
            }
            for (auto &run : convertor[u1]){
                convertor[u2][run.first] = convertor[u2][u1] * run.second;
                convertor[run.first][u2] = 1 / (convertor[u2][u1] * run.second);
            }
        }
    }

    double convert(const string &src,const string &dest, double v){
        if (src == dest){
            return v;}
        try{
            return convertor.at(src).at(dest) * v;}
        catch(const exception &exc) {
            throw invalid_argument{"Units do not match - ["+src+"] cannot be converted to ["+dest+"]"};
        }
    }

    NumberWithUnits NumberWithUnits::operator+() const{
        return NumberWithUnits(this->value, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &n) const{
        double n2 = convert(n.unit, this->unit, n.value);
        NumberWithUnits ret(this->value + n2, this->unit);
        return ret;
    }
    NumberWithUnits NumberWithUnits::operator-() const{
        return NumberWithUnits((-1) * this->value, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n) const{
        double n2 = convert(n.unit, this->unit, n.value);
        NumberWithUnits ret(this->value - n2, this->unit);
        return ret;
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n){
        this->value += convert(n.unit, this->unit, n.value);
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n){
        this->value -= convert(n.unit, this->unit, n.value);
        return *this;
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &n) const{
        double n2 = convert(n.unit, this->unit, n.value);
        return (this->value > n2);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &n) const{
        return (this->value < convert(n.unit, this->unit, n.value));
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const{
        return !(*this < n);
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const{
        return !(*this > n);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const{
        return (abs(this->value - convert(n.unit, this->unit, n.value))<=EPS);
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const{
        return !(*this == n);
    }

    NumberWithUnits& NumberWithUnits::operator++(){
        value++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int flag){
        NumberWithUnits ret = *this;
        value++;
        return ret;
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        value--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int flag){
        NumberWithUnits ret = *this;
        value--;
        return ret;
    }

    NumberWithUnits operator*(const NumberWithUnits& n, double a){
        return NumberWithUnits(n.value * a, n.unit);
    }
    NumberWithUnits operator*(double a, const NumberWithUnits& n){
        return n * a;
    }

    ostream& operator<<(std::ostream &out, const NumberWithUnits &n){
        out << n.value << "[" << n.unit << "]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits &n){
        double val = 0;
        string type;
        char  c = ' ';
        in >> val >> c >> type;
        if(type.at(type.length() - 1) != ']'){
            in >> c;}
        else{
            type = type.substr(0, type.length()-1);}
        n = NumberWithUnits(val,type);
        return in;
    }
};