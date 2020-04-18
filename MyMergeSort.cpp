#include<iostream>
void Merge(int *a,int first,int last,int p){
 int countL=p-first;
 int countR=last-p+1;
 int* L=new int[countL];
 int* R=new int [countR];
 for(int i=0;i<countL;i++){
  L[i]=a[first+i];
 }
 for(int i=0;i<countR;i++){
  R[i]=a[p+i];
 }
 int l=0,r=0;
 for(int i=first;i<=last;i++){
  if(L[l]<R[r]&&l<countL){
   a[i]=L[l++];
   continue;
  }
  if(r<countR){
   a[i]=R[r++];
   continue;
  }
  a[i]=L[l++];
 }
 delete[]R;
 delete[]L;
}
void MyMergeSort(int *a,int first,int last){
 if(last==first){
  return;
 }
 int p=(last-first+1)/2+first;
 MyMergeSort(a, first,p-1);
 MyMergeSort(a,p,last);
 Merge(a,first,last,p);
}
