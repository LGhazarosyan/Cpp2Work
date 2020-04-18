#include<iostream>
//SelectionSort
void MySelectionSort(int *a,int count){
 int minIndex;
 for(int i=0;i<count-1;i++){
     minIndex=i;
  for(int j=i+1;j<count;j++){
   if(a[minIndex]>a[j]){
    minIndex=j;
   }
  }
  std::swap(a[minIndex],a[i]);
 }
}

//InsertionSort
void MyInsertionSort(int *a,int count){
 int temp,j;
 for(int i=1;i<count;i++){
  temp=a[i];
  j=i-1;
  while(j>=0 &&temp<a[j]){
  a[j+1]=a[j];
   j--;
  }
  a[j+1]=temp;
 }
}

//BubbleSort
void MyBubbleSort(int *a,int count){
    bool swapped;
 for(int i=0;i<count-1;i++){
     swapped=false;
  for(int j=1;j<count-i;j++){
   if(a[j-1]>a[j]){
    std::swap(a[j-1],a[j]);
    swapped=true;
   }
  }
  if (swapped==false){
      break;
      }
 }
}



int main(){
 int a[]={4,3,1,8,7,7,1,4,23,1,13,11,15,3,4,16,12,19,5,61,7,5,6,3,8,0,1,5,4,7} ;
MyBubbleSort(a, 30);
 for(int i=0;i<30;i++){
  std::cout<<a[i]<<"  ";
 }
}
