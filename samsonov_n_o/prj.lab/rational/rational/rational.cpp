#include <iostream>
#include <sstream>
#include <rational/rational.hpp>

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.writeTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.readFrom(istrm);
}

Rational::Rational() : num(0), den(1) {} // default constructor
Rational::Rational(int32_t rhs) : num(rhs), den(1) {} // int to rational
Rational::Rational(const int32_t lhs, const int32_t rhs) // : num(lhs), den(rhs)
{   
    if(rhs == 0) {
        throw std::overflow_error("Warning: division by zero");
        try {}
        catch(const std::exception& ex)
        {
            std::cerr << ex.what() << '\n';
        }
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

int32_t Rational::NOD(int32_t lhs, int32_t rhs) // here: lhs - numenator, rhs - denomenator, return NOD
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
    int32_t r = NOD(std::abs(num), den);
    num /= r;
    den /= r;
}

// int32_t & Rational::getDen(int32_t Den)
// {
//     return den;
// }

Rational& Rational::operator+=(const Rational& rhs)
{
    num = rhs.den * num + rhs.num * den;
    den *= rhs.den;
    Reduce();
    return *this;
}
Rational& Rational::operator+=(const int32_t rhs)
{
    num += rhs * den;
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
Rational& Rational::operator-=(const int32_t rhs)
{
    num -= rhs * den;
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
Rational& Rational::operator*=(const int32_t rhs)
{
    num *= rhs;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs)
{
    if(rhs.den == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    num *= rhs.den;
    den *= rhs.num;
    Reduce();
    return *this;
}
Rational& Rational::operator/=(const int32_t rhs)
{
    if(rhs == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    den *= rhs;
    Reduce();
    return *this;
}

bool operator==(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.getNum() == 0);
}
bool operator!=(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.getNum() != 0);
}
bool operator>(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.getNum() > 0);
}
bool operator>=(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.getNum() >= 0);
}
bool operator<(const Rational& lhs, Rational rhs)
{
    rhs -= lhs;
    return (rhs.getNum() > 0);
}
bool operator<=(const Rational& lhs, Rational rhs)
{
    rhs -= lhs;
    return (rhs.getNum() >= 0);
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
    Rational div(lhs);
    div *= rhs;
    div.Reduce();
    return div;
}
Rational operator/(const int32_t lhs, const Rational& rhs)
{
    Rational div(lhs);
    div *= lhs;
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
    Rational tmp(*this);
    *this += 1;
    return tmp;
}
Rational& Rational::operator--()
{
    num -= den;
    Reduce();
    return *this;
}
Rational Rational::operator--(int)
{
    Rational tmp(*this);
    *this -= 1;
    return tmp;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
    ostrm << num << separator << den;
    return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm)
{
    int32_t numInp(0);
    char sep{ '/' };
    int32_t denInp(1);
    istrm >> numInp >> sep >> denInp;
    if(istrm.good())
    {
        if(sep == separator)
        {
            if(denInp <= 0)
            {
                throw std::invalid_argument("Expected positive denominator");
            }
            num = numInp;
            den = denInp;
            Reduce();
        }
        else
        {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}