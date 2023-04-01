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

std::istream& Rational::ReadFrom(std::istream& istrm)
{
    int32_t numInp(0);
    char sep{'/'};
    int32_t denInp(1);
    try {
        istrm >> numInp >> sep >> denInp;
        std::cout << "numInp = " << numInp << ", sep = " << sep << ", denInp = " << denInp << std::endl;
        if(istrm.good())
        {
            if(sep == separator) //  && sep != enter
            {
                if(denInp <= 0)
                {
                    throw std::invalid_argument("expected positive denominator");
                }
                num = numInp;
                den = denInp;
                Reduce();
                std::cout << "num = " << num << ", den = " << den << std::endl;
            } else {
                throw std::invalid_argument("Incorrect input");
            }
        } else {
            istrm.setstate(std::ios_base::badbit);
        }
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
    } catch (...) {
        std::cerr << "smth went wrong\n";
    }
    return istrm;
}


/* mine */
// std::istream& Rational::ReadFrom(std::istream& istrm)
// {
//     int32_t numInp(0);
//     char sep{'/'};
//     int32_t denInp(1);
//     try {
//         istrm >> numInp >> sep >> denInp;
//         if(istrm.good())
//         {
//             if(sep == separator) //  && sep != enter
//             {
//                 if(denInp <= 0)
//                 {
//                     throw std::invalid_argument("expected positive denominator");
//                 }
//                 // if(denInp < 0) {
//                 //     istrm.setstate(std::ios_base::badbit);
//                 //     return istrm;
//                 // }
//                 num = numInp;
//                 den = denInp;
//                 Reduce();
//                 // ToInt();
//             } else {
//                 throw std::invalid_argument("Incorrect input");
//             }
//         } else {
//             istrm.setstate(std::ios_base::badbit);
//         }
//     } catch (const std::exception& ex) {
//         std::cerr << ex.what() << '\n';
//     } catch (...) {
//         std::cerr << "smth went wrong\n";
//     }
//     return istrm;
// }

// std::istream& Rational::ReadFrom(std::istream& istrm)
// {
//     int32_t numInp(0);
//     char sep{'/'};
//     int32_t denInp(1);
//     try {
//         istrm >> numInp >> sep >> denInp;
//         if (istrm.good() && sep == separator && denInp > 0) {
//             num = numInp;
//             den = denInp;
//             Reduce();
//         } else {
//             istrm.clear();
//             istrm.setstate(std::ios_base::badbit);
//         }
//     } catch (...) {
//         istrm.clear();
//         istrm.setstate(std::ios_base::badbit);
//     }
//     return istrm;
// }

// std::istream& Rational::ReadFrom(std::istream& istrm)
// {
//     int32_t numerator;
//     int32_t denominator;
//     char separator;

//     istrm >> numerator >> separator >> denominator;

//     if (istrm.good() && separator == '/') {
//         num = numerator;
//         den = denominator;
//         Reduce();
//     } else {
//         // Set failbit if input is invalid
//         istrm.setstate(std::ios_base::failbit);
//     }

//     return istrm;
// }

/*std::istream& Rational::ReadFrom(std::istream& istrm) {
    int32_t numInp(0);
    char sep{'/'};
    int32_t denInp(1);
    try {
        istrm >> numInp >> sep >> denInp;
        if (istrm.good()) {
            if (sep == separator) {
                if (denInp <= 0) {
                    istrm.setstate(std::ios_base::failbit);
                    return istrm;
                }
                num = numInp;
                den = denInp;
                Reduce();
            } else {
                istrm.setstate(std::ios_base::failbit);
                return istrm;
            }
        } else {
            istrm.setstate(std::ios_base::failbit);
            return istrm;
        }
    } catch (...) {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    return istrm;
}*/

/*std::istream& Rational::ReadFrom(std::istream& istrm) {
    int numerator = 0;
    int denominator = 0;
    char slash = '/';

    istrm >> numerator >> slash >> denominator;
    
    if (istrm.good() && slash == '/') {
        Rational newRational(numerator, denominator);
        istrm.clear();
        istrm.ignore(10000, '\n');
        return istrm;
    } else {
        istrm.setstate(std::ios::failbit);
        return istrm;
    }
}*/