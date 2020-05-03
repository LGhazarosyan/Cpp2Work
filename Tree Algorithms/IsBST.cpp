#include <iostream>
template<class T>
struct Node{
 T key_;
 Node * right_;
 Node * left_;
 Node(T item=T(),Node<T>*left=nullptr,Node<T>*right=nullptr):key_(item),left_(left),right_(right){};
};
template<class T>
bool IsSearchTree(Node<T>*root){
 if(!root){
  return 1;
 }
 bool b=1;
 if(root->left_){
  if(root->left_->key_>=root->key_){
   return 0;
  }
 }
 if(root->right_){
  if(root->right_->key_<root->key_){
   return 0;
  }
 }
 if(root->left_){
   b&=IsSearchTree(root->left_);
 }
 if(!b){
  return b;
 }
 if(root->right_){
 b&=IsSearchTree(root->right_);
 }
 return b;
}
int main(){
 Node <int>*  a  = new Node<int> (1);
 Node <int> * b  = new Node<int> (2);
 Node <int >* c = new Node<int> (2,a,b);
 Node <int>* d= new Node<int>(3,c);
 Node <int>* e=new Node<int> (5);
 Node <int>* f=new Node<int>(4,d,e);
 Node <int> *g=new Node<int>(9);
 Node<int> *h=new Node<int>(11);
 Node<int>* i=new Node<int>(10,g,h);
 Node <int>* j=new Node<int>(6);
 Node <int>*k=new Node <int>(7);
 Node<int > *l=new Node<int>(7,j,k);
 Node<int >* m=new Node<int >(8,l,i);
 Node<int>*n=new Node<int >(8,f,m);
 std::cout<<IsSearchTree(n);
 
}
