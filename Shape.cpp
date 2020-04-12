#define DebugMode 0
#if DebugMode==1
#define Log(x) std::cout<<x<<std::endl
#else
#define Log(x)
#endif
#include<iostream>
#include<cmath>
float pi=acos(-1);
struct Point{
 float x_;
 float y_;
 Point(float x =0,float y =0):x_(x),y_(y){
  Log("Called Point(int =0,int=0)");
 }
 Point(const Point &other):x_(other.x_),y_(other.y_){
  Log("Called Point(const Point &)");
 }
 Point (Point && other):x_(other.x_),y_(other.y_){
  Log("Called Point(Point&&)");
 }
 Point &operator =(const Point&other){
  Log("Called Point::operator=(const Point &)");
  x_=other.x_;
  y_=other.y_;
  return(*this);
 }
 Point &operator=(Point &&other){
  Log("Called Point operator=(Point &&)");
  x_=other.x_;
  y_=other.y_;
  return (*this);
 }
 bool operator==(const Point&other)const{
  return (x_==other.x_ &&y_==other.y_);
 }
 ~Point(){
  Log("Called ~Point()");
 }
 float Distance(const Point&other)const{
  Log("Called Point::Distance(const Point &)");
  return sqrt((x_-other.x_)*(x_-other.x_)+(y_-other.y_)*(y_-other.y_));
 }
};
class Shape{
public:
 Shape(){
  Log(" Called Shape::Shape()");
 }
 Shape(const Shape&){
  Log("Called Shape::Shape(const Shape&)");
 }
 Shape(Shape&&){
  Log("Called Shape::Shape(Shape&&)");
 }
 virtual float Area()const=0;
 virtual float Perimeter()const=0;
 virtual ~Shape(){
  Log("Called ~Shape()");
 }
};
class Circle: public Shape{
protected:
 Point O_;
 float r_;
public:
 Circle(int=0,int=0,int=1);
 Circle(const Circle &);
 Circle(Circle &&);
 ~Circle()override;
 Circle& operator =(const Circle&);
 Circle& operator =(Circle &&);
 bool operator ==(const Circle &)const;
 bool operator !=(const Circle &)const;
 virtual float Area() const override;
 virtual float Perimeter() const override;
 float CentreDistance(const Circle&)const;
 bool operator >(const Circle &)const;
 bool operator <(const Circle &)const;
 bool Belongs(const Point& p)const;
 short CountOfCrosses(const Circle&)const;
 void MoveAlongX(float x);
 void MoveAlongY(float y);
 void  EnlargeCircleArea(float k);
 float GetRadius()const;
 Point GetCentre()const;
 friend std::istream & operator >>(std::istream &,Circle &);
 friend std::ostream & operator<<(std::ostream &,const Circle &);
};
Circle::Circle(int x,int y,int r):O_(x,y),r_(r){
 Log("Called Circle (int=0,int=0,int=1)");
 assert(r_>0);
};

Circle::Circle(const Circle &other):O_(other.O_),r_(other.r_){
 Log("Called Circle (const Circle&)");
}
Circle::Circle(Circle &&other):O_(other.O_),r_(other.r_){
 Log("Called Circle (const Circle &)");
}
Circle::~Circle(){
 Log("Called ~Circle()");
}
Circle& Circle::operator =(const Circle&other){
 Log("Called Circle operator=(const Circle &)");
 O_=other.O_;
 r_=other.r_;
 return (*this);
}
Circle& Circle:: operator =(Circle && other){
 Log("Called Circle operator=(Circle &&)");
 O_=other.O_;
 r_=other.r_;
 return (*this);
}
bool Circle:: operator ==(const Circle & other)const{
 Log("Called Circle::operator ==(const Circle &)");
 return (O_== other.O_ && r_==other.r_);
}
bool Circle:: operator !=(const Circle &other)const{
 Log("Called Circle :: operator !=(const Circle&) ");
 return !(*this==other);
}
float Circle:: Area() const{
 Log("Called Circle::Area()");
 return pi*r_*r_;
}
float Circle::Perimeter() const{
 Log("Called Circle::Perimeter()");
 return 2*pi*r_;
}
float Circle:: CentreDistance(const Circle&other)const{
 Log("Called Circle::CentreDistance(const Circle&)");
 return O_.Distance(other.O_);
}
bool Circle::operator >(const Circle &other)const{
 Log("Called Circle::operator >(const Circle &)");
 return (r_>other.r_);
}
bool Circle::operator <(const Circle &other)const{
  Log("Called Circle::operator <(const Circle &)");
 return (r_<other.r_);
}
bool Circle:: Belongs (const Point& p)const{
 Log("Called Circle::Belongs(const Point&)");
 if (p.Distance(O_)==r_){
  return 1;
 }
 return 0;
}
short Circle:: CountOfCrosses(const Circle&other)const{
 Log("Called Circle::CountOfCrosses const Circle&");
 if((*this)==other){
  return 3;
 }
 if(O_.Distance(other.O_)>r_+other.r_){
  return 0;
 }
 if(O_.Distance(other.O_)==r_+other.r_){
  return 1;
 }
 return 2;
}
void Circle::MoveAlongX(float x){
 Log("Called Circle::MoveAlongX(float) ");
 O_.x_+=x;
}
void Circle::MoveAlongY(float y){
  Log("Called Circle::MoveAlongY(float) ");
 O_.y_+=y;
}
void  Circle::EnlargeCircleArea(float k){
  Log("Called Circle::EnlargeCircleArea(float) ");
 r_*=sqrt(k);
}
float Circle::GetRadius()const{
 return r_;
}
Point Circle:: GetCentre()const{
 return O_;
}
std::istream & operator >>(std::istream & in,Circle &current){
 Log("Called in>>Circle&");
 in>>current.O_.x_>>current.O_.y_>>current.r_;
 return in;
}
std::ostream & operator<<(std::ostream & out ,const Circle & current){
 Log("Called out<<Circle&");
 out<<"O("<<current.O_.x_<<","<<current.O_.y_<<")"<<"  "<<"r="<<current.r_<<std::endl;
 return out;
}

class Triangle:public Shape{
 protected:
  float a_,b_,c_;
 public:
  Triangle(float=1,float=1,float=1);
  Triangle(const Triangle&);
  Triangle(Triangle&&);
  ~Triangle() override;
  float Area() const override;
  float Perimeter() const override;
  bool operator ==(const Triangle&)const;
  bool operator !=(const Triangle&)const;
  short TypeByAngles()const;//0-սուրանկյուն,1-ուղղանկյուն ,2-բութանկյուն
  short TypeBySides()const;//0-սովորական,1-հավասարասրուն,2-հավասարակողմ
  bool Alike(const Triangle&)const;
  float GetMinSide()const;
  float GetMidSide()const;
  float GetMaxSide()const;
  friend std::istream & operator >>(std::istream &,Triangle &);
  friend std::ostream & operator<<(std::ostream &,const Triangle &);
};

Triangle::Triangle(float a,float b,float c):a_(a),b_(b),c_(c){
 Log("Called Triangle(float=1,float=1,float=1)");
 assert(a_>0 && b_>0 && c_>0);
 assert(a_+b_>c_ && a_+c_>b && c_+b_>a_);
 if (a_>b_){
  std::swap(a_,b_);
 }
 if(a_>c_){
  std::swap(a_,c_);
 }
 if(b_>c_){
  std::swap(b_,c_);
 }
}
Triangle::Triangle (const Triangle&other):a_(other.a_),b_(other.b_),c_(other.c_){
 Log("Called Triangle (const Triangle&)");
}
Triangle::Triangle(Triangle&&other):a_(other.a_),b_(other.b_),c_(other.c_){
 Log("Triangle(Triangle&&)");
}
Triangle::~Triangle(){
 Log("~Triangle()");
}
float Triangle:: Area()const {
 Log("Triangle:: Area()");
 float p=Perimeter()/2;
 return sqrt(p*(p-a_)*(p-b_)*(p-c_));
}
float Triangle::Perimeter() const {
 Log("Called Triangle::Perimeter() ");
 return a_+b_+c_;
}
bool Triangle:: operator ==(const Triangle&other)const{
 Log("Triangle:: operator ==(const Triangle&)");
 if(a_==other.a_  && b_==other.b_ &&c_==other.c_){
  return 1;
 }
 return 0;
}
bool  Triangle::operator !=(const Triangle&other)const{
 Log("Triangle:: operator !=(const Triangle&)");
 return !(other==(*this));
}
short Triangle::TypeByAngles()const{
 Log("Called Triangle::TypeByAngles()");
 if(a_*a_+b_*b_>c_*c_){
  return 0;
 }
 if(a_*a_+b_*b_==c_*c_){
  return 1;
 }
 return 2;
}
short Triangle:: TypeBySides()const{
 Log("Called Triangle::TypeBySides()");
 if(a_==b_ && b_==c_){
  return 2;
 }
 if(a_==b_ || b_==c_|| a_==c_ ){
  return 1;
 }
 return 0;
}
bool Triangle::Alike(const Triangle&other)const{
 Log("Triangle::Alike(const Triangle&)");
 if(a_/other.a_==b_/other.b_ && a_/other.a_==c_/other.c_){
  return 1;
 }
 return 0;
}
float Triangle::GetMinSide()const{
 return a_;
}
float Triangle::GetMidSide()const{
 return b_;
}
float Triangle::GetMaxSide()const{
 return c_;
}

class Rectangle:public Shape{
protected:
 float a_,b_;
public:
 Rectangle(float=1,float=1);
 Rectangle(const Rectangle&);
 Rectangle(Rectangle&&);
 ~Rectangle()override;
 float Perimeter() const override;
 float Area() const override;
 bool operator ==(const Rectangle &)const;
 bool operator !=(const Rectangle &)const;
 bool IsSquare()const;
 float GetMinSide()const;
 float GetMaxSize()const;
};


Rectangle::Rectangle(float a,float b):a_(a),b_(b){
 Log(" Called Rectangle(float=1,float=1)");
 assert(a_>0 && b_>0);
 if(a_>b_){
  std::swap(a_,b_);
 }
}
Rectangle:: Rectangle(const Rectangle&other):a_(other.a_),b_(other.b_){
 Log(" Called Rectangle(const Rectangle&");
}
Rectangle:: Rectangle(Rectangle&&other):a_(other.a_),b_(other.b_){
 Log(" Called Rectangle(Rectangle&&)");
}
Rectangle::~Rectangle(){
 Log("Called ~Rectangle()");
}
float Rectangle::Perimeter() const{
 Log("Called Rectangle::Perimeter()");
 return 2*(a_+b_);
}
float Rectangle::Area() const {
 Log("Called Rectangle::Area()");
 return a_*b_;
}
bool Rectangle::operator ==(const Rectangle &other)const{
 Log("Called Rectangle::operator ==(const Rectangle &)");
 return(a_==other.a_ && b_==other.b_);
}
bool Rectangle:: operator !=(const Rectangle &other)const{
  Log("Called Rectangle::operator !=(const Rectangle &)");
 return !(other==(*this));
}
bool Rectangle::IsSquare()const{
 Log("Called Recrangle::IsSquare() ");
 return(a_==b_);
}
int main(){
 Circle c(0,0,2);
 Point p(0,2);
}

