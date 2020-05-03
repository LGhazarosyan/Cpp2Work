#define debugMode 1
#if debugMode==1
#define Log(x) std::cout<<x<<std::endl;
#else
#define Log(x)
#endif
#include <iostream>
#include<thread>
#include<mutex>
#include<atomic>
template <class T>
struct ControlBlock{
 T * info_;
 std::mutex mu_;
 std::atomic<unsigned long> strongCount_;
 std::atomic<unsigned long> weakCount_;
 ControlBlock():info_(nullptr),strongCount_(0),weakCount_(0){};
 ControlBlock(const ControlBlock<T>&)=delete;
 ControlBlock(ControlBlock<T>&&)=delete;
 ControlBlock<T>& operator=(const ControlBlock<T>&)=delete;
 ControlBlock<T>& operator=(ControlBlock<T>&&)=delete;
};
template<class T>
class SharedPtr;

template <class T>
class WeakPtr{
private:
 ControlBlock<T>* ptrCB_;
  void ClearCB()noexcept;
public:
 WeakPtr()=delete;
 explicit WeakPtr(const SharedPtr<T>&)noexcept;
 WeakPtr(const WeakPtr<T>&)noexcept;
 WeakPtr(WeakPtr<T>&&)=delete;
 WeakPtr<T>&operator =(const SharedPtr<T>&)noexcept;
 WeakPtr<T>& operator=(const WeakPtr<T>&)noexcept;
 WeakPtr<T>& operator=(WeakPtr<T>&&)=delete;
 ~WeakPtr<T>()noexcept;
 SharedPtr<T> Lock()const noexcept;
 bool IsExpired()const noexcept;
 unsigned long Count()const noexcept;
 bool OwnerBefore (const WeakPtr<T>& ) const noexcept;
 bool OwnerBefore (const SharedPtr<T>& ) const noexcept;
 friend class SharedPtr<T>;
};

template<class T>
class SharedPtr{
private:
ControlBlock<T> *ptrCB_;
 T* ptr_;
  void ClearCB()noexcept;
public:
 SharedPtr()noexcept;
 explicit SharedPtr( T*&)noexcept;
 SharedPtr(const SharedPtr<T>&)noexcept;
 SharedPtr(SharedPtr<T>&&)noexcept;
 ~SharedPtr()noexcept;
 SharedPtr<T>& operator=(const SharedPtr<T>&)noexcept;
 SharedPtr<T>& operator=(SharedPtr&&)noexcept;
 void LockInfo()const noexcept;
 void UnlockInfo()const noexcept;
 bool TryLockInfo()const noexcept;
 T* get()const noexcept;
 T& operator*()const;
 T* operator->() const noexcept;
 unsigned long Count()const noexcept;
 bool IsNull()const noexcept;
 bool IsUnique()const noexcept;
 bool OwnerBefore(const SharedPtr<T>&)const noexcept;
 bool OwnerBefore(const WeakPtr<T>&)const noexcept;
 friend class WeakPtr<T>;
};

template<class T>
WeakPtr<T>:: WeakPtr(const SharedPtr<T>&shPtr) noexcept:ptrCB_(shPtr.ptrCB_){
  ptrCB_->weakCount_++;
}

template<class T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other) noexcept:ptrCB_(other.ptrCB_){
  ptrCB_->weakCount_++;
}

template<class T>
WeakPtr<T>& WeakPtr<T>::operator =(const SharedPtr<T>&shPtr) noexcept{
 if(ptrCB_==shPtr.ptrCB_){
  return (*this);
 }
 ptrCB_->weakCount_--;
 ClearCB();
 ptrCB_=shPtr;
 ptrCB_->weakCount_++;
 return (*this);
}

template<class T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>&other) noexcept{
 if(this==&other){
  return *this;
 }
 ptrCB_->weakCount_--;
 ClearCB();
 ptrCB_=other.ptrCB_;
 ptrCB_->weakCount_++;
 return (*this);
}

template<class T>
WeakPtr<T>::~WeakPtr<T>() noexcept{
 ptrCB_->weakCount_--;
 ClearCB();
  }

template<class T>
SharedPtr<T> WeakPtr<T>::Lock()const noexcept{
  SharedPtr<T> ptr;
 if(IsExpired()){
  return ptr;
 }
 ptr.ptrCB_->strongCount_--;
 ptr.ClearCB();
 ptr.ptrCB_=ptrCB_;
 ptr.ptr_=ptrCB_->info_;
 ptrCB_->strongCount_++;
 return ptr;
}

template<class T>
bool WeakPtr<T>::IsExpired()const noexcept{
 return (ptrCB_->strongCount_==0);
}

template<class T>
unsigned long WeakPtr<T>::Count()const noexcept{
 return ptrCB_->weakCount_;
}

template<class T>
bool WeakPtr<T>::OwnerBefore (const WeakPtr<T>& other) const noexcept{
 return (ptrCB_==other.ptrCB_);
}

template<class T>
bool WeakPtr<T>::OwnerBefore (const SharedPtr<T>& shPtr) const noexcept{
 return (ptrCB_==shPtr.ptrCB_);
}

template<class T>
void WeakPtr<T>::ClearCB() noexcept{
 if(ptrCB_->weakCount_+ptrCB_->strongCount_==0){
  delete ptrCB_;
  ptrCB_=nullptr;
  Log("The Control Block Was deleted")
 }
}


template <class T>
SharedPtr<T>::SharedPtr() noexcept:ptrCB_(new ControlBlock<T>),ptr_(nullptr){
 ptrCB_->strongCount_=1;
}

template <class T>
SharedPtr<T>::SharedPtr(T* & ptr) noexcept: ptrCB_(new ControlBlock<T>),ptr_(ptr){
 ptrCB_->info_=ptr;
 ptrCB_->strongCount_++;
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>&other) noexcept:ptrCB_(other.ptrCB_),ptr_(other.ptr_){
 ptrCB_->strongCount_++;
}

template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&&other) noexcept:ptrCB_(other.ptrCB_),ptr_(other.ptr_){
 other.ptrCB_=new ControlBlock<T>;
 other.ptr_=nullptr;
 other.ptrCB_->strongCount_=1;
}

template<class T>
SharedPtr<T>::~SharedPtr() noexcept{
 ptrCB_->strongCount_--;
 ClearCB();
}

 template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>&other) noexcept{
  ptrCB_->strongCount_--;
  ClearCB();
  ptrCB_=other.ptrCB_;
  ptr_=other.ptr_;
  ptrCB_->strongCount_++;
  return (*this);
 }

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&&other) noexcept{
 ptrCB_->strongCount_--;
 ClearCB();
 ptrCB_=other.ptrCB_;
 ptr_=other.ptr_;
 other.ptrCB_=new ControlBlock<T>;
 other.ptrCB_->strongCount_=1;
 other.ptr_=nullptr;
 return (*this);
}

template <class T>
void SharedPtr<T>::LockInfo()const noexcept{
 ptrCB_->mu_.lock();
}

template <class T>
void SharedPtr<T>:: UnlockInfo()const noexcept{
 ptrCB_->mu_.unlock();
}

template<class T>
bool SharedPtr<T>::TryLockInfo()const noexcept{
 return ptrCB_->mu_.try_lock();
}

template<class T>
T* SharedPtr<T>::get()const noexcept{
 ptrCB_->mu_.lock();
 T* temp=ptr_;
 ptrCB_->mu_.unlock();
 return temp;
}

template<class T>
T& SharedPtr<T>::operator*()const{
 ptrCB_->mu_.lock();
 T*temp=ptr_;
 ptrCB_->mu_.unlock();
 if(temp==nullptr){
  throw std::runtime_error("Dereferencing nullptr");
 }
 return *temp;
}

template<class T>
T* SharedPtr<T>::operator->()const noexcept{
 return &(operator*());
 }

template <class T>
unsigned long SharedPtr<T>::Count()const noexcept{
 return ptrCB_->strongCount_;
}

template<class T>
bool SharedPtr<T>::IsNull()const noexcept{
 return ptr_==nullptr;
}

template<class T>
bool SharedPtr<T>::IsUnique()const noexcept{
 return ptrCB_->strongCount_==1;
}

template<class T>
bool SharedPtr<T>::OwnerBefore(const SharedPtr<T>& other)const noexcept{
 return ptrCB_==other.ptrCB_;
}

template <class T>
bool SharedPtr<T>::OwnerBefore(const WeakPtr<T>&wPtr)const noexcept{
 return ptrCB_==wPtr.ptrCB_;
}

template<class T>
void SharedPtr<T>:: ClearCB() noexcept{
 if(ptrCB_->strongCount_){
  return;
 }
 delete ptrCB_->info_;
 ptrCB_->info_=nullptr;
 ptr_=nullptr;
 if(!ptrCB_->weakCount_){
  delete ptrCB_;
  ptrCB_=nullptr;
  ptr_=nullptr;
  Log("The Control Block Was deleted");
 }
}



class A{
public:
 A(){
  Log("A ctor");
 }
 ~A(){
  Log("A dtor");
 }
 void f(){
  std::cout<<"Hello"<<std::endl;
 }
};

int main(){
 A *p=new A;
 SharedPtr<A> shPtr(p);
 {
  SharedPtr<A> sh2Ptr=shPtr;
  std::cout<<shPtr.Count()<<std::endl;
  std::cout<<sh2Ptr.Count()<<std::endl;
  WeakPtr<A> wPtr(shPtr);
   std::cout<<wPtr.Count()<<std::endl;
 }
 std::cout<<shPtr.IsUnique()<<std::endl;
 WeakPtr<A> wPtr(shPtr);
 SharedPtr<A> sh2ptr=wPtr.Lock();
 std::cout<<shPtr.IsUnique()<<std::endl;
 std::cout<<shPtr.OwnerBefore(wPtr)<<std::endl;
 SharedPtr<A> sh3ptr;
 sh3ptr=sh2ptr;
 std::cout<< sh2ptr.IsNull()<<std::endl;
 (*shPtr).f();
 shPtr.LockInfo();
 std::cout<<sh2ptr.TryLockInfo()<<std::endl;
}
