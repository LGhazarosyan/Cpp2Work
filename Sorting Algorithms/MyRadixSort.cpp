#include<iostream>
void MyRadixSort(int *a,unsigned int count){
 int * res=new int[count];
 int * temp=new int [count];
 int* helper=new int[10];
 int ind=0;
 for(int i=0;i<10;i++){
  helper[i]=0;
 }
 int k=1;
 bool cont=0;
 int min=a[0];
 for(int i=0;i<count;i++){
  if(a[i]<min){
   min=a[i];
  }
  res[i]=a[i];
 }
 while(1){
  cont=0;
  for(int i=0;i<count;i++){
   ind=((res[i]-min)%(10*k))/k;
   helper[ind]++;
   if(ind){
    cont=1;
   }
  }
  if(!cont){
   break;
  }
  for(int i=0;i<9;i++){
   helper[i+1]+=helper[i];
  }
  for(int i=count-1;i>=0;--i){
  ind=((res[i]-min)%(10*k))/k;
   temp[helper[ind]-1]=res[i];
   helper[ind]--;
  }
  k*=10;
  std::swap(res,temp);
  for(int i=0;i<10;i++){
   helper[i]=0;
  }
 }
 for(int i=0;i<count;i++){
  a[i]=res[i];
 }
}
int main(){
 int a[]={10,2,3,19,100,2,3,4,7,19,2,20,100,1000,2345,23,456,78,-10,13,-100,12,56,47,89,900,67,45,56,77,8,9,10};
 MyRadixSort(a, 33);
 for(int i=0;i<33;i++){
  std::cout<<a[i]<<" ";
 }
}
