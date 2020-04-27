//maxArea in histogram
#include<iostream>
#include<stack>
#include<utility>
int MaxArea(int *a,int count){
 int maxArea=0;
 int k=0;
 std::stack<std::pair<int,int>> s;
 std::pair <int,int> p;
 for(int i=0;i<count;i++){
  if(s.empty()){
   p.first=a[i];
   p.second=k+1;
   s.push(p);
   k=0;
   continue;
  }
  if(a[i]==s.top().first){
   s.top().second+=k+1;
   k=0;
   continue;
  }
  if(a[i]>s.top().first){
   p.first=a[i];
   p.second=k+1;
   s.push(p);
   k=0;
   continue;
  }
   p=s.top();
   s.pop();
   if(p.first*(p.second+k)>maxArea){
    maxArea=p.first*(p.second+k);
   }
    k+=p.second;
   i--;
 }
 k=0;
 while(!s.empty()){
  p=s.top();
  s.pop();
  if((k+p.second)*p.first>maxArea){
   maxArea=(k+p.second)*p.first;
  }
  k+=p.second;
 }
 return maxArea;
}
int main(){
   int a[]={10,1,3,2,9,4,2,3,1,2,33,25,25,4,2,5,7,10,19,20};
  std::cout<<MaxArea(a,20);
}
