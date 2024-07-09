#include <bits/stdc++.h>
using namespace std;
#define ll long long
int t[1000000];
void update(int v,int tl,int tr,int l,int r){
	if(l>r){return;}
	if(tl==l&&tr==r){t[v]+=1;return;}
	int tm=(tl+tr)/2;
	update(2*v,tl,tm,l,min(r,tm));
	update(2*v+1,tm+1,tr,max(l,tm+1),r);
}
int get(int v,int tl,int tr,int idx){
	if(tl==tr){
		return t[v];
	}
	int tm=(tl+tr)/2;
	if(idx<=tm){
		return t[v]+get(2*v,tl,tm,idx);
	}
	return t[v]+get(2*v+1,tm+1,tr,idx);
}
int n,p;
vector<pair<int,int>>posts;
map<int,vector<pair<int,int>>>xval;
map<int,vector<pair<int,int>>>yval;
map<int,vector<int>>xval1;
map<int,vector<int>>yval1;
map<pair<int,int>,int>lookup;
vector<vector<pair<int,int>>>adj;
vector<int>id;
vector<int>idtopoint;
vector<int>direction;
vector<int>x;
vector<int>y;
vector<ll>psum;
vector<vector<int>>cows;
vector<int>passes;
ll manhattan(ll x1,ll y1,ll x2,ll y2){
	return abs(x1-x2)+abs(y1-y2);
}
void makegraph(){ //we make the directed graph
	sort(x.begin(),x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
	sort(y.begin(),y.end());
	y.erase(unique(y.begin(),y.end()),y.end());
	for(auto&[key,val]:xval){
		sort(val.begin(),val.end());
	}
	for(auto&[key,val]:yval){
		sort(val.begin(),val.end());
	}
	//0 1 2 3 correspond to NESW
	for(int i=0;i<x.size();++i){
		for(int j=0;j<xval[x[i]].size();j+=2){
			xval1[x[i]].push_back(xval[x[i]][j].first);
		}
	}
	for(int i=0;i<y.size();++i){
		for(int j=0;j<yval[y[i]].size();j+=2){
			yval1[y[i]].push_back(yval[y[i]][j].first);
		}
	}
	for(int i=0;i<x.size();++i){
		for(int j=0;j<xval[x[i]].size();j+=2){
			adj[xval[x[i]][j].second].push_back({0,xval[x[i]][j+1].second});
			adj[xval[x[i]][j+1].second].push_back({2,xval[x[i]][j].second});
		}
	}
	for(int i=0;i<y.size();++i){
		for(int j=0;j<yval[y[i]].size();j+=2){
			adj[yval[y[i]][j].second].push_back({1,yval[y[i]][j+1].second});
			adj[yval[y[i]][j+1].second].push_back({3,yval[y[i]][j].second});
		}
	}
	for(int i=0;i<p;++i){
		sort(adj[i].begin(),adj[i].end());
	}
}
void readinput(){//what it looks like
	cin>>n>>p;
	id.resize(p);
	idtopoint.resize(p);
	adj.resize(p);
	posts.resize(p);
	direction.resize(p);
	passes.resize(p);
	psum.resize(p+1);
	for(int i=0;i<p;++i){
		cin>>posts[i].first>>posts[i].second;
		xval[posts[i].first].push_back({posts[i].second,i});
		yval[posts[i].second].push_back({posts[i].first,i});
		x.push_back(posts[i].first);
		y.push_back(posts[i].second);
		lookup[{posts[i].first,posts[i].second}]=i;
	}
	for(int i=0;i<n;++i){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		cows.push_back({x1,y1,x2,y2});
	}
}
void traversegraph(){//we assign each cow an id in order of traversal and get prefix sum for perimeter of graph
	vector<bool>vis(p,false);
	queue<int>q;
	int currid=0;
	q.push(0);
	while(!q.empty()){
		int k=q.front();vis[k]=true;
		q.pop();
		for(auto&c:adj[k]){
			if(c.second==0&&currid==p-1){
				psum[currid+1]=psum[currid]+manhattan(posts[k].first,posts[k].second,posts[c.second].first,posts[c.second].second);
				direction[currid]=c.first;
				break;
			}
			if(!vis[c.second]){
				id[c.second]=currid+1;
				idtopoint[currid+1]=c.second;
				vis[c.second]=true;
				psum[currid+1]=psum[currid]+manhattan(posts[k].first,posts[k].second,posts[c.second].first,posts[c.second].second);
				direction[currid]=c.first;
				q.push(c.second);
				currid++;
				break;
			}
		}
	}
}
pair<int,int> getindex(int x1,int y1){
	if(lookup.find({x1,y1})!=lookup.end()){
		return {id[lookup[{x1,y1}]],-1};
	}
	if(yval.find(y1)!=yval.end()){
		auto k=upper_bound(yval1[y1].begin(),yval1[y1].end(),x1);
		if(k!=yval1[y1].begin()){
			k--;
			int idx=k-yval1[y1].begin();
			if(yval[y1][idx*2+1].first>=x1){
				return {id[lookup[{yval[y1][idx*2+1].first,y1}]],1};
			}
		}
	}
	auto k1=upper_bound(xval1[x1].begin(),xval1[x1].end(),y1);
	k1--;
	int idx=k1-xval1[x1].begin();
	return {id[lookup[{x1,xval[x1][idx*2+1].first}]],0};
}
int casework(int type,int idx){
	if(idx==0){
		if(type==0&&((direction[p-1]==0)||(direction[0]==1||direction[0]==3))){
			return p-1;
		}
		if(type==1&&((direction[p-1]==1)||(direction[0]==0||direction[0]==2))){
			return p-1;
		}
	}
	else {
		if(type==0&&((direction[idx-1]==0)||(direction[idx]==1||direction[idx]==3))){
			return idx-1;
		}
		if(type==1&&((direction[idx-1]==1)||(direction[idx]==0||direction[idx]==2))){
			return idx-1;
		}
	}
	return idx;
}
//0 1 2 3 are north south east west
void solve(int i){
	int x1,y1,x2,y2;
	ll p1,p2;p1=p2=0;//p1 is increase idx1 to get idx2, p2 is increase idx2 to get idx1
	x1=cows[i][0];y1=cows[i][1];x2=cows[i][2];y2=cows[i][3];
	auto[idx1,type1]=getindex(x1,y1);
	auto[idx2,type2]=getindex(x2,y2);
	idx1=casework(type1,idx1);
	idx2=casework(type2,idx2);
	int sx,sy,ex,ey;
	ex=posts[idtopoint[idx2]].first;
	ey=posts[idtopoint[idx2]].second;
	sx=posts[idtopoint[idx1]].first;
	sy=posts[idtopoint[idx1]].second;
	//p1 covers interval [idx1,idx2] or interval [idx1,p-1],[0,idx2]
	if(idx2>=idx1){
		p1=psum[idx2]+manhattan(ex,ey,x2,y2)-psum[idx1]-manhattan(sx,sy,x1,y1);
	}
	else if(idx1>idx2){
		p1=psum[idx2]+manhattan(ex,ey,x2,y2)+(psum[p]-psum[idx1]-manhattan(sx,sy,x1,y1));
	}
	p2=psum[p]-p1;
	if(p2>p1){
		if(type1==-1){
			update(1,0,p-1,idx1,idx1);
		}
		if(idx1<idx2){
			update(1,0,p-1,idx1+1,idx2);
		}
		else if(idx1>idx2){
			update(1,0,p-1,idx1+1,p-1);
			update(1,0,p-1,0,idx2);
		}
	}
	else{
		if(type2==-1){
			update(1,0,p-1,idx2,idx2);
		}
		if(idx2<idx1){
			update(1,0,p-1,idx2+1,idx1);
		}
		else if(idx2>idx1){
			update(1,0,p-1,idx2+1,p-1);
			update(1,0,p-1,0,idx1);
		}
	}
}
void addvals(){
	for(int i=0;i<n;++i){
		solve(i);
	}
}
int main(){
	readinput();
	makegraph();
	traversegraph();
	addvals();
	for(int i=0;i<p;++i){
		passes[idtopoint[i]]=get(1,0,p-1,i);
	}
	for(int i=0;i<p;++i){
		cout<<passes[i]<<'\n';
	}
}