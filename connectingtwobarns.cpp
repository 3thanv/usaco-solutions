#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
void dfs(vector<vector<int>>&adj,vector<bool>&vis,int u,int q,vector<vector<long long>>&comp){
  vis[u]=true;
  comp[q].push_back(u);
  for(int v:adj[u]){
    if(!vis[v]){vis[v]=true;dfs(adj,vis,v,q,comp);}
  }
}
long long llmin(long long i,long long j){
  return i<j?i:j;
}
long long sq(long long i,long long j){
  return (j-i)*(j-i);
}
long long closest(long long i,long long j,long long k){
  return abs(i-k)>abs(j-k)?j:i;
}
long long bsearch(vector<long long>&c,long long t){
  int lo=0;int hi=c.size()-1;
  int mid=0;
  if(c[lo]>=t){
    return c[lo];
  }
  else if (c[hi]<=t){
    return c[hi];
  }
  while(lo<=hi){
    int mid=(lo+hi)/2;
    if(c[mid]==t){
      return c[mid];
    }
    else if (c[mid]<t){
      if(mid+1<c.size()&&c[mid+1]>=t){
        return closest(c[mid],c[mid+1],t);
      }
      lo=mid+1;
    }
    else if (c[mid]>t){
      if(mid-1>=0&&c[mid-1]<=t){
        return closest(c[mid],c[mid-1],t);
      }
      hi=mid-1;
    }
  }
  return mid;
}
void solve(){
  int n,m;cin>>n>>m;
  int s=0;
  int startc=-1;
  int endc=-1;
  vector<vector<int>>adj(n);
  vector<vector<long long>>comp;
  vector<bool>vis(n,false);
  for(int i=0;i<m;++i){
    int u,v;cin>>u>>v;u--;v--;adj[u].push_back(v);adj[v].push_back(u);
  }
  for(int i=0;i<n;++i){
    if(!vis[i]){
      comp.push_back({});
      dfs(adj,vis,i,s,comp);
      ++s;
    }
  }
  for(int i=0;i<s;++i){
    for(int j=0;j<comp[i].size();++j){
      if(comp[i][j]==0){
        startc=i;
      }
      if (comp[i][j]==n-1){
        endc=i;
      }
    }
    sort(comp[i].begin(),comp[i].end());
  }
  vector<long long>diststart(s,INT64_MAX);
  vector<long long>distend(s,INT64_MAX);
  for(int i=0;i<s;++i){
    for(int j=0;j<comp[i].size();++j){
      int closest1=bsearch(comp[endc],comp[i][j]);
      distend[i]=llmin(sq(closest1,comp[i][j]),distend[i]);
      int closest=bsearch(comp[startc],comp[i][j]);
      diststart[i]=llmin(sq(closest,comp[i][j]),diststart[i]);
    }
  }
  long long res=INT64_MAX;
  for(int i=0;i<s;++i){
    res=llmin(res,diststart[i]+distend[i]);
  }
  cout<<res<<'\n';
}
int main(){
  int t;cin>>t;
  for(int i=0;i<t;++i){
    solve();
  }
}
