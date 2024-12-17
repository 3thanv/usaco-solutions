#include <bits/stdc++.h>
using namespace std;
#define ll long long
//we can solve this with a sweep line and coordinate compression
int n,k;
int distinct;
ll venetian;
ll res=0;
set<pair<int,int>>lines;
vector<int>a;
vector<vector<int>>segs;
vector<vector<vector<int>>>events;
vector<int>cnttree;
//events will be stored in this form
//type, index, add
//if type is 1 and add is 1 then add segs[idx] to sweep line
//if type is 1 and add is 0 then remove it from active set
//if type is 2 then query set to see if you can remove the tree
void cmp(){//compression
	vector<int>c;
	unordered_map<int,int>idx;
	for(int i=0;i<n;++i){
		c.push_back(a[i]);
	}
	for(int i=0;i<k;++i){
		c.push_back(segs[i][0]);
		c.push_back(segs[i][1]);
	}
	sort(c.begin(),c.end());
	c.erase(unique(c.begin(),c.end()),c.end());
	distinct=c.size();
	for(int i=0;i<distinct;++i){
		idx[c[i]]=i;
	}
	for(int i=0;i<n;++i){
		a[i]=idx[a[i]];
	}
	for(int i=0;i<k;++i){
		segs[i][0]=idx[segs[i][0]];
		segs[i][1]=idx[segs[i][1]];
	}
}
void makeevents(){
	events.resize(distinct);
	for(int i=0;i<n;++i){
		events[a[i]].push_back({2,i,-1,-1});
	}
	for(int i=0;i<k;++i){
		events[segs[i][0]].push_back({1,i,1,segs[i][2]});
		events[segs[i][1]].push_back({1,i,0,segs[i][2]});
	}
}
void calcp(){
	vector<int>psum(distinct);
	cnttree.resize(k);
	for(int i=0;i<n;++i){
		psum[a[i]]++;
	}
	for(int i=1;i<distinct;++i){
		psum[i]+=psum[i-1];
	}
	for(int i=0;i<k;++i){
		if(segs[i][0]-1>=0){
			cnttree[i]=psum[segs[i][1]]-psum[segs[i][0]-1];
		}
		else{
			cnttree[i]=psum[segs[i][1]];
		}
	}
}
void sweep(){
	ll totaltree=0;
	venetian=0;
	vector<ll>remember;
	remember.resize(k);
	for(int i=0;i<distinct;++i){
		for(int j=0;j<events[i].size();++j){//hold off any remove queries until the end
			if(events[i][j][0]==1&&events[i][j][2]==1){
				lines.insert({cnttree[events[i][j][1]]-events[i][j][3]+venetian,events[i][j][1]});
				remember[events[i][j][1]]=cnttree[events[i][j][1]]-events[i][j][3]+venetian;
			}
		}
		for(int j=0;j<events[i].size();++j){
			if(lines.size()==0){
				res++;
			}
			else{
				if(events[i][j][0]==2&&(*lines.begin()).first-venetian-1>=0){
					venetian++;res++;
				}
			}
		}
		for(int j=0;j<events[i].size();++j){//hold off any remove queries until the end
			if(events[i][j][0]==1&&events[i][j][2]==0){
				lines.erase({remember[events[i][j][1]],events[i][j][1]});
			}
		}
	}
}
void solve(){
	cnttree.clear();
	lines.clear();
	segs.clear();
	a.clear();
	events.clear();
	res=0;
	cin>>n>>k;
	a.resize(n);
	for(int i=0;i<n;++i){
		cin>>a[i];
	}
	for(int i=0;i<k;++i){
		int l,r,cnt;cin>>l>>r>>cnt;
		segs.push_back({l,r,cnt});
	}
	cmp();
	makeevents();
	calcp();
	sweep();
	cout<<res<<'\n';
}
int main() {
	int t;cin>>t;
	while(t--){
		solve();
	}
}
