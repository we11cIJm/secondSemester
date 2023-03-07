#pragma once
#ifndef RATIONAL
#define RATIONAL

#include <iosfwd>
#include <cstdint>

class Rational
{
public:
    Rational();
    Rational(const int32_t rhs);
    Rational(const int32_t lhs, const int32_t rhs);
    Rational(const Rational& rhs);

    int32_t NOD(int32_t lhs, int32_t rhs);
    void Reduce();
    Rational& operator+=(const Rational& rhs);
    Rational& operator+=(const int32_t rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator-=(const int32_t rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator*=(const int32_t rhs);
    Rational& operator/=(const Rational& rhs);
    Rational& operator/=(const int32_t rhs);
    bool operator==(const Rational& rhs);
    bool operator!=(const Rational& rhs);
    bool operator>(const Rational& rhs);
    bool operator<(const Rational& rhs);
    bool operator>=(const Rational& rhs);
    bool operator<=(const Rational& rhs);
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);

    // int32_t & getDen(int32_t Den);

    static const char separator{ '/' };

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

#endif
