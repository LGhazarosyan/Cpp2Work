#define debugMode 0
#if debugMode==1
#define Log(x) std::cout<<x<<std::endl
#else
#define Log(x)
#endif
#include<iostream>
#include<cassert>
#include<math.h>
class Complex{
private:
 float re_;
 float im_;
public:
 Complex(float=0,float=0);
 Complex(const Complex&);
 Complex(Complex&&);
 ~Complex();
 Complex& operator =(const Complex&);
 Complex& operator =(Complex&&);
 bool operator ==(const Complex&)const ;
 bool operator !=(const Complex&)const;
 Complex& operator+=(const Complex &);
 Complex operator+(const Complex & )const;
 Complex& operator-=(const Complex &);
 Complex operator-(const Complex & )const;
 Complex& operator*=(const Complex &);
 Complex operator*(const Complex & )const;
 Complex& operator/=(const Complex &);
 Complex operator/(const Complex & )const;
 Complex& operator^=(int);
 Complex operator^(int)const;
 Complex& operator ++();
 Complex operator ++(int);
 Complex& operator --();
 Complex operator --(int);
 Complex Conjugate()const;
 float Modul()const;
 float GetReal()const;
 float GetImaginary()const;
 float arg()const;
 friend std::istream&operator>>(std::istream&,Complex& );
 friend std::ostream&operator<<(std::ostream&,const Complex&);
 
};
Complex::Complex(float re,float im):re_(re),im_(im){
 Log("Called parametrized constructor ");
}
Complex::Complex(const Complex&other):re_(other.re_),im_(other.im_){
 Log("Called copy constructor");
}
Complex::Complex(Complex&&other):re_(other.re_),im_(other.im_){
 Log("Called move constructor");
}
Complex::~Complex(){
 Log("Called destructor");
 
}
Complex&  Complex::operator = (const Complex&other){
 Log("Called operator=");
 re_=other.re_;
 im_=other.im_;
 return (*this);
}
Complex& Complex:: operator =(Complex&&other){
 Log("Called move operator=");
 re_=other.re_;
 im_=other.im_;
 return (*this);
}
bool Complex::operator ==(const Complex&other)const{
 Log("Called operator==");
 return (re_==other.re_ && im_==other.im_);
}
bool Complex:: operator !=(const Complex&other )const{
 Log("Called operator!=");
 return !(*this==other);
}
Complex& Complex:: operator+=(const Complex & other){
 Log("Called operator+=");
 re_+=other.re_;
 im_+=other.im_;
 return(*this);
}
Complex Complex::operator+(const Complex & other )const{
 Log("Called operator+");
 Complex res(*this);
 res+=other;
 return res;
}
Complex& Complex:: operator-=(const Complex & other){
 Log("Called operator-=");
 re_-=other.re_;
 im_-=other.im_;
 return(*this);
}
Complex Complex::operator-(const Complex & other )const{
 Log("Called operator-");
 Complex res(*this);
 res-=other;
 return res;
}
Complex& Complex::operator*=(const Complex &other ){
 Log("Called operator*=");
 (*this)=(*this)*other;
 return (*this);
}
Complex Complex:: operator*(const Complex & other)const{
Log("Called operator*");
 Complex res;
 res.re_=re_*other.re_-im_*other.im_;
 res.im_=re_*other.im_+im_*other.re_;
 return res;
}
Complex& Complex:: operator/=(const Complex & other){
 Log("called operator /=");
 assert(other.re_!=0 || other.im_!=0);
 (*this)=(*this)/other;
 return (*this);
}
Complex Complex::operator/(const Complex & other )const{
 Log("called operator /");
 assert(other.re_!=0 || other.im_!=0);
 Complex res(*this);
 res*=other.Conjugate();
 float k=other.Modul()*other.Modul();
 res.re_/=k;
 res.im_/=k;
 return res;
}
Complex& Complex::operator^=(int n){
 Log("called operator ^=");
 (*this)=(*this)^n;
 return (*this);
}
Complex Complex:: operator^(int n )const{
 Log("called operator ^");
 Complex res(1);
 while(n<0){
  res/=(*this);
  n++;
 }
 while(n>0){
  res*=(*this);
  n--;
 }
 return res;
}
Complex& Complex:: operator ++(){
 Log("Called operator ++()");
 ++re_;
 return (*this);
}
Complex Complex::operator ++(int){
 Log("Called operator ++(int)");
 Complex res(*this);
 ++re_;
 return res;
}
Complex& Complex:: operator --(){
 Log("Called operator --()");
 --re_;
 return (*this);
}
Complex Complex:: operator --(int){
 Log("Called operator --(int)");
 Complex res(*this);
 --re_;
 return res;
}
Complex Complex::Conjugate()const{
 Log("Called function Conjugate()");
 Complex res(*this);
 res.im_*=-1;
 return res;
 
}
float Complex:: Modul()const{
 Log("Called function Modul()");
 return sqrt(re_*re_+im_*im_);
}
float Complex:: GetReal()const{
 Log("Called function GetReal()");
 return re_;
}
float Complex::GetImaginary()const{
 Log("Called function GetImaginary()");
 return im_;
}
float Complex::arg()const{
 Log("called function arg() ");
 assert(re_!=0||im_!=0);
if(re_>0){
    return atan(im_/re_);
}
if(re_==0){
    if(im_>0){
        return asin(1);
        }
        else{
            return -asin(1);
            }
    }
    float k=atan(im_/re_);
    if (k<=0){
        return k+acos(-1);
        }
    return k-acos(-1);
        
}
std::istream&operator>>(std::istream & in,Complex& current){
 Log("Called friend function istream& operator  >>");
 in>>current.re_>>current.im_;
 return in;
}
std::ostream&operator<<(std::ostream & out ,const Complex&current){
 Log("Called friend function  ostream operator <<");
 if(current.im_==0){
   out<<current.re_;
  return out;
 }
 if(current.re_!=0){
  out<<current.re_;
 if(current.im_>0){
  out<<"+";
 }
 }
 if(current.im_!=1 && current.im_!=-1){
  out<<current.im_<<"*";
 }
 if(current.im_==-1){
 out<<"-";
 }
 out<<"i";
 return out;
}
int main(){
 Complex c(0,-1);
 std::cout<<c<<std::endl;
}
