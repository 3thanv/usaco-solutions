#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
long long llmin(ll i,ll j){
	return i>j?j:i;
}
long long llmax(ll i,ll j){
	return i>j?j:i;
}
#define fastio cin.tie(0)->sync_with_stdio(false);
#define FOR(a,b) for(int i=a;i<b;++i)
#define vi vector<int>
#define vll vector<ll>
long long gcd(long long a,long long b){
	return b?gcd(b,a%b):a;
}
vector<int> monostack(vector<int>&arr){//decreasing stack is very easy too 
	stack<int>s;
	vector<int>output;
	for(int i=0;i<arr.size();++i){
		while(s.size()>0&&s.top()>arr[i]){
			s.pop();
		}
		s.push(arr[i]);
	}
	while(s.size()>0){
		output.push_back(s.top());
		s.pop();
	}
	return output;
}
int l2(int p){
	return 31-__builtin_clz(p);
}
void sps(vector<vector<int>>&sps,vector<int>&arr){
	int n=arr.size();
	int k=l2(n);
	sps.resize(k+1,vector<int>(n));
	for(int i=0;i<n;++i){
		sps[0][i]=arr[i];
	}
	for(int i=1;i<=k;++i){
		for(int j=0;j+(1<<i)<=n;++j){
			sps[i][j]=min(sps[i-1][j],sps[i-1][j+(1<<(i-1))]);//for range max static just change ez
		}
	}
}
struct dsubysize{
	vector<int>p,s;
	dsubysize(int n){
		s.resize(n,1);
		p.resize(n,-1);
	}
	int find(int u){
		return p[u]==-1?u:p[u]=find(p[u]);
	}
	bool unite(int u,int v){
		int pu,pv;pu=find(u);pv=find(v);
		if(pu==pv){return false;}
		if(s[pu]>s[pv]){p[pv]=pu;s[pu]+=s[pv];return true;}
		p[pu]=pv;s[pv]+=s[pu];return true;
	}
};
struct dsubyrank{
	vector<int>p,r;
	dsubyrank(int n){
		r.resize(n,0);
		p.resize(n,-1);
	}
	int find(int u){
		return p[u]==-1?u:p[u]=find(p[u]);
	}
	bool unite(int u,int v){
		int pu,pv;pu=find(u);pv=find(v);
		if(pu==pv){return false;}
		if(r[pu]>r[pv]){p[pv]=pu;return true;}
		p[pu]=pv;++r[pv];return true;
	}
};
struct fenwick{
	vector<int>bit;
	int n;
	fenwick(int k){
		this->n=k;
		bit.resize(k,0);
	}
	fenwick(vector<int> const&a) : fenwick(a.size()){//build in o(n)
		for(int i=0;i<n;++i){
			bit[i]+=a[i];
			int r=i|(i+1);
			if(r<n)bit[r]+=bit[i];
		}
	}
	int sum(int r){//sum from 0-r
		int ret=0;
		for(;r>=0;r=(r&(r+1))-1){
			ret+=bit[r];
		}
		return ret;
	}
	int sum(int l,int r){//returns sum in range
		return sum(r)-sum(l-1);
	}
	void update(int idx,int delta){//updates element at idx i
		for(;idx<n;idx|=(idx+1)){
			bit[idx]+=delta;
		}
	}
};
void news(int p,set<int>&remove,vector<vector<int>>&cx,vector<vector<int>>&cy){
	int n=cx.size();
	if(p==0){
		int k=n-1;
		while(k>=0&&remove.find(cx[k][2])!=remove.end()){
			--k;
		}
		if(k>=0){
			remove.insert(cx[k][2]);
		}
	}
	if(p==1){
		int k=0;
		while(k<n&&remove.find(cx[k][2])!=remove.end()){
			++k;
		}
		if(k<n){
			remove.insert(cx[k][2]);
		}
	}
	if(p==2){
		int k=n-1;
		while(k>=0&&remove.find(cy[k][2])!=remove.end()){
			--k;
		}
		if(k>=0){
			remove.insert(cy[k][2]);
		}
	}
	if(p==3){
		int k=0;
		while(k<n&&remove.find(cy[k][2])!=remove.end()){
			++k;
		}
		if(k<n){
			remove.insert(cy[k][2]);
		}
	}
}
int main(){
	ifstream r("reduce.in");
	ofstream o("reduce.out");
	int n;r>>n;
	vector<vector<int>>cx;
	vector<vector<int>>cy;
	vector<vector<int>>original;
	FOR(0,n){
		int x,y;r>>x>>y;
		cx.push_back({x,y,i});
		cy.push_back({y,x,i});
		original.push_back({x,y});
	}
	sort(cx.begin(),cx.end());
	sort(cy.begin(),cy.end());
	int minarea=2e9;
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j){
			for(int k=0;k<4;++k){
				set<int>remove;
				int maxx=-2e9;
				int maxy=-2e9;
				int minx=2e9;
				int miny=2e9;
				news(i,remove,cx,cy);
				news(j,remove,cx,cy);
				news(k,remove,cx,cy);
				for(int l=0;l<n;++l){
					if(remove.find(l)==remove.end()){
						maxx=max(maxx,original[l][0]);
						minx=min(minx,original[l][0]);
						maxy=max(maxy,original[l][1]);
						miny=min(miny,original[l][1]);
					}
				}
				if(maxx==-2e9){
					minarea=0;
				}
				else {
					minarea=min(minarea,(maxx-minx)*(maxy-miny));
				}
			}
		}
	}
	o<<minarea;
}