/*******************************************************************************
*	    Descriptions - Complex API Functions                                   *
*		Date: 25.01.2021                                                       *
*	    author: Moshe Cohen                                                    *
*	    reviewer: Dor Glaubach                                                      *
*       Group: RD96                                                            * 
*                                                                              *
*******************************************************************************/
#ifndef __ILRD_RD96_COMPLEX_HPP__
#define __ILRD_RD96_COMPLEX_HPP__ 

#include <iostream> // std::ostream, std::istream 

namespace ilrd
{

class Complex
{
public:
    Complex(double real_ = 1, double imag_ = 0): m_real(real_), m_imag(imag_) {} 

    Complex& operator+=(const Complex& rhs_);
    Complex& operator-=(const Complex& rhs_);
    Complex& operator*=(const Complex& rhs_);
    Complex& operator/=(const Complex& rhs_);

    double GetReal() const {return m_real;}
    double GetImag() const {return m_imag;}
    void SetReal(double data_) {m_real = data_;}
    void SetImag(double data_) {m_imag = data_;}  

private:
    double m_real;
    double m_imag;
};


bool operator==(const Complex& lhs_ ,const Complex& rhs_); 
bool IsEqual(const double lhs_, const double rhs_); 
bool operator!=(const Complex& lhs_ ,const Complex& rhs_); 

const Complex operator+(const Complex& lhs_ ,const Complex& rhs_);  // implemented second way - an optimization
const Complex operator-(const Complex& lhs_ ,const Complex& rhs_);  // implemented first way 
const Complex operator*(const Complex& lhs_ ,const Complex& rhs_); 
const Complex operator/(const Complex& lhs_ ,const Complex& rhs_);


std::ostream& operator<<(std::ostream& os_, const Complex& inum_); 
std::istream& operator>>(std::istream& is_, Complex& inum_);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~implementations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline bool operator==(const Complex& lhs_ ,const Complex& rhs_)
{
    return IsEqual(lhs_.GetReal(), rhs_.GetReal()) 
           && IsEqual(lhs_.GetImag(), rhs_.GetImag());
}

inline bool operator!=(const Complex& lhs_ ,const Complex& rhs_)
{
    return !(lhs_ == rhs_);
}

inline const Complex operator+(const Complex& lhs_ ,const Complex& rhs_)
{
    return Complex(lhs_.GetReal(), lhs_.GetImag()) += rhs_;
}

inline const Complex operator-(const Complex& lhs_ ,const Complex& rhs_)
{
    return Complex(lhs_.GetReal() - rhs_.GetReal(),
                  lhs_.GetImag() - rhs_.GetImag());
}

inline const Complex operator*(const Complex& lhs_ ,const Complex& rhs_)
{
    Complex comp;

    comp.SetReal(lhs_.GetReal() * rhs_.GetReal() - lhs_.GetImag() * 
                                                    rhs_.GetImag());
    comp.SetImag(lhs_.GetReal() * rhs_.GetImag() + lhs_.GetImag() * 
                                                    rhs_.GetReal());

    return comp;
}

inline const Complex operator/(const Complex& lhs_ ,const Complex& rhs_)
{
    Complex comp;

    double numerator = lhs_.GetReal() * rhs_.GetReal() + lhs_.GetImag() *
                                                            rhs_.GetImag();
    double denominator = rhs_.GetReal() * rhs_.GetReal() + rhs_.GetImag() * 
                                                            rhs_.GetImag(); 

    comp.SetReal(numerator/denominator);

    numerator = lhs_.GetImag() * rhs_.GetReal() - lhs_.GetReal()   * 
                                                     rhs_.GetImag();
    denominator = rhs_.GetReal() * rhs_.GetReal() + rhs_.GetImag() *   
                                                     rhs_.GetImag();

    comp.SetImag(numerator/denominator);

    return comp;
}

inline std::ostream& operator<<(std::ostream& os_, const Complex& inum_)
{
    return os_ << inum_.GetReal() << " + " << inum_.GetImag() << "i" << std::endl;
}

inline std::istream& operator>>(std::istream& is_, Complex& inum_)
{
    double input = 0;

    std::cout << "Enter Real: "; 
    is_ >> input;
    inum_.SetReal(input); 
    
    std::cout << "Enter Imaginary: "; 
    is_ >> input;
    inum_.SetImag(input); 

    return is_; 
}

inline Complex& Complex:: operator+=(const Complex& rhs_)
{// doesn't make a call to CCtor as '*this + rhs_' does.
    this->m_real += rhs_.GetReal();
    this->m_imag += rhs_.GetImag();

    return *this;
}

inline Complex& Complex:: operator-=(const Complex& rhs_)
{
    *this = *this - rhs_;

    return *this;
}

inline Complex& Complex:: operator*=(const Complex& rhs_)
{
    *this = *this * rhs_;

    return *this;
}

inline Complex& Complex:: operator/=(const Complex& rhs_)
{
    *this = *this / rhs_;

    return *this;
}


//~~~~~~~~~~~~~~~~~~~~~aid functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool IsEqual(const double lhs_ ,const double rhs_)
{
    return (lhs_ - rhs_ < 0.00001) && (rhs_ - lhs_ < 0.00001);
}

} // namespace ilrd

#endif   /*__ILRD_RD96_COMPLEX_HPP__ */
