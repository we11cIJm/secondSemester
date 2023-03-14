#pragma once
#ifndef RATIONAL
#define RATIONAL

#include <iosfwd>
#include <cstdint>

class Rational
{
public:
    Rational();
    Rational(int32_t rhs);
    Rational(const int32_t lhs, const int32_t rhs);
    Rational(const Rational& rhs);

    int32_t Nod(int32_t lhs, int32_t rhs);
    void Reduce();
    // int32_t ToInt();
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    int32_t & GetNum() { return num; }
    int32_t & GetDen() { return den; }

    static const char separator{ '/' };

    std::ostream& WriteTo(std::ostream& ostrm) const;
    std::istream& ReadFrom(std::istream& istrm);

    ~Rational() = default;

private:
    int32_t num{0};
    int32_t den{1};
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational& lhs, const int32_t rhs);
Rational operator+(const int32_t lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const int32_t rhs);
Rational operator-(const int32_t lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const int32_t rhs);
Rational operator*(const int32_t lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const int32_t rhs);
Rational operator/(const int32_t lhs, const Rational& rhs);

bool operator==(Rational lhs, const Rational& rhs);
bool operator!=(Rational lhs, const Rational& rhs);
bool operator>(Rational lhs, const Rational& rhs);
bool operator>=(Rational lhs, const Rational& rhs);
bool operator<(const Rational& lhs, Rational rhs);
bool operator<=(const Rational& lhs, Rational rhs);

#endif
