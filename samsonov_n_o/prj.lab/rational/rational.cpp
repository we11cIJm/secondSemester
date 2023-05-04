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

Rational::Rational() : num_(0), den_(1) {} /* default ctor */
Rational::Rational(const int32_t rhs) : num_(rhs), den_(1) {} // int to rational
Rational::Rational(const int32_t lhs, const int32_t rhs) // : num_(lhs), den_(rhs)
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
        num_ = -lhs;
        den_ = -rhs;
        Reduce();
    }   
    else {
        num_ = lhs;
        den_ = rhs;
        Reduce();
    }
}
Rational::Rational(const Rational& rhs)
    : num_(rhs.num_), den_(rhs.den_) // copy constructor
{}

Rational::Rational(Rational&& rat)
    : num_(std::move(rat.num_))
    , den_(std::move(rat.den_))
{}

Rational& Rational::operator=(const Rational& rhs) {
	num_ = rhs.num_;
	den_ = rhs.den_;
	return *this;
}

Rational& Rational::operator=(Rational&& rhs) {
    if (this != &rhs) {
        num_ = std::move(rhs.num_);
        den_ = std::move(rhs.den_);
    }
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
    int32_t r = Nod(std::abs(num_), den_);
    num_ /= r;
    den_ /= r;
}

Rational Rational::operator-() {
	Rational newR(*this);
	newR.num_ = -num_;
	return newR;
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num_ = rhs.den_ * num_ + rhs.num_ * den_;
    den_ *= rhs.den_;
    Reduce();
    return *this;
}
Rational& Rational::operator+=(const int32_t& rhs)
{
    Rational tmp(rhs);
    num_ = tmp.den_ * num_ + tmp.num_ * den_;
    den_ *= tmp.den_;
    Reduce();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs)
{
    num_ = rhs.den_ * num_ - rhs.num_ * den_;
    den_ *= rhs.den_;
    Reduce();
    return *this;
}
Rational& Rational::operator-=(const int32_t& rhs)
{
    Rational tmp(rhs);
    num_ = tmp.den_ * num_ - tmp.num_ * den_;
    den_ *= tmp.den_;
    Reduce();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs)
{
    num_ *= rhs.num_;
    den_ *= rhs.den_;
    Reduce();
    return *this;
}
Rational& Rational::operator*=(const int32_t& rhs)
{
    num_ *= rhs;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs)
{
    if(rhs.num_ == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    num_ *= rhs.den_;
    den_ *= rhs.num_;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const int32_t& rhs)
{
    if(rhs == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    den_ *= rhs;
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
    num_ += den_;
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
    num_ -= den_;
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
    ostrm << num_ << separator << den_;
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
        num_ = numInp;
        den_ = denInp;
        if (isNegative) {
            num_ *= -1;
        }
        Reduce();
    }
    return istrm;
}
