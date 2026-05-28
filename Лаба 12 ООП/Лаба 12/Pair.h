#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <iostream>
using namespace std;

class Pair {
    int first;
    double second;
public:
    Pair() { first = 0; second = 0.0; }
    Pair(int f, double s) { first = f; second = s; }
    Pair(const Pair& p) { first = p.first; second = p.second; }
    ~Pair() {}

    int get_first() const { return first; }
    double get_second() const { return second; }
    void set_first(int f) { first = f; }
    void set_second(double s) { second = s; }

    Pair& operator=(const Pair&);
    Pair operator+(const Pair&) const;
    Pair operator/(const int&);
    bool operator>(const Pair&) const;
    bool operator<(const Pair&) const;
    bool operator==(const Pair&) const;
    bool operator!=(const Pair&) const;

    friend istream& operator>>(istream& in, Pair& p);
    friend ostream& operator<<(ostream& out, const Pair& p);
};

Pair& Pair::operator=(const Pair& p) {
    if (&p == this) return *this;
    first = p.first;
    second = p.second;
    return *this;
}

Pair Pair::operator+(const Pair& p) const{
    Pair temp;
    temp.first = first + p.first;
    temp.second = second + p.second;
    return temp;
}

Pair Pair::operator/(const int& n) {
    Pair temp;
    temp.first = first / n;
    temp.second = second / n;
    return temp;
}

bool Pair::operator>(const Pair& p) const {
    if (first > p.first) return true;
    if (first == p.first && second > p.second) return true;
    return false;
}

bool Pair::operator<(const Pair& p) const {
    if (first < p.first) return true;
    if (first == p.first && second < p.second) return true;
    return false;
}

bool Pair::operator==(const Pair& p) const {
    return (first == p.first && second == p.second);
}

bool Pair::operator!=(const Pair& p) const {
    return !(*this == p);
}

istream& operator>>(istream& in, Pair& p) {
    cout << "first (int): "; in >> p.first;
    cout << "second (double): "; in >> p.second;
    return in;
}

ostream& operator<<(ostream& out, const Pair& p) {
    out << p.first << " : " << p.second;
    return out;
}

#endif
