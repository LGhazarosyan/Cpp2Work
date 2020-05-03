#include <iostream>
#include <stack>
#include <queue>
template<class T>
struct Node{
 T key_;
 Node * right_;
 Node * left_;
 Node(T item=T(),Node<T>*left=nullptr,Node<T>*right=nullptr):key_(item),left_(left),right_(right){};
};

template<class T>
void PreOrder(Node<T>*root,void(*f)(Node<T>*)){
 std::stack<Node<T>*> st;
 Node<T>* temp=root;
 while(temp){
  while(temp->left_){
   st.push(temp);
   f(temp);
   temp=temp->left_;
  }
  if(temp->right_){
   st.push(temp);
   f(temp);
   temp=temp->right_;
   continue;
  }
   f(temp);
  while(!st.empty()){
   if(temp==st.top()->left_ && st.top()->right_){
    temp=st.top()->right_;
    break;
   }
   temp=st.top();
   st.pop();
  }
  if(st.empty()){
   break;
  }
 }
}

template <class T>
void PreOrderRecursive(Node<T>*root,void(*f)(Node<T>*)){
 if(!root){
  return ;
 }
 f(root);
 PreOrderRecursive<T>(root->left_, f);
 PreOrderRecursive<T>(root->right_, f);
}
template<class T>
void InOrder(Node<T>*root,void(*f)(Node<T>*)){
 std::stack<Node<T>*> st;
 Node<T>* temp=root;
 while(temp){
  while(temp->left_){
   st.push(temp);
   temp=temp->left_;
  }
   f(temp);
  if(temp->right_){
   st.push(temp);
   temp=temp->right_;
   continue;
  }
  while(!st.empty()){
   if(temp==st.top()->left_ && st.top()->right_){
    f(st.top());
    temp=st.top()->right_;
    break;
   }
   temp=st.top();
   if(!temp->right_){
    f(temp);
   }
   st.pop();
  }
  if(st.empty()){
   break;
  }
 }
}

template<class T>
void InOrderRecursive(Node<T>*root,void(*f)(Node<T>*)){
 if(!root){
  return;
 }
 InOrderRecursive<T>(root->left_, f);
 f(root);
 InOrderRecursive<T>(root->right_, f);
}

template<class T>
void PostOrder(Node<T>*root,void(*f)(Node<T>*)){
 std::stack<Node<T>*> st;
 Node<T>* temp=root;
 while(temp){
  while(temp->left_){
   st.push(temp);
   temp=temp->left_;
  }
  if(temp->right_){
   st.push(temp);
   temp=temp->right_;
   continue;
  }
  f(temp);
  while(!st.empty()){
   if(temp==st.top()->left_ && st.top()->right_){
    temp=st.top()->right_;
    break;
   }
   temp=st.top();
   f(temp);
   st.pop();
  }
  if(st.empty()){
   break;
  }
 }
}
template<class T>
void PostOrderRecursive(Node<T>*root,void(*f)(Node<T>*)){
 if(!root){
  return;
 }
 PostOrderRecursive<T>(root->left_, f);
 PostOrderRecursive<T>(root->right_, f);
 f(root);
}
template<class T>
void LevelOrder(Node<T>*root,void(*f)(Node<T>*)){
 std::queue<Node<T>*>Q;
 Q.push(root);
 Node<T> *temp;
 while(!Q.empty()){
  temp=Q.front();
  Q.pop();
  f(temp);
  if(temp->left_){
   Q.push(temp->left_);
  }
  if(temp->right_){
   Q.push(temp->right_);
  }
 }
 }

template <class T>
void Print(Node<T>*root){
 std::cout<<root->key_<<" ";
}
int main(){
 Node <int>*  a  = new Node<int> (2);
 Node <int> * b  = new Node<int> (3);
 Node <int >* c = new Node<int> (4,a,b);
 Node <int>* d= new Node<int>(3,c);
 Node <int>* e=new Node<int> (5);
 Node <int>* f=new Node<int>(10,d,e);
 Node <int> *g=new Node<int>(9);
 Node<int> *h=new Node<int>(11);
 Node<int>* i=new Node<int>(2,g,h);
 Node <int>* j=new Node<int>(5);
 Node <int>*k=new Node <int>(7);
 Node<int > *l=new Node<int>(8,j,k);
 Node<int >* m=new Node<int >(1,l,i);
 Node<int>*n=new Node<int >(12,f,m);
 LevelOrder(n, Print);
 std::cout<<std::endl;
 PreOrder(n, Print);
 std::cout<<std::endl;
 PreOrderRecursive(n, Print);
 std::cout<<std::endl;
 InOrder(n, Print);
 std::cout<<std::endl;
 InOrderRecursive(n, Print);
 std::cout<<std::endl;
 PostOrder(n, Print);
 std::cout<<std::endl;
 PostOrderRecursive(n, Print);
 std::cout<<std::endl;
}

