#include<iostream>
#include<stack>
template <class T>
struct Node{
 T info_;
 Node<T>* prev_;
 Node<T>* next_;
 Node():info_(T()),prev_(nullptr),next_(nullptr){};
 Node(const T& info):info_(info),prev_(nullptr),next_(nullptr){};
 Node(T&& info):info_(std::move(info)),prev_(nullptr),next_(nullptr){};
 
};
template <class T>
class List{
public:
 class Iterator;
private:
 Node<T>* head_;
 Node<T>* tail_;
 unsigned long size_;
 void Clear(Node<T>*);
public:
 List():head_(new Node<T>),tail_(new Node<T>){};
 List(const std::initializer_list<T>&);
 List(std::initializer_list<T>&&);
 List(const List&);
 List(List&&);
 ~List();
 List<T>& operator=(const List&);
 List<T>& operator=(List&&);
 bool operator ==(const List&)const;
 bool operator !=(const List&)const;
 T Front()const;
 T& Front();
 T Back()const;
 T& Back();
 void PopFront();
 void PopBack();
 void PushBack(const T&);
 void PushBack(T&&);
 void PushFront(const T&);
 void PushFront(T&&);
 void Clear();
 List<T>::Iterator Begin()const;
 List<T>::Iterator End()const;
 void Reverse();
 bool IsEmpty()const;
 unsigned long GetSize()const;
};
template<class T>
 class  List<T>::Iterator{
 private:
  Node<T>* ptr_;
 public:
  Iterator():ptr_(nullptr){};
  Iterator(Node<T>*node):ptr_(node){};
  Iterator(const List<T>::Iterator&)=default;
  Iterator(List<T>::Iterator&&)=default;
  List<T>::Iterator& operator=(const List<T>::Iterator&)=default;
  List<T>::Iterator&operator=(List<T>::Iterator &&)=default;
  T& operator *()const;
  T* operator ->()const;
  List<T>::Iterator& operator++();
  List<T>::Iterator operator++(int);
  List<T>::Iterator& operator--();
  List<T>::Iterator operator--(int);
  List<T>::Iterator Erase(bool b=1);//if b=1 returns iterator that follows (*this)
  List<T>::Iterator InsertAfter(const T&)const;
  List<T>::Iterator InsertAfter(T&&)const;
  List<T>::Iterator InsertBefore(const T&)const;
  List<T>::Iterator InsertBefore(T&&)const;
  bool operator ==(const List<T>::Iterator&)const;
  bool operator !=(const List<T>::Iterator&)const;
};

template <class T>
T& List<T>::Iterator:: operator *()const{
 if(!ptr_ || !ptr_->next_ || !ptr_->prev_){
   throw std::runtime_error("Dereferencing Invalid Iterator");
 }
 return ptr_->info_;
}

template <class T>
T* List<T>::Iterator::operator ->()const{
 return &(operator *());
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){
 if(!ptr_ || !ptr_->next_ || !ptr_->prev_){
   throw std::runtime_error( " Incrementing Invalid Iterator");
 }
 ptr_=ptr_->next_;
 return (*this);
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int){
  if(!ptr_ || !ptr_->next_ || !ptr_->prev_){
   throw std::runtime_error( " Incrementing Invalid Iterator");
 }
 List<T>::Iterator temp=(*this);
 ptr_=ptr_->next_;
 return temp;
}

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--(){
 if(!ptr_ || !ptr_->next_ || !ptr_->prev_){
   throw std::runtime_error( " Decrementing  Invalid Iterator");
 }
 ptr_=ptr_->prev_;
 return (*this);
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int){
 if(!ptr_ || !ptr_->next_ || !ptr_->prev_){
   throw std::runtime_error( " Decrementing  Invalid Iterator");
 }
 List<T>::Iterator temp=(*this);
 ptr_=ptr_->prev_;
 return temp;
}

template<class T>
typename List<T>::Iterator List<T>::Iterator::Erase(bool b){
 if(!ptr_ || !ptr_->prev_ || !ptr_->next_){
  throw std::runtime_error("Invalid Iterator");
 }
 List<T>::Iterator it=(*this);
 if(b){
 it++;
 }
 else {
  it--;
 }
 Node<T>*temp=ptr_->prev_;
 temp->next_=ptr_->next_;
 ptr_->next_->prev_=temp;
 delete ptr_;
 ptr_=nullptr;
 return it;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::InsertAfter(const T& item)const{
 if(!ptr_ || !ptr_->prev_ || !ptr_->next_){
  throw std::runtime_error("Invalid Iterator");
 }
 Node<T>* temp=new Node<T>(item);
 temp->prev_=ptr_;
 temp->next_=ptr_->next_;
 ptr_->next_->prev_=temp;
 ptr_->next_=temp;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::InsertAfter(T&&item)const{
 if(!ptr_ || !ptr_->prev_ || !ptr_->next_){
  throw std::runtime_error("Invalid Iterator");
 }
 Node<T>* temp=new Node<T>(std::move(item));
 temp->prev_=ptr_;
 temp->next_=ptr_->next_;
 ptr_->next_->prev_=temp;
 ptr_->next_=temp;
 List<T>::Iterator it=*this;
 return ++it;
 
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::InsertBefore(const T&item)const{
 if(!ptr_ || !ptr_->prev_ || !ptr_->next_){
  throw std::runtime_error("Invalid Iterator");
 }
 Node<T> * temp=new Node<T>(item);
 temp->next_=ptr_;
 temp->prev_=ptr_->prev_;
 ptr_->prev_->next=temp;
 ptr_->prev_=temp;
 List<T>::Iterator it=(*this);
 return --it;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::InsertBefore(T&&item)const{
 if(!ptr_ || !ptr_->prev_ || !ptr_->next_){
  throw std::runtime_error("Invalid Iterator");
 }
 Node<T> * temp=new Node<T>(std::move(item));
 temp->next_=ptr_;
 temp->prev_=ptr_->prev_;
 ptr_->prev_->next_=temp;
 ptr_->prev_=temp;
 List<T>::Iterator it=(*this);
 return --it;
}
template<class T>
bool  List<T>::Iterator::operator ==(const List<T>::Iterator & other)const{
 return ptr_==other.ptr_;
}

template<class T>
bool  List<T>::Iterator::operator !=(const List<T>::Iterator& other)const{
 return ptr_!=other.ptr_;
}





template<class T>
void List<T>::Clear(Node<T>*node){
 while(node!=tail_->prev_){
  PopBack();
 }
 PopBack();
}

template<class T>
List<T>::List(const std::initializer_list<T>&l){
 head_=new Node<T>;
 tail_=new Node<T>;
 head_->next_=tail_;
 tail_->prev_=head_;
 Node<T>*temp=nullptr;
 for(const auto& i :l){
  temp=new Node<T>(i);
  temp->next_=tail_;
  temp->prev_=tail_->prev_;
  tail_->prev_->next_=temp;
  tail_->prev_=temp;
 }
}

template<class T>
List<T>::List(std::initializer_list<T>&& l){
 head_=new Node<T>;
 tail_=new Node<T>;
 head_->next_=tail_;
 tail_->prev_=head_;
 Node<T>*temp=nullptr;
 for(const auto& i :l){
  temp=new Node<T>(std::move(i));
  temp->next_=tail_;
  temp->prev_=tail_->prev_;
  tail_->prev_->next_=temp;
  tail_->prev_=temp;
 }
}

template<class T>
List<T>::List(const List&other){
 head_=new Node<T>;
 tail_=new Node<T>;
 head_->next_=tail_;
 tail_->prev_=head_;
 Node<T>*tempo=other.head_->next_;
 Node<T>*temp=nullptr;
 while(tempo!=other.tail_){
  temp=new Node<T>(tempo->info_);
   temp->next_=tail_;
   temp->prev_=tail_->prev_;
   tail_->prev_->next_=temp;
   tail_->prev_=temp;
 }
}

template<class T>
List<T>::List(List&&other):head_(other.head_),tail_(other.tail_){
 other.head_=new Node<T>;
 other.tail_=new Node<T>;
 other.head_->next_=other.tail_;
 other.tail_->prev_=other.head_;
}

template<class T>
List<T>::~List(){
 Clear();
}

template<class T>
List<T>& List<T>::operator=(const List&other){
 if(this==&other){
  return *this;
 }
 Node<T>*temp=head_->next_;
 Node<T>*tempo=other.head_->next_;
 while(temp!=tail_ && tempo!=other.tail_){
  temp->info_=tempo->info_;
  temp=temp->next_;
  tempo=tempo->next_;
 }
 while(tempo!=other.tail_){
  PushBack(tempo->info_);
  tempo=tempo->next_;
 }
 if(temp!=tail_){
  tempo=temp->prev_;
  Clear(temp);
 }
 return (*this);
}

template<class T>
List<T>& List<T>::operator=(List&&other){
 if(this==&other){
  return *this;
 }
 Clear();
 head_=other.head_;
 tail_=other.tail_;
 other.head_=new Node<T>;
 other.tail_=new Node<T>;
 head_->next_=tail_;
 tail_->prev_=head_;
 return (*this);
}

template<class T>
bool List<T>::operator ==(const List&other)const{
 Node<T>* temp=head_->next_;
 Node<T>*tempo=other.head_->next_;
 while(temp!=tail_&&tempo!=other.tail_){
  if(temp->info_!=tempo->info_){
   return 0;
  }
  temp=temp->next_;
  tempo=tempo->next_;
 }
 if(temp==tail_&&tempo==other.tail_){
  return 1;
 }
 return 0;
}

template<class T>
bool List<T>::operator !=(const List&other)const{
 return !((*this)==other);
}

template<class T>
T List<T>::Front()const{
 if(IsEmpty()){
  throw std::underflow_error("Empty List");
 }
 return head_->next_->info_;
}

template<class T>
T& List<T>::Front(){
 if(IsEmpty()){
  throw std::underflow_error("Empty List");
 }
 return head_->next_->info_;
}
template <class T>
T List<T>::Back()const{
  if(IsEmpty()){
   throw std::underflow_error("Empty List");
  }
  return tail_->prev_->info_;
}


template <class T>
T& List<T>::Back(){
  if(IsEmpty()){
   throw std::underflow_error("Empty List");
  }
  return tail_->prev_->info_;
}

template<class T>
void List<T>::PopFront(){
 if(IsEmpty()){
  throw std::underflow_error("Empty List");
 }
 Node<T>*temp=head_->next_;
 head_->next_=temp->next_;
 temp->next_->prev_=head_;
 temp->next_=nullptr;
 delete temp;
}

template<class T>
void List<T>::PopBack(){
 if(IsEmpty()){
  throw std::underflow_error("Empty List");
 }
 Node<T>*temp=tail_->prev_;
 tail_->prev_=temp->prev_;
 temp->prev_->next_=tail_;
temp->next_=nullptr;
 delete temp;
 
}

template<class T>
void List<T>::PushBack(const T&item){
 Node<T>*temp=new Node<T>(item);
 temp->next_=tail_;
 temp->prev_=tail_->prev_;
 tail_->prev_=temp;
 temp->prev_->next_=temp;
}

template<class T>
void List<T>::PushBack(T&&item){
 Node<T>*temp=new Node<T>(std::move(item));
 temp->next_=tail_;
 temp->prev_=tail_->prev_;
 tail_->prev_=temp;
 temp->prev_->next_=temp;
}

template<class T>
void List<T>::PushFront(const T& item){
 Node<T>*temp=new Node<T>(item);
 temp->prev_=head_;
 temp->next_=head_->next_;
 head_->next_=temp;
 temp->next_->prev_=temp;
}

template<class T>
void List<T>::PushFront(T&& item){
 Node<T>*temp=new Node<T>(std::move(item));
 temp->prev_=head_;
 temp->next_=head_->next_;
 head_->next_=temp;
 temp->next_->prev_=temp;
}

template<class T>
void List<T>::Clear(){
 while(!IsEmpty()){
  PopBack();
 }
 
}

template<class T>
typename List<T>::Iterator List<T>::Begin()const{
 return List<T>::Iterator(head_->next_);

}

template<class T>
typename List<T>::Iterator List<T>:: End()const{
 return List<T>::Iterator(tail_);
}

template<class T>
void List<T>:: Reverse(){
 Node<T>*temp=head_;
 while(temp){
  std::swap(temp->next_,temp->prev_);
  temp=temp->prev_;
 }
 std::swap(head_,tail_);
}

template <class T>
bool List<T>::IsEmpty()const{
 return head_->next_==tail_;
}

template<class T>
unsigned long List<T>::GetSize()const{
 unsigned long size=0;
 Node<T>*temp=head_->next_;
 while(temp!=tail_){
  size++;
  temp=temp->next_;
 }
 return size;
}
int main(){
 List<int> l1={1,2,6,8,9,10};
 List<int> l2={1,2,6,8,9,2};
 auto it1=l1.Begin();

 while(it1!=l1.End()){
  std::cout<<*it1<<" ";
  it1++;
 }
 l2.Reverse();
  auto it2=l2.Begin();
 std::cout<<std::endl;
 while(it2!=l2.End()){
  std::cout<<*it2<<" ";
  it2++;
 }
 l1=l2;
 std::cout<<(l1==l2);
}

