#include<iostream>
#include<exception>
#include <stdexcept>
#include <string>
#define DebugMode 1
#if DebugMode==1
#define Log(x) std::cout<<x<<std::endl
#else
#define Log(x)
#endif
template <typename T>
class Vector{
private:
 unsigned long size_;
 unsigned long capacity_;
 T* array_;
 void Enlarge();
 void Shorten();
 void Allocate();
public:
 Vector():capacity_(0),size_(0),array_(nullptr){} // +
 Vector(const std::initializer_list<T>&);//+
 Vector(std::initializer_list<T>&&);//+
 Vector(const Vector&);//+
 Vector(Vector&&);//+
 ~Vector();//+
 Vector& operator =(const Vector &);//+
 Vector& operator =(Vector &&);//+
 bool operator ==(const Vector & )const;//+
 bool operator!=(const Vector &)const;//+
 T& operator [](unsigned long);//+
 T operator [](unsigned long)const;//+
 void PushBack( const T&);//+
 void PushBack(T&&);//+
 void PopBack();//+
 T& Front();//+
 T& Back();//+
 T Front()const;//+
 T Back()const;//+
 void Clear();//+
 void InsertAt(unsigned long,const T&);//+
 void InsertAt(unsigned long,T&&);//+
 void EraseAt(unsigned long);//+
 bool IsEmpty()const;//+
 unsigned long GetSize()const;//+
 unsigned long GetCapacity()const;//+
};


template<typename T>
Vector<T>::Vector (const  std::initializer_list<T> & list):size_(list.size()),capacity_(2*size_){
 if(capacity_==0){
  array_=nullptr;
  return;
 }
 
 Allocate();
 unsigned long index=0;
 for(const auto& i:list){
  Log(i);
  array_[index]=i;
  index++;
 }
}

template<typename T>
Vector<T>::Vector ( std::initializer_list<T>&& list):size_(list.size()),capacity_(2*size_){
 if(capacity_==0){
  array_=nullptr;
  return;
 }
 Allocate();
 unsigned long index=0;
 for(const auto& i:list){
  Log(i);
  array_[index]=std::move(i);
  index++;
 }
}


template <typename T>
Vector<T>::Vector(const Vector<T> &other):size_(other.size_),capacity_(other.capacity_){
 if (capacity_==0){
  array_=nullptr;
  return;
 }
 Allocate();
 for(unsigned int i=0;i<size_;i++){
  array_[i]=other[i];
 }
}


template <typename T>
Vector<T>::Vector(Vector<T> &&other):size_(other.size_),capacity_(other.capacity_),array_(other.array_){
 other.array_=nullptr;
 other.size_=0;
 other.capacity_=0;
}


template<typename T>
Vector<T>::~Vector(){
 delete []array_;
 array_=nullptr;
 }


template<typename T>
Vector<T>& Vector<T>:: operator =(const Vector<T> &other){
 if(this==&other){
  return (*this);
 }
 if(capacity_<other.size_ || other.capacity_==0 ){
  delete []array_;
  capacity_=other.capacity_;
  if(capacity_==0){
   array_=nullptr;
   size_=0;
   return (*this);
  }
  Allocate();
 }
 size_=other.size_;
 for(unsigned long i=0;i<size_;i++){
  array_[i]=other[i];
 }
 if(size_*4>capacity_){
  return (*this);
 }
 Shorten();
 }


template<typename T>
Vector<T>& Vector<T> :: operator =(Vector<T> &&other){
 if(this==&other){
  return (*this);
 }
 delete[] array_;
 array_= other.array_;
 size_=other.size_;
 capacity_=other.capacity_;
 other.array_=nullptr;
 other.size_=0;
 other.capacity_=0;
 return (*this);
}



template<typename T>
bool Vector<T>::operator ==(const Vector <T> & other )const{
 if(size_!=other.size_){
  return 0;
 }
 for(unsigned long i=0;i<size_;i++){
  if(array_[i]!=other[i]){
   return 0;
  }
 }
 return 1;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> & other)const{
 return !((*this)==other);
}

template<typename T>
T& Vector<T>::operator [](unsigned long n){
 if( n>=size_){
  throw std::out_of_range("Invalid index") ;
 }
 return array_[n];
}

template<typename T>
T  Vector<T>::operator [](unsigned long n)const{
 if( n>=size_){
  throw std::out_of_range("Invalid index") ;
 }
 return array_[n];
}

template<typename T>
void  Vector<T>::PushBack(const T& item){
 if(size_==capacity_){
  Enlarge();
 }
 array_[size_]=item;
 ++size_;
}

template<typename T>
void Vector<T>::PushBack(T&& item){
 if(size_==capacity_){
  Enlarge();
 }
 array_[size_]=std::move(item);
 ++size_;
}

template<typename T>
void Vector<T>:: PopBack(){
 if(IsEmpty()){
  throw std::underflow_error("Vector is empty");
 }
 array_[--size_].~T();
 if(size_*4>capacity_){
  return;
 }
  Shorten();
}

template<typename T>
T& Vector<T>::Front(){
 if(IsEmpty()){
  throw std::underflow_error("Vector is empty");
 }
 return array_[0];
}

template<typename T>
T& Vector<T>::Back(){
 if(IsEmpty()){
  throw std::underflow_error("Vector is empty");
 }
 return array_[size_-1];
}

template<typename T>
T Vector<T>::Front()const{
 if(IsEmpty()){
  throw std::underflow_error("Vector is empty");
 }
 return array_[0];
}

template<typename T>
T Vector<T>::Back()const{
 if(IsEmpty()){
  throw std::underflow_error("Vector is empty");
 }
 return array_[size_-1];
}

template<typename T>
void Vector<T>:: Clear(){
 delete[] array_;
 array_=nullptr;
 size_=0;
 capacity_=0;
}

template<typename T>
void Vector<T>:: InsertAt(unsigned long n,const T&item){
 if(n>=size_){
  throw std::out_of_range("Invalid index");
 }
 if(size_==capacity_){
  Enlarge();
 }
 ++size_;
 for(unsigned long i=size_-2;i>=n;i++){
  array_[i+1]=std::move(array_[i]);
 }
 array_[n]=item;
}


template <typename T>
void Vector<T>::InsertAt(unsigned long n,T&&item){
 if(n>=size_){
  throw std::out_of_range("Invalid index");
 }
 if(size_==capacity_){
  Enlarge();
 }
 ++size_;
 for(unsigned long i=size_-2;i>=n;i++){
  array_[i+1]=std::move(array_[i]);
 }
 array_[n]=std::move(item);
}


template<typename T>
void Vector<T>:: EraseAt(unsigned long n){
 if(n>=size_){
  throw std::out_of_range("Invalid index");
 }
 for(unsigned long i=n;i<size_-1;i++){
  array_[i]=std::move(array_[i+1]);
 }
 --size_;
 if(4*size_>capacity_){
   return;
 }
   Shorten();
}

template<typename T>
bool Vector<T>:: IsEmpty()const{
 return (size_==0);
 
}

template<typename T>
unsigned long Vector<T>:: GetSize()const{
 return size_;
}
template<typename T>
unsigned long Vector<T>::GetCapacity()const{
 return capacity_;
}

template <typename T>
void Vector<T>:: Enlarge(){
 if(capacity_==0){
  capacity_=1;
 }
 else{
 capacity_=2*capacity_;
 }
 int failedCount=0;
 T* temp=nullptr;
 while(1){
 temp=new(std::nothrow) T[capacity_];
  if(temp!=nullptr){
  Log("Enlarge was successful");
  break;
  }
  failedCount++;
  Log("Enlarge has failed");
  if(failedCount==10){
   Log("Enlarge was unsuccessful");
   std::exit(EXIT_FAILURE);
 }
  Log("Trying Enlarge again");
 }
 for(unsigned long i=0;i<size_;i++){
  temp[i]= std::move(array_[i]);
 }
 delete []array_;
 array_=temp;
}

template<typename T>
void Vector<T>:: Shorten(){
 if(size_==0){
  capacity_=0;
  delete[]array_;
  array_=nullptr;
  return ;
 }
 int failedCount=0;
 unsigned long tempCapacity=2*size_;
 T* temp=nullptr;
 while(1){
 temp=new(std::nothrow)T[tempCapacity];
  if(temp!=nullptr){
  Log("Shorten was successful");
  break;
  }
  failedCount++;
  Log("Shorten has failed");
  if(failedCount==5){
   Log("Shorten was unsuccessful");
   return;
  }
  Log("Trying Shorten again");
 }
 for(unsigned long i=0;i<size_;i++){
  temp[i]=std::move(array_[i]);
 }
 delete[]array_;
 array_=temp;
 capacity_=tempCapacity;
}
 
template <typename T>
void Vector<T>::Allocate(){
 int failedCount=0;
 while(1){
 array_=new (std::nothrow) T[capacity_];
  if(array_!=nullptr){
   Log("The Allocation was successful");
   return;
 }
  failedCount++;
  Log("Allocation has failed");
  if(failedCount==10){
   Log("The Allocation was unsuccessful ");
   std::exit(EXIT_FAILURE);
  }
  Log("Trying Allocation again");
 }
}
int main(){
}

