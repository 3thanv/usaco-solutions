#include <bits/stdc++.h>
using namespace std;
//create two merge sort trees to answer queries
//first one answers query, given coordinates i, find how many j such that lj<li have rj>=li+k
//second one answer query, find number of j where lj is between [li,ri-k] such that rj-lj>=k
//now we just use the trees
//runs in nlog^2n
int n;
vector<vector<int>>lines;
vector<pair<int,int>>tmp;
vector<int>x1;
vector<int>y2;
vector<int>s2;
vector<vector<int>>t1;
vector<vector<int>>t2;
void build(int v,int tl,int tr,vector<int>&p,vector<vector<int>>&t){
	if(tl==tr){
		t[v].push_back(p[tl]);return;
	}
	int tm=(tl+tr)/2;
	build(2*v,tl,tm,p,t);
	build(2*v+1,tm+1,tr,p,t);
	merge(t[2*v].begin(),t[2*v].end(),t[2*v+1].begin(),t[2*v+1].end(),back_inserter(t[v]));
}
int get1(int v,int tl,int tr,int l,int r,int targ,vector<vector<int>>&t){
	if(l>r){
		return 0;
	}
	else if(tl==l&&tr==r){
		int q=lower_bound(t[v].begin(),t[v].end(),targ)-t[v].begin();
		return t[v].size()-q;
	}
	int tm=(tl+tr)/2;
	return get1(2*v,tl,tm,l,min(r,tm),targ,t)+get1(2*v+1,tm+1,tr,max(l,tm+1),r,targ,t);
}
int query1(int lb,int k){
	auto q=lower_bound(x1.begin(),x1.end(),lb);
	if(q==x1.begin()){
		return 0;
	}
	q--;
	return get1(1,0,n-1,0,q-x1.begin(),lb+k,t1);
}
int query2(int lb,int ub,int sum){
	auto q1=lower_bound(x1.begin(),x1.end(),lb);
	auto q2=upper_bound(x1.begin(),x1.end(),ub);
	q2--;
	return get1(1,0,n-1,q1-x1.begin(),q2-x1.begin(),sum,t2);
}
int main(){
	cin>>n;
	t1.resize(4*n);
	t2.resize(4*n);
	for(int i=0;i<n;++i){
		int l,r,k;cin>>l>>r>>k;
		lines.push_back({l,r,k});
		tmp.push_back({l,r});
	}
	sort(tmp.begin(),tmp.end());
	for(int i=0;i<n;++i){
		x1.push_back(tmp[i].first);
		y2.push_back(tmp[i].second);
		s2.push_back(tmp[i].second-tmp[i].first);
	}
	build(1,0,n-1,y2,t1);
	build(1,0,n-1,s2,t2);
	for(int i=0;i<n;++i){
		int ans=0;
		ans+=query1(lines[i][0],lines[i][2]);
		ans+=query2(lines[i][0],lines[i][1]-lines[i][2],lines[i][2]);
		ans--;
		cout<<ans<<'\n';
	}
}