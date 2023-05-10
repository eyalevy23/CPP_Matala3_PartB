#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>
#include<iostream>
#include<vector>
#include <algorithm>
#include <climits>

namespace ariel{};

class Fraction{
    private:
        int numerator;
        int denominator;

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        void reduction();
        Fraction (float num);

        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int numerator);
        void setDenominator(int denominator);

        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

        Fraction operator+(float num);
        Fraction operator-(float num);
        Fraction operator*(float num);
        Fraction operator/(float num);
        
        bool operator==(float num);
        bool operator<(float num);
        bool operator>(float num);
        bool operator<=(float num);
        bool operator>=(float num);
        
        
        
        Fraction &operator++();
        Fraction operator++(int);
        Fraction &operator--();
        Fraction operator--(int);

        bool operator==(const Fraction& other) const;
        bool operator<(const Fraction& other) const;
        bool operator>(const Fraction& other) const;
        bool operator<=(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;

        friend std::ostream& operator<<(std::ostream& stream, const Fraction& fraction);
        friend std::istream& operator>>(std::istream& stream, Fraction& fraction);

        //freind 
        friend Fraction operator+(float num, const Fraction& other);
        friend Fraction operator-(float num, const Fraction& other);
        friend Fraction operator*(float num, const Fraction& other);
        friend Fraction operator/(float num, const Fraction& other);

        friend bool operator==(float num, const Fraction& other);
        friend bool operator<(float num, const Fraction& other);
        friend bool operator>(float num, const Fraction& other);
        friend bool operator<=(float num, const Fraction& other);
        friend bool operator>=(float num, const Fraction& other);
    
};

#endif