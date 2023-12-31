#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;
#define ll long long
long long llmin(ll i,ll j){
	return i>j?j:i;
}
long long llmax(ll i,ll j){
	return i<j?j:i;
}
#define fastio cin.tie(0)->sync_with_stdio(false);
#define FOR(a,b) for(int i=a;i<b;++i)
#define vi vector<int>
#define vll vector<ll>
vector<vector<int>>dirs={{0,1},{0,-1},{1,0},{-1,0}};
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
//if we can reach h index h then obv we can for h+1
//so thus bsearch on ans
//to check sort the array, find the first idx such that mid>a[idx]
//we need to increase idx-(n-mid) of these to mid, indices [(n-mid),idx] has least cost to achieve an h if we increase
//we can only do this if the sum of the differences is less than l*k (maximum)
//and also the maximum difference between mid and ai is less than k
//so we can solve in nlogn
ll n,k,l;vll a;
bool check(ll mid){
	ll idx=lower_bound(a.begin(),a.end(),mid)-a.begin()-1;
	if(n-idx>=mid){
		return true;
	}
	ll m=0;
	ll sum=0;
	for(int c=idx;c>llmax(1,n-mid);c--){
		m=llmax(m,mid-a[c]);
		sum+=mid-a[c];
	}
	return (sum<=l*k&&m<=k);
}
int main(){
	cin>>n>>k>>l;
	ll valid=-1;
	a.resize(n+1);
	FOR(1,n+1){
		cin>>a[i];
	}
	sort(a.begin(),a.end());
	ll lo=0;ll hi=n+5;ll mid;
	while(lo<=hi){
		mid=(lo+hi)/2;
		if(check(mid)){
			lo=mid+1;
			valid=mid;
		}
		else {
			hi=mid-1;
		}
	}
	cout<<valid<<endl;
}