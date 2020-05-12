#include <iostream>
template <class T>
class Stack{
private:
 struct Node{
  T info_;
  Node *next_;
  Node():info_(T()){};
  Node(const T& item):info_(item),next_(nullptr){};
  Node(const T&& item):info_(std::move(item)),next_(nullptr){};
 };
 Node *first_;
 unsigned long size_;
 void  ClearAfter(Node * &);//Deletes given Node and all nodes following it
public:
 Stack():first_(nullptr),size_(0){};
 Stack(const std::initializer_list<T>&);
 Stack(std::initializer_list<T>&&);
 Stack(const Stack<T>&);
 Stack(Stack<T>&&);
 ~Stack();
 Stack<T>& operator=(const Stack<T>&);
 Stack<T>&operator=(Stack<T>&&);
 bool operator ==(const Stack<T>&)const;
 bool operator !=(const Stack<T>&)const;
 void Push(const T&);
 void Push(T&&);
 void Pop();
 T& Top()const;   
 bool IsEmpty()const;
 unsigned long Size()const;
 void Clear();
 
};

template<class T>
void Stack<T>:: ClearAfter(Node * &node){
 Node *temp=nullptr;
 while(node->next_){
  temp=node->next_->next_;
  delete node->next_;
  node->next_=temp;
 }
 delete node;
 node=nullptr;
}

template<class T>
Stack<T>::Stack(const std::initializer_list<T>&ls):size_(ls.size()),first_(nullptr){
 if (size_==0){
  return;
 }
 Node *temp=nullptr;
 for(const auto & item:ls){
  temp=new Node(item);
  temp->next_=first_;
  first_=temp;
  }
 }

template<class T>
Stack<T>::Stack(std::initializer_list<T>&&ls):size_(ls.size()),first_(nullptr){
 std::cout<<"Called move list constructor"<<std::endl;
 if (size_==0){
  return;
 }
 Node *temp=nullptr;
 for(const auto & item:ls){
  temp=new Node(std::move(item));
  temp->next_=first_;
  first_=temp;
  }
}

template<class T>
Stack<T>::Stack(const Stack<T>&other):size_(other.size_){
 std::cout<<"Copy constructor called"<<std::endl;
 first_=nullptr;
 if(size_==0){
  return;
 }
 first_=new Node(other.first_->info_);
 Node* tempo=other.first_->next_;
 Node* temp=first_;
 while(tempo){
  temp->next_=new Node(tempo->info_);
  tempo=tempo->next_;
  temp=temp->next_;
 }
}

template <class T>
Stack<T>::Stack(Stack<T>&&other):size_(other.size_),first_(other.first_){
 other.first_=nullptr;
 other.size_=0;
}

template<class T>
Stack<T>::~Stack(){
 Clear();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>&other){
 if(this==&other){
  return(*this);
 }
 if(other.size_==0){
  Clear();
  return (*this);
 }
 Node* tempo=other.first_;
 Node* temp=first_;
 temp->info_=tempo->info_;
 while(temp->next_ && tempo->next_){
  temp->next_->info_=tempo->next_->info_;
  temp=temp->next_;
  tempo=tempo->next_;
 }
 temp->info_=tempo->info_;
  tempo=tempo->next_;
  while(tempo){
   temp->next_=new Node(tempo->info_);
   tempo=tempo->next_;
   temp=temp->next_;
  }//temp->next_ is nullptr after while loop
 if(temp->next_){
  ClearAfter(temp->next_);
 }
 size_=other.size_;
 return (*this);
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T>&&other){
 if(this==&other){
  return (*this);
 }
 Clear();
 size_=other.size_;
 first_=other.first_;
 other.size_=0;
 other.first_=nullptr;
 return (*this);
}

template<class T>
bool Stack<T>::operator ==(const Stack<T>&other)const{
 if(size_!=other.size_){
  return 0;
 }
 Node* temp=first_;
 Node *tempo=other.first_;
 while(temp){
  if(temp->info_!=tempo->info_){
   return 0;
  }
  temp=temp->next_;
  tempo=tempo->next_;
 }
 return 1;
}

template<class T>
bool Stack<T>::operator !=(const Stack<T>&other)const{
 return !(*this==other);
}

template<class T>
void Stack<T>::Push(const T&item){
Node* temp=new Node(item);
 temp->next_=first_;
 first_=temp;
 size_++;
}

template<class T>
void Stack<T>::Push(T&&item){
 Node *temp=new Node(std::move(item));
 temp->next_=first_;
 first_=temp;
 size_++;
}
template<class T>
void Stack <T>::Pop(){
 if(size_==0){
  throw std::underflow_error("Popping from empty Stack");
 }
 Node *temp=first_->next_;
 delete first_;
 first_=temp;
 size_--;
}

template<class T>
T&  Stack<T>:: Top()const{
 if(size_==0){
  throw std::underflow_error("Taking Top of empty Stack");
 }
 return first_->info_;
}

template<class T>
bool Stack<T>::IsEmpty()const{
 return size_==0;
}

template<class T>
unsigned long  Stack<T>::Size()const{
 return size_;
}

template<class T>
void Stack<T>::Clear(){
 while(size_!=0){
  Pop();
 }
}


int main(){

}
