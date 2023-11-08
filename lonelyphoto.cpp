#include <iostream>
#include <vector>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;cin>>n;
  long long res=0;
  string s;cin>>s;
  vector<long long> g;
  vector<long long> h;
  for(int i=0;i<n;++i){
    if(s[i]=='G'){
      g.push_back(i);
    }
    else{
      h.push_back(i);
    }
  }
  for(int i=0;i<g.size();++i){
    if(i==0){
      if(g[i]-1>0){
        res+=g[i]-1;
      }
      if(i+1<g.size()&&g[i+1]-g[i]-2>0){
        res+=g[i+1]-g[i]-2;
      }
      if(i+1>=g.size()&&n-1-g[i]-1>0){
        res+=n-1-g[i]-1;
      }
      if(i+1>=g.size()&&n-1-g[i]>0&&g[i]>0){
        res+=(n-1-g[i])*(g[i]);
      }
      if(i+1<g.size()&&g[i+1]-g[i]-1>0&&g[i]>0){
        res+=(g[i+1]-g[i]-1)*(g[i]);
      }
    }
    else if(i==g.size()-1){
      if(i-1>=0&&g[i]-g[i-1]-2>0){
        res+=g[i]-g[i-1]-2;
      }
      if(n-1-g[i]-1>0){
        res+=n-1-g[i]-1;
      }
      if(n-1-g[i]>0&&g[i]-g[i-1]-1>0){
        res+=(n-1-g[i])*(g[i]-g[i-1]-1);
      }
    }
    else {
      long long j=g[i]-g[i-1];
      long long p=g[i+1]-g[i];
      if(j-2>0){
        res+=j-2;
      }
      if(p-2>0){
        res+=p-2;
      }
      if(p-1>0&&j-1>0){
        res+=(p-1)*(j-1);
      }
    }
  }
  for(int i=0;i<h.size();++i){
    if(i==0){
      if(h[i]-1>0){
        res+=h[i]-1;
      }
      if(i+1<h.size()&&h[i+1]-h[i]-2>0){
        res+=h[i+1]-h[i]-2;
      }
      if(i+1>=h.size()&&n-1-h[i]-1>0){
        res+=n-1-h[i]-1;
      }
      if(i+1>=h.size()&&n-1-h[i]>0&&h[i]>0){
        res+=(n-1-h[i])*(h[i]);
      }
      if(i+1<h.size()&&h[i+1]-h[i]-1>0&&h[i]>0){
        res+=(h[i+1]-h[i]-1)*(h[i]);
      }
    }
    else if(i==h.size()-1){
      if(i-1>=0&&h[i]-h[i-1]-2>0){
        res+=h[i]-h[i-1]-2;
      }
      if(n-1-h[i]-1>0){
        res+=n-1-h[i]-1;
      }
      if(n-1-h[i]>0&&h[i]-h[i-1]-1>0){
        res+=(n-1-h[i])*(h[i]-h[i-1]-1);
      }
    }
    else {
      long long j=h[i]-h[i-1];
      long long p=h[i+1]-h[i];
      if(j-2>0){
        res+=j-2;
      }
      if(p-2>0){
        res+=p-2;
      }
      if(p-1>0&&j-1>0){
        res+=(p-1)*(j-1);
      }
    }
  }
  cout<<res;
}