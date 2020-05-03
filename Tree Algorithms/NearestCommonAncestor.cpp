#include <iostream>
template<class T>
struct Node{
 T key_;
 Node * right_;
 Node * left_;
 Node(T item=T(),Node<T>*left=nullptr,Node<T>*right=nullptr):key_(item),left_(left),right_(right){};
};
template <class T>
Node<T>* NearestCommonAncestor(Node<T>*root,Node<T>*first,Node<T>*second,bool& find1,bool &find2){
 if(root==nullptr){
  return nullptr;
 }
 bool leftFind1=0,leftFind2=0;
 bool rightFind1=0,rightFind2=0;
 Node<T>*tempL=NearestCommonAncestor(root->left_, first, second,leftFind1,leftFind2);
 Node<T>*tempR=NearestCommonAncestor(root->right_, first, second,rightFind1,rightFind2);
 if(tempR){
  return tempR;
 }
 if(tempL){
  return tempL;
 }
 find1=leftFind1+rightFind1;
 find2=leftFind2+rightFind2;
 if(root==first){
  find1=1;
 }
 if(root==second){
  find2=1;
 }
 if(find1&&find2){
  return root;
 }
 return nullptr;
}
int main(){
 Node <int>*  a  = new Node<int> (2);
 Node <int> * b  = new Node<int> (3);
 Node <int >* c = new Node<int> (4,a,b);
 Node <int>* d= new Node<int>(5,c);
 Node <int>* e=new Node<int> (6);
 Node <int>* f=new Node<int>(10,d,e);
 Node <int> *g=new Node<int>(9);
 Node<int> *h=new Node<int>(11);
 Node<int>* i=new Node<int>(7,g,h);
 Node <int>* j=new Node<int>(8);
 Node <int>*k=new Node <int>(1);
 Node<int > *l=new Node<int>(12,j,k);
 Node<int >* m=new Node<int >(15,l,i);
 Node<int>*n=new Node<int >(13,f,m);
 bool x=0,y=0;
 std::cout<<NearestCommonAncestor(n, h, g, x, y)->key_;
 
}
