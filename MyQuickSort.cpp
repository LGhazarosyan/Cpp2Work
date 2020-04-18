//QuickSort
#include<iostream>
int Portition(int *a,int start,int end){
 int pivot=a[end];
 int left=end-1;
 int right=start;
 while(1){
  while(a[right]<pivot&&right<=end){
   right++;
  }
  while(a[left]>=pivot&&left>=start){
   left--;
  }
  if(right>left){
   break;
  }
  std::swap(a[right],a[left]);
 }
 std::swap(a[right],a[end]);
 return right;
}
void MyQuickSort(int *a,int start,int end){
 if(start>=end){
  return;
 }
 int index=Portition(a,start,end );
 MyQuickSort (a, start, index-1);
 MyQuickSort(a, index+1, end);
}
int main(){
 int a[]={-1,-2,5,6,7,8,9,10,3,2,1,4,5,6,-1,7};
 MyQuickSort(a,0,15 );
 for(int i=0;i<16;i++){
  std::cout<<a[i]<<" ";
 }
}
