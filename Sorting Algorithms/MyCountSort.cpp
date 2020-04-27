//CountSort
#include<iostream>
void MyCountSort(int *a,int count){
 int min=a[0];
 int max=a[0];
 for(int i=1;i<count;i++){
  if(a[i]<min){
   min=a[i];
  }
  if(a[i]>max){
   max=a[i];
  }
 }
 int*helper=new int[max-min+1];
 for(int i=0;i<max-min+1;i++){
  helper[i]=0;
 }
 for(int i=0;i<count;i++){
  helper[a[i]-min]++;
 }
 int index=0;
 
 for(int i=0;i<count;i++){
  if(helper[index]){
   a[i]=index+min;
   helper[index]--;
   continue;
  }
  index++;
  i--;
 }
 
}

int main(){
 int a[]={-1,-2,5,6,7,8,9,10,3,2,1,4,5,6,-1,7};
 MyCountSort(a, 16 );
 for(int i=0;i<16;i++){
  std::cout<<a[i]<<" ";
 }
}
