//find maximum valid length
#include<iostream>
#include<string>
#include<stack>
#define open '{'
#define close '}'
unsigned long MaxValidIndex(std::string s){
 unsigned long maxLength=0;
 unsigned long size=s.size();
 std::stack<char> cont;
  long  long start=-1;
 for(unsigned long i=0;i<size;i++){
  if(s[i]==open){
   cont.push(s[i]);
   if(start==-1){
    start=i;
   }
   continue;
  }
  if(cont.empty()){
   if(start!=-1){
    if(maxLength<i-start){
     maxLength=i-start;
    }
   }
   start=-1;
   continue;
  }
  cont.pop();
}
 if(start!=-1 && cont.empty() ){
  if(size-start+1>maxLength){
   maxLength=size-start;
  }
 }
 return maxLength;
}
int main(){
 std::string s="{}{}{}{}{}}}}}}{}{}{}{{{{}}}}}}}}}}}}}";
 std::cout<<MaxValidIndex(s);
}
