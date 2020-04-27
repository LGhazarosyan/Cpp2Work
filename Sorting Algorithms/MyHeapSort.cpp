//HeapSort
#include <iostream>
class PQueue{
 unsigned int capacity_;
 unsigned int size_;
 int *a_;
 
public:
  PQueue(unsigned int count):capacity_(count+1),size_(1),a_(new int[capacity_]){};
 ~PQueue(){
  delete[] a_;
 }
 int Pop(){
  if(size_==0){
   throw std::out_of_range("invalid Index");
  }
  std::swap(a_[1],a_[size_-1]);
  unsigned int parent=1,lchild,rchild;
  while(parent*2<size_-1){
   lchild=parent*2;
   rchild=lchild+1;
   if(rchild<size_-1){
    if(a_[rchild]<a_[lchild]){
     lchild=rchild;
    }
   }
   if(a_[lchild]<a_[parent]){
    std::swap(a_[lchild],a_[parent]);
    parent=lchild;
   }
   else{
    break;
   }
  }
  return a_[--size_];
 }
 void Push(int x){
  if(size_==capacity_){
   return;
  }
  a_[size_++]=x;
  unsigned int child=size_-1;
  unsigned int parent=child/2;
  while(parent>=1){
   if(a_[child]<a_[parent]){
    std::swap(a_[child],a_[parent]);
    child=parent;
    parent=child/2;
   }
   else{
    break;
   }
  }
 }
};
void MyHeapSort(int*a,unsigned int count  ){
 PQueue pq(count);
 for(unsigned i=0;i<count;i++){
  pq.Push(a[i]);
 }
 for(unsigned i=0;i<count;i++){
  a[i]=pq.Pop();
 }
}
int main(){
 int a[]={-1,-2,5,6,7,8,9,10,3,2,1,4,5,6,-1,7};
 MyHeapSort(a, 16);
 for(int i=0;i<16;i++){
  std::cout<<a[i]<<" ";
 }
}

