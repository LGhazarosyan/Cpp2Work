//MaxArea in histogram
#include<iostream>
int MaxArea(int *a,int start,int end){
if(start>end){
  return 0;
 }
 if(start==end){
  return a[start];
 }
 int minIndex=start;
 for(int i=start+1;i<=end;i++){
  if(a[i]<a[minIndex]){
   minIndex=i;
  }
 }
 int Area=a[minIndex]*(end-start+1);
 int left=MaxArea(a, minIndex+1, end);
 int right=MaxArea(a, start, minIndex-1);
 if(left>Area){
  Area=left;
 }
 if(right>Area){
  Area=right;
 }
 return Area;
}

int main(){
 int a[]={6,10,7,14,15,2,8,7,7,7};
 std::cout<<MaxArea(a,0,9);
}
