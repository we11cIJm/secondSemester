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

int32_t Rational::Nod(int32_t lhs, int32_t rhs) // here: lhs - numenator, rhs - denomenator, return Nod
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

// int32_t Rational::ToInt() {
//     // if(den == 1) {
//     //     int32_t Int = num;
//     //     (*this) = Int;
//     // }
//     // return *this;
//     // return static_cast<double>(*this);
//     if(den == 1) {
//         double tmp = 
//     }
// }

Rational& Rational::operator+=(const Rational& rhs)
{
    num = rhs.den * num + rhs.num * den;
    den *= rhs.den;
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
Rational& Rational::operator*=(const Rational& rhs)
{
    num *= rhs.num;
    den *= rhs.den;
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

bool operator==(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.GetNum() == 0);
}
bool operator!=(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.GetNum() != 0);
}
bool operator>(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.GetNum() > 0);
}
bool operator>=(Rational lhs, const Rational& rhs)
{
    lhs -= rhs;
    return (lhs.GetNum() >= 0);
}
bool operator<(const Rational& lhs, Rational rhs)
{
    rhs -= lhs;
    return (rhs.GetNum() > 0);
}
bool operator<=(const Rational& lhs, Rational rhs)
{
    rhs -= lhs;
    return (rhs.GetNum() >= 0);
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
    // if(den < 0) {
    //     // ToInt();
    //     ostrm << -num << separator << -den;
    // }
    // else {
    //     // ToInt();
    //     ostrm << num << separator << den;
    // }
    ostrm << num << separator << den;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm)
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
                throw std::invalid_argument("expected positive denominator");
            }
            num = numInp;
            den = denInp;
            Reduce();
            // ToInt();
        }
        else
        {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}

