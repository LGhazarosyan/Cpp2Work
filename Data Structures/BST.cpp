#include <iostream>
template<class T>
struct Node{
 T key_;
 Node *left_;
 Node *right_;
 Node():left_(nullptr),right_(nullptr){};
 Node(T item):key_(item),left_(nullptr),right_(nullptr){};
};
template <class T>
class BST{
private:
 Node<T> *root_;
 unsigned long size_;
 void Copy(Node<T>*&, Node<T>*&);
 void Assaign(Node<T>*&,Node<T>*&);
 void Empty(Node<T>*&);
 bool Delete(Node<T>*&,const T&);
 void Print(Node<T>* root)const;//for testing
 bool FindRecursive(const Node<T> *&,const T&)const;
 void InsertItemRecursive( Node<T> *&,const T&);
 bool DeleteItemRecursive( Node<T> *,const T&,Node<T>*);
 Node <T>* GetMinimum(Node<T>*&root)const;
 Node <T>* GetMaximum(Node<T>*&root)const;
public:
 BST():root_(nullptr),size_(0){
 };
 BST(const BST<T>&);
 BST(BST<T>&&);
 BST<T>&operator=(const BST<T>&);
 BST<T>&operator=(BST<T>&&);
 ~BST();
 bool Find(const T&)const;
 bool FindRecursive(const T&)const;
 bool DeleteItem(const T&);
 bool DeleteItemRecursive(const T&);
 void InsertItem(const T&);
 void InsertItemRecursive(const T&);
 void Clear();
 bool IsEmpty()const;
 unsigned long GetSize()const;
 T GetMaximum()const;
 T GetMinimum()const;
 void Print()const;//for testing
};



template<class T>
void BST<T>::Copy(Node<T>*&current,Node<T>*&other){
 if(!other){
  current=nullptr;
  return;
 }
 if(other->left_){
  current->left_=new Node<T>;
  Copy(current->left_,other->left_);
 }
 if(other->right_){
  current->right_=new Node<T>;
   Copy(current->right_,other->right_);
 }
 current->key_=other->key_;
}

template<class T>
void BST<T>::Assaign(Node<T>*&current,Node<T>*&other){
 if(!other){
  Empty(current);
  return;
 }
 current->key_=other->key_;
 if(other->left_){
  if(!current->left_){
  current->left_=new Node<T>;
  }
  Assaign (current->left_,other->left_);
 }
 else{
  Empty(current->left_);
 }
 if(other->right_){
  if(!current->right_){
  current->right_=new Node<T>;
  }
  Assaign (current->right_,other->right_);
 }
 else{
  Empty(current->right_);
 }
}

template<class T>
void BST<T>::Empty(Node<T>* & root){
 if(root==nullptr){
  return;
 }
 Empty(root->left_);
 Empty(root->right_);
 delete root;
 size_--;
 root=nullptr;
}

template<class T>
bool BST<T>::Delete(Node<T>*&root,const T &item ){
 if(root==nullptr){
  return 0;
 }
 Node<T>*temp=root;
 Node<T>*parent=nullptr;
 bool left=0;
 while(temp){
  if(temp->key_==item){
   break;
  }
  parent=temp;
  if(item< temp->key_){
   temp=temp->left_;
   left=1;
  }
  else{
  temp=temp->right_;
  left=0;
  }
 }
 if(temp==nullptr){
  return 0;
 }
 if(temp->left_&&temp->right_){
  parent=temp->left_;
  parent=GetMaximum(temp->left_);
  T k=parent->key_;
 bool b=Delete(temp,k);
  temp->key_=k;
  return b;
 }
 
 Node<T> *child=nullptr;
 if(temp->left_){
  child=temp->left_;
 }
 else{
  child=temp->right_;
 }
 delete temp;
 if(!parent){
  root_=child;
  return 1;
 }
 if(left){
  parent->left_=child;
 }
 else{
  parent->right_=child;
 }
 return 1;
}

template<class T>
void BST<T>::Print(Node<T>* root)const{
 if(!root){
  return;
 }
 Print(root->left_);
  std::cout<<root->key_<<" ";
 Print(root->right_);
}
template <class T>
bool BST<T>:: FindRecursive(const Node<T> *&root,const T& item)const{
 if(root==nullptr){
  return 0;
 }
 if(item==root->key_){
  return 1;
 }
 if(item<root->key_){
  return FindRecursive(root->left_, item);
 }
 return FindRecursive(root->right_, item);
}


template<class T>
void BST<T>::InsertItemRecursive( Node<T>*& root,const T&item){
 if(root==nullptr){
  root=new Node<T>(item);
  return;
 }
 if(item<root->key_){
  if(!root->left_){
   root->left_=new Node<T>(item);
  }
  else{
   InsertItemRecursive(root->left_, item);
  }
 }
 else{
  if(!root->right_){
   root->right_=new Node<T>(item);
  }
  else{
   InsertItemRecursive(root->right_, item);
  }
 }
}

template<class T>
bool BST<T>::DeleteItemRecursive(Node<T> * root,const T&item,Node<T>* parent){
 if(root==nullptr){
  return 0;
 }
 if(root->key_!=item){
  if(item<root->key_){
   return DeleteItemRecursive(root->left_, item, root);
  }
   return DeleteItemRecursive(root->right_, item, root);
 }
  if(root->left_&&root->right_){
   bool b=0;
   T tempItem=GetMaximum(root->left_)->key_;
   b=DeleteItemRecursive(root->left_,tempItem,root);
   root->key_=tempItem;
   return b;
  }
 Node<T>*child=nullptr;
 if(root->right_){
  child=root->right_;
 }
 else{
  child=root->left_;
 }
 if(!parent){
  delete root_;
  root_=child;
  return 1;
 }
 if(parent->left_==root){
  parent->left_=child;
 }
 if(parent->right_==root){
  parent->right_=child;
 }
  delete root;
 return 1;
  }


template<class T>
Node <T>* BST<T>::GetMinimum(Node<T>*&root)const{
 if(root==nullptr){
  throw std::underflow_error("empty BST");
 }
 while(root->left_){
  root=root->left_;
 }
 return root;
}
template<class T>
Node <T>* BST<T>::GetMaximum(Node<T>*&root)const{
 if(root==nullptr){
  throw std::underflow_error("empty BST");
 }
 while(root->right_){
  root=root->right_;
 }
 return root;
}
template<class T>
BST<T>::BST( const BST<T>& other):size_(other.size_){
 if(size_==0){
  root_=nullptr;
  return;
 }
 root_=new Node<T>;
 Node<T>*oroot=other.root_;
 Copy(root_,oroot);
}


template<class T>
BST<T>::BST(BST<T>&&other):size_(other.size_){
 root_=other.root_;
 other.root_=nullptr;
 other.size_=0;
}
template<class T>
BST<T>& BST<T>::operator =(const BST<T>&other){
 size_=other.size_;
 if(size_==0){
  root_=nullptr;
  return (*this);
 }
 root_=new Node<T>;
 Node<T>*aroot=other.root_;
 Assaign(root_, aroot);
 return (*this);
}


template <class T>
BST<T>& BST<T>::operator=(BST<T>&&other){
 Clear();
 size_=other.size_;
 root_=other.root_;
 other.root_=nullptr;
 other.size_=0;
 return (*this);
}

template<class T>
BST<T>::~BST(){
 Empty(root_);
}


template <class T>
bool BST<T>:: Find(const T& item)const{
 if(IsEmpty()){
  return 0;
 }
 Node<T>*temp=root_;
 while(temp!=nullptr){
  if(temp->key_==item){
   return 1;
  }
  if(temp->key_>item){
   temp=temp->left_;
  }
  else{
  temp=temp->right_;
  }
 }
 return 0;
}
template<class T>
bool BST<T>::FindRecursive(const T& item)const{
 return FindRecursive(root_, item);
}

template<class T>
void BST<T>::InsertItem(const T& item){
  if(IsEmpty()){
  root_=new Node<T>(item);
   size_++;
  return ;
 }
 size_++;
 Node<T>* temp=root_;
 Node<T>* parent=nullptr;
 bool left=0;
 while(temp!=nullptr){
  parent=temp;
  if(item<temp->key_){
   temp=temp->left_;
   left=1;
  }
  else{
  temp=temp->right_;
  left=0;
  }
 }
 if(left){
  parent->left_=new Node<T>(item);
 }
 else{
 parent->right_=new Node<T>(item);
 }
}
template<class T>
void BST<T>::InsertItemRecursive(const T&item){
 InsertItemRecursive(root_, item);
 size_++;
}
template <class T>
bool BST<T>::DeleteItem(const T& item){
 bool b= Delete(root_,item);
 if(b){
 size_--;
 }
 return b;
}
template<class T>
bool BST<T>:: DeleteItemRecursive(const T&item){
 Node<T>* parent=nullptr;
 bool b= DeleteItemRecursive(root_, item, parent);
 if(b){
 size_--;
 }
 return b;
}
template <class T>
void BST<T>::Clear(){
 Empty(root_);
}

template<class T>
bool BST<T>::IsEmpty()const{
 return size_==0;
}

template<class T>
unsigned long BST<T>::GetSize()const{
 return size_;
}


template<class T>
T BST<T>::GetMaximum()const{
 return GetMaximum(root_)->key_;
}


template<class T>
T BST<T>::GetMinimum()const{
  return GetMinimum()->key_;
 }

template<class T>
void BST<T>::Print()const{
 Print(root_);
}


int main(){
 BST<int> t3;
 t3.InsertItem(2);
  t3.InsertItem(3);
  t3.InsertItem(4);
  t3.InsertItem(5);
  t3.InsertItem(3);
  t3.InsertItem(2);
 t3.InsertItem(6);
 t3.InsertItem(7);
  t3.InsertItem(8);
  t3.InsertItem(7);
  t3.InsertItem(10);
  t3.InsertItem(7);
  t3.InsertItem(9);
  t3.InsertItem(11);


 t3.DeleteItem(5);
 t3.DeleteItem(7);
 t3.DeleteItem(6);
 t3.DeleteItem(1);
 t3.DeleteItem(3);
 t3.DeleteItem(2);
 t3.Print();
  std::cout<<std::endl;
 t3.Clear();
 t3.InsertItemRecursive(2);
  t3.InsertItemRecursive(3);
  t3.InsertItemRecursive(4);
  t3.InsertItemRecursive(5);
  t3.InsertItemRecursive(3);
  t3.InsertItemRecursive(2);
 t3.InsertItemRecursive(6);
 t3.InsertItemRecursive(7);
  t3.InsertItemRecursive(8);
  t3.InsertItemRecursive(7);
  t3.InsertItemRecursive(10);
  t3.InsertItemRecursive(7);
  t3.InsertItemRecursive(9);
  t3.InsertItemRecursive(11);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(5);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(7);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(6);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(1);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(3);
 t3.Print();
   std::cout<<std::endl;
 t3.DeleteItemRecursive(2);
 t3.Print();
   std::cout<<std::endl;
 t3.Print();
std::cout<< std::endl;
 std::cout<<t3.GetSize()<<std::endl;
}
