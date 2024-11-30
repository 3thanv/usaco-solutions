#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct dsu{
	int n;
	vector<ll>p,s;
	dsu(int l){
		n=l;
		p.resize(n,-1);s.resize(n,1);
	}
	int find(int u){
		return p[u]==-1?u:p[u]=find(p[u]);
	}
	bool unite(int u,int v){
		int pu=find(u);int pv=find(v);
		if(pu==pv){return false;}
		if(s[pu]>s[pv]){p[pv]=pu;s[pu]+=s[pv];}
		else{p[pu]=pv;s[pv]+=s[pu];}
		return true;
	}
};
int n,m;
vector<vector<int>>adj;
vector<vector<vector<ll>>>rem;
vector<int>cnt;
vector<int>origin;
set<pair<int,int>>no;
set<pair<int,int>>s;
//we need to make the queries
//we will repeatedly remove the minimum degree vertex from the graph
//if queries are saying "remove edge" from graph
//we just reverse the queries and add all those edges
void makeq(){
	origin=cnt;
	for(int i=0;i<n;++i){
		s.insert({cnt[i],i});
	}
	int p=0;
	while(s.size()>0){
		auto it=s.begin();
		int idx=(*it).second;
		rem.push_back({});
		rem[rem.size()-1].push_back({cnt[idx],idx});
		for(int j=0;j<adj[idx].size();++j){
			if(no.find({idx,adj[idx][j]})==no.end()&&no.find({adj[idx][j],idx})==no.end()){
				rem[rem.size()-1].push_back({adj[idx][j],idx});
				s.erase({cnt[adj[idx][j]],adj[idx][j]});
				cnt[adj[idx][j]]--;
				s.insert({cnt[adj[idx][j]],adj[idx][j]});
				no.insert({idx,adj[idx][j]});
			}
		}
		s.erase(it);
	}
}
void process(){
	reverse(rem.begin(),rem.end());
	ll maxsz=1;
	ll res=1;
	dsu ds(n);
	for(int i=0;i<rem.size();++i){
		for(int j=1;j<rem[i].size();++j){
			ds.unite(rem[i][j][0],rem[i][j][1]);
			maxsz=max(maxsz,ds.s[ds.find(rem[i][j][0])]);
			res=max(res,rem[i][0][0]*maxsz);
		}
	}
	cout<<res;
}
void inp(){
	cin>>n>>m;
	adj.resize(n);
	cnt.resize(n);
	for(int i=0;i<m;++i){
		int u,v;cin>>u>>v;u--;v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		cnt[u]++;cnt[v]++;
	}
}
int main() {
	inp();
	makeq();
	process();
}
