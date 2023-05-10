#include "Fraction.hpp"
#include <iostream>
#include <climits>
#include <algorithm>
#include <stdexcept>

using namespace ariel;

Fraction::Fraction(){
    this->numerator = 0;
    this->denominator = 1;
}


Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
    if(denominator == 0){
        throw std::invalid_argument("denominator can't be 0");
    }
    this->numerator = numerator;
    this->denominator = denominator;

    // check for negative number
    if (this->denominator < 0 && this->numerator < 0){
        this->denominator *= -1;
        this->numerator *= -1;
    }
    else if(this->denominator < 0 && this->numerator > 0){
        this->denominator *= -1;
        this->numerator *= -1;
    }
    reduction();
};

int Fraction::getNumerator() const{
    return this->numerator;
}

int Fraction::getDenominator() const{
    return this->denominator;
}

void Fraction::setNumerator(int numerator){
    this->numerator = numerator;
}

void Fraction::setDenominator(int denominator){
    if(denominator == 0){
        throw std::runtime_error("denominator can't be 0");
    }
    this->denominator = denominator;
}

bool exceedsIntLimit(long long value) {
    return ((value > INT_MAX) || (value < INT_MIN));
}

Fraction Fraction::operator+(const Fraction& other) const{
    long long newDenominator = (long long)this->denominator * (long long)other.denominator;
    long long newNumerator = ((long long)this->numerator * (long long)other.denominator) + ((long long)other.numerator * (long long)this->denominator);

    // Check if newDenominator or newNumerator exceeds the int limit
    // if (exceedsIntLimit(newDenominator) || exceedsIntLimit(newNumerator)) {
    //     std::overflow_error("Denominator exceeds the int limit");
    // }

    if(newNumerator>INT_MAX || newNumerator < INT_MIN || newDenominator> INT_MAX || newDenominator< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the add will cause overflow");
    }

    return Fraction((int)newNumerator, (int)newDenominator); 
}

Fraction Fraction::operator-(const Fraction& other) const{
    long long newDenominator = (long long)this->denominator * (long long)other.denominator;
    long long newNumerator = ((long long)this->numerator * (long long)other.denominator) - ((long long)other.numerator * (long long)this->denominator);

    // Check if newDenominator or newNumerator exceeds the int limit
    // if (exceedsIntLimit(newDenominator) || exceedsIntLimit(newNumerator)) {
    //     std::overflow_error("Denominator exceeds the int limit");
    // }

    if(newNumerator>INT_MAX || newNumerator < INT_MIN || newDenominator> INT_MAX || newDenominator< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the add will cause overflow");
    }

    return Fraction((int)newNumerator, (int)newDenominator);
}

Fraction Fraction::operator*(const Fraction& other) const{
    long long newDenominator = (long long)this->denominator * (long long)other.denominator;
    long long newNumerator = (long long)this->numerator * (long long)other.numerator;

    // Check if newDenominator or newNumerator exceeds the int limit
    // if (exceedsIntLimit(newDenominator) || exceedsIntLimit(newNumerator)) {
    //     std::overflow_error("Denominator exceeds the int limit");
    // }
    if(newNumerator>INT_MAX || newNumerator < INT_MIN || newDenominator> INT_MAX || newDenominator< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the add will cause overflow");
    }

    return Fraction((int)newNumerator, (int)newDenominator);
}

Fraction Fraction::operator/(const Fraction& other) const{
    long long newDenominator = (long long)this->denominator * (long long)other.numerator;
    long long newNumerator = (long long)this->numerator * (long long)other.denominator;

    if(newDenominator == 0){
        throw std::runtime_error("denominator can't be 0");
    }
    // Check if newDenominator or newNumerator exceeds the int limit
    // if (exceedsIntLimit(newDenominator) || exceedsIntLimit(newNumerator)) {
    //     std::overflow_error("Denominator exceeds the int limit");
    // }

    if(newNumerator>INT_MAX || newNumerator < INT_MIN || newDenominator> INT_MAX || newDenominator< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the add will cause overflow");
    }

    return Fraction((int)newNumerator, (int)newDenominator);
}



//in case of ++Fraction
Fraction &Fraction::operator++(){
    this->numerator += this->denominator;
    if(exceedsIntLimit(this->numerator)){
        std::overflow_error("Numerator exceeds the int limit");
    }
    return *this;
}

//in case of Fraction++
Fraction Fraction::operator++(int){
    Fraction temp = *this;
    this->numerator += this->denominator;
    if(exceedsIntLimit(this->numerator)){
        std::overflow_error("Numerator exceeds the int limit");
    }
    return temp;
    
}

Fraction& Fraction::operator--(){
    this->numerator -= this->denominator;
    if(exceedsIntLimit(this->numerator)){
        std::overflow_error("Numerator exceeds the int limit");
    }
    return *this;
}

Fraction Fraction::operator--(int){
    Fraction temp = *this;
    this->numerator -= this->denominator;
    if(exceedsIntLimit(this->numerator)){
        std::overflow_error("Numerator exceeds the int limit");
    }
    return temp;
}

bool Fraction::operator==(const Fraction& other)const {
    Fraction temp1 = *this;
    Fraction temp2 = other;
    temp1.reduction();
    temp2.reduction();
    bool isNumeratorEqual = (temp1.numerator == temp2.numerator);
    bool isDenominatorEqual = (temp1.denominator == temp2.denominator);
    if(temp1.numerator == 0 && temp2.numerator == 0){
        return true;
    }
    return isNumeratorEqual && isDenominatorEqual;
}

bool Fraction::operator<(const Fraction& other)const {
    double thisFraction = (double)this->numerator / (double)this->denominator;
    double otherFraction = (double)other.numerator / (double)other.denominator;
    return thisFraction < otherFraction;
}

bool Fraction::operator>(const Fraction& other)const {
    double thisFraction = (double)this->numerator / (double)this->denominator;
    double otherFraction = (double)other.numerator / (double)other.denominator;
    return thisFraction > otherFraction;
}

bool Fraction::operator<=(const Fraction& other)const {
    double thisFraction = (double)this->numerator / (double)this->denominator;
    double otherFraction = (double)other.numerator / (double)other.denominator;
    return thisFraction <= otherFraction;
}

bool Fraction::operator>=(const Fraction& other)const {
    double thisFraction = (double)this->numerator / (double)this->denominator;
    double otherFraction = (double)other.numerator / (double)other.denominator;
    return thisFraction >= otherFraction;
}

std::ostream& operator<<(std::ostream& stream, const Fraction& fraction){
    stream << fraction.numerator << "/" << fraction.denominator;
    return stream;
}

std::istream &operator>>(std::istream &stream,Fraction &fraction) { 
    int num;
    int num2;
    if(stream >> num){
        if (stream >> num2){
            fraction.setDenominator(num2);
            if (fraction.getDenominator() < 0 && num < 0){
                fraction.setDenominator(fraction.getDenominator() * (-1));
                fraction.setNumerator(num * (-1));
            }
            else if(num > 0 && fraction.getDenominator() < 0){
            fraction.setDenominator(fraction.getDenominator() * (-1));
            fraction.setNumerator(num * (-1)) ;
            }
            else{
                fraction.setNumerator(num);
            }
        }
        else
        {
        throw std::runtime_error("Invalid input: Expected two integers separated by space");
        }
    }
    else{
        throw std::runtime_error("Invalid input: Expected a number");
    }
    if (fraction.getDenominator() == 0){
        throw std::runtime_error("Denominator can't be zero");
    }
    fraction.reduction();
    return stream;
}

//compare between fraction and float
bool operator==(const Fraction& fraction, const float num){
    Fraction temp = Fraction(num);
    return fraction == temp;

}

bool operator<(const Fraction& fraction, const float num){
    Fraction temp = Fraction(num);
    return fraction < temp;
}

bool operator>(const Fraction& fraction, const float num){
    Fraction temp = Fraction(num);
    return fraction > temp;
}

bool operator<=(const Fraction& fraction, const float num){
    Fraction temp = Fraction(num);
    return fraction <= temp;
}

bool operator>=(const Fraction& fraction, const float num){
    Fraction temp = Fraction(num);
    return fraction >= temp;
}

//compare between float and fraction

bool operator==(const float num, const Fraction& fraction){
    return fraction == num;
}

bool operator<(const float num, const Fraction& fraction){
    return fraction > num;
}

bool operator>(const float num, const Fraction& fraction){
    return fraction < num;
}

bool operator<=(const float num, const Fraction& fraction){
    return fraction >= num;
}

bool operator>=(const float num, const Fraction& fraction){
    return fraction <= num;
}

//friend function
Fraction operator+(const float num, const Fraction& fraction){
    Fraction temp = Fraction(num);
    return temp + fraction;
}

Fraction operator-(const float num, const Fraction& fraction){
    Fraction temp = Fraction(num);
    return temp - fraction;
}

Fraction operator*(const float num, const Fraction& fraction){
    Fraction temp = Fraction(num);
    return temp * fraction;
}

Fraction operator/(const float num, const Fraction& fraction){
    Fraction temp = Fraction(num);
    return temp / fraction;
}


//frection reduction
void Fraction::reduction(){
    int gcdNum = abs(std::__gcd(this->numerator, this->denominator));
    this->numerator /= gcdNum;
    this->denominator /= gcdNum;
}

// float constructor
Fraction::Fraction(float num){
    if(num == 0){
        this->numerator = 0;
        this->denominator = 1;
        return;
    }
    this->numerator = (int)(num * 1000);
    this->denominator = 1000;
    reduction();
}


//friend function
Fraction Fraction::operator+(const float num) {
    Fraction temp = Fraction(num);
    return *this + temp;
}

Fraction Fraction::operator-(const float num) {
    Fraction temp = Fraction(num);
    return *this - temp;
}

Fraction Fraction::operator*(const float num) {
    Fraction temp = Fraction(num);
    return *this * temp;
}

Fraction Fraction::operator/(const float num) {
    Fraction temp = Fraction(num);
    return *this / temp;
}

//compare between fraction and float
bool Fraction::operator==(float num) {
    Fraction temp = Fraction(num);
    return *this == temp;
}

bool Fraction::operator<(float num) {
    Fraction temp = Fraction(num);
    return *this < temp;
}

bool Fraction::operator>(float num) {
    Fraction temp = Fraction(num);
    return *this > temp;
}

bool Fraction::operator<=(float num) {
    Fraction temp = Fraction(num);
    return *this <= temp;
}

bool Fraction::operator>=(float num) {
    Fraction temp = Fraction(num);
    return *this >= temp;
}


