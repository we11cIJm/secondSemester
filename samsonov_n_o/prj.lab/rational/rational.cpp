#include <iostream>
#include <sstream>
#include <rational/rational.hpp>

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.WriteTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.ReadFrom(istrm);
}

Rational::Rational() : num(0), den(1) {} /* default ctor */
Rational::Rational(const int32_t rhs) : num(rhs), den(1) {} // int to rational
Rational::Rational(const int32_t lhs, const int32_t rhs) // : num(lhs), den(rhs)
{
    if(rhs == 0) {
        throw std::overflow_error("division by zero");
        // try {}
        // catch(const std::exception& ex)
        // {
        //     std::cerr << ex.what() << '\n';
        // }
    }
    if(rhs < 0) {
        num = -lhs;
        den = -rhs;
        Reduce();
    }   
    else {
        num = lhs;
        den = rhs;
        Reduce();
    }
}
Rational::Rational(const Rational& rhs) : num(rhs.num), den(rhs.den) {} // copy constructor

Rational& Rational::operator=(const Rational& rhs) {
	num = rhs.num;
	den = rhs.den;
	return *this;
}

int32_t Rational::Nod(int32_t lhs, int32_t rhs) 
{
    int32_t remain = 0;
    while(rhs != 0)
    {
        remain = lhs % rhs;
        lhs = rhs;
        rhs = remain;
    }
    return lhs;
}

void Rational::Reduce()
{
    int32_t r = Nod(std::abs(num), den);
    num /= r;
    den /= r;
}

Rational Rational::operator-() {
	Rational newR(*this);
	newR.num = -num;
	return newR;
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num = rhs.den * num + rhs.num * den;
    den *= rhs.den;
    Reduce();
    return *this;
}
Rational& Rational::operator+=(const int32_t& rhs)
{
    Rational tmp(rhs);
    num = tmp.den * num + tmp.num * den;
    den *= tmp.den;
    Reduce();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs)
{
    num = rhs.den * num - rhs.num * den;
    den *= rhs.den;
    Reduce();
    return *this;
}
Rational& Rational::operator-=(const int32_t& rhs)
{
    Rational tmp(rhs);
    num = tmp.den * num - tmp.num * den;
    den *= tmp.den;
    Reduce();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs)
{
    num *= rhs.num;
    den *= rhs.den;
    Reduce();
    return *this;
}
Rational& Rational::operator*=(const int32_t& rhs)
{
    num *= rhs;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs)
{
    if(rhs.num == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    num *= rhs.den;
    den *= rhs.num;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const int32_t& rhs)
{
    if(rhs == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    den *= rhs;
    Reduce();
    return *this;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() == 0);
}
bool operator==(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() == 0);
}
bool operator==(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() == 0);
}
bool operator!=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() != 0);
}
bool operator!=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() != 0);
}
bool operator!=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() != 0);
}
bool operator>(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() > 0);
}
bool operator>(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() > 0);
}
bool operator>(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() > 0);
}
bool operator>=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() >= 0);
}
bool operator>=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() >= 0);
}
bool operator>=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.GetNum() >= 0);
}
bool operator<(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() > 0);
}
bool operator<(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() > 0);
}
bool operator<(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() > 0);
}
bool operator<=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() >= 0);
}
bool operator<=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() >= 0);
}
bool operator<=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.GetNum() >= 0);
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.Reduce();
    return sum;
}
Rational operator+(const Rational& lhs, const int32_t rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.Reduce();
    return sum;
}
Rational operator+(const int32_t lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.Reduce();
    return sum;
}
Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational dif(lhs);
    dif -= rhs;
    dif.Reduce();
    return dif;
}
Rational operator-(const Rational& lhs, const int32_t rhs)
{
    Rational dif(lhs);
    dif -= rhs;
    dif.Reduce();
    return dif;
}
Rational operator-(const int32_t lhs, const Rational& rhs)
{
    Rational dif(lhs);
    dif -= rhs;
    dif.Reduce();
    return dif;
}
Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational mult(lhs);
    mult *= rhs;
    mult.Reduce();
    return mult;
}
Rational operator*(const Rational& lhs, const int32_t rhs)
{
    Rational mult(lhs);
    mult *= rhs;
    mult.Reduce();
    return mult;
}
Rational operator*(const int32_t lhs, const Rational& rhs)
{
    Rational mult(lhs);
    mult *= rhs;
    mult.Reduce();
    return mult;
}
Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.Reduce();
    return div;
}
Rational operator/(const Rational& lhs, const int32_t rhs)
{
    if(rhs == 0) {
        throw std::invalid_argument("division by zero");
    }
    Rational div(lhs);
    div /= rhs;
    div.Reduce();
    return div;
}
Rational operator/(const int32_t lhs, const Rational& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.Reduce();
    return div;
}

Rational& Rational::operator++()
{
    num += den;
    Reduce();
    return *this;
}
Rational Rational::operator++(int)
{
    Rational oldValue(*this);
    ++(*this);
    return oldValue;
}
Rational& Rational::operator--()
{
    num -= den;
    Reduce();
    return *this;
}
Rational Rational::operator--(int)
{
    Rational oldValue(*this);
    --(*this);
    return oldValue;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const
{
    ostrm << num << separator << den;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm) {
    int32_t numInp(0);
    char sep{'/'};
    int32_t denInp(0);
    char ch{' '};
    bool isNegative(false);  
/*
in the code below:
std::isspace - checking if there's any of whitespaces (eg: ' ', '\t', '\n', etc)
argument - ch (in this case - next character is input stream)

istrm.peek() - function, that can view next ch without getting itself as
an object

istrm.get() - func that getting next character
*/
    while (std::isspace(istrm.peek())) { // start searching for whitespaces
        ch = istrm.get(); // just sorting out characters
    } // whitespaces ended
    if (istrm.peek() == '-') {
        isNegative = true;
        ch = istrm.get();
    }
    while (std::isdigit(istrm.peek())) { // start reading a numenator
        ch = istrm.get();
        numInp *= 10;
        numInp += static_cast<int>(ch - '0');
    }
    if (ch == '-') { // if previous loop wasn't working
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    if (istrm.peek() != sep) { // checking for separator
        istrm.setstate(std::ios_base::failbit);
    }
    ch = istrm.get(); // write a separator
    while (std::isdigit(istrm.peek())) { // start reading a numenator
        ch = istrm.get();
        denInp *= 10;
        denInp += static_cast<int>(ch - '0');
    }
    if (ch == sep) { // what this for?
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    if(istrm.good() || istrm.eof()) {
        if(denInp == 0) {
            istrm.setstate(std::ios_base::failbit);
            return istrm;
        }
        num = numInp;
        den = denInp;
        if (isNegative) {
            num *= -1;
        }
        Reduce();
    }
    return istrm;
}
