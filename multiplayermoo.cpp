//this took an hour to solve so even tho this failed tc 9 i am uploading this
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
vector<vector<int>>grid;
vector<vector<bool>>vis(255,vector<bool>(255,false));
vector<vector<pair<int,int>>>components;
vector<set<int>>adjcomponents;
vector<int>componentteams;
vector<int>componentsizes;
vector<vector<int>>componentids(255,vector<int>(255,-1));
vector<int>get_team_ids;
vector<pair<int,int>>dirs={{-1,0},{0,-1},{1,0},{0,1}};
int k=0;int n=0;int res1=0;int res2=0;int totalteams=0;
void dfs(int i,int j,int id){
	components[k].push_back({i,j});
	vis[i][j]=true;
	for(int l=0;l<4;++l){
		int di=i+dirs[l].first;int dj=j+dirs[l].second;
		if(di>=0&&di<n&&dj>=0&&dj<n&&grid[di][dj]==id&&!vis[di][dj]){
			dfs(di,dj,id);
		}
	}
}
int dfs2(int i,int id1,int id2,vector<bool>&vis){
	int ans=componentsizes[i];
	vis[i]=true;
	for(set<int>::iterator p=adjcomponents[i].begin();p!=adjcomponents[i].end();++p){
		if(!vis[*p]&&(componentteams[*p]==id1||componentteams[*p]==id2)){
			ans+=dfs2(*p,id1,id2,vis);
		}
	}
	return ans;
}
int main(){
	ifstream r("multimoo.in");
	ofstream o("multimoo.out");
	r>>n;
	grid.resize(n,vector<int>(n));
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			r>>grid[i][j];get_team_ids.push_back(grid[i][j]);
		}
	}
	sort(get_team_ids.begin(),get_team_ids.end());
	get_team_ids.erase(unique(get_team_ids.begin(),get_team_ids.end()),get_team_ids.end());
	totalteams=get_team_ids.size();
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			grid[i][j]=lower_bound(get_team_ids.begin(),get_team_ids.end(),grid[i][j])-get_team_ids.begin();
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(!vis[i][j]){
				components.push_back({});
				dfs(i,j,grid[i][j]);
				componentteams.push_back(grid[i][j]);
				++k;
			}
		}
	}
	adjcomponents.resize(k);
	componentsizes.resize(k);
	for(int i=0;i<k;++i){
		componentsizes[i]=components[i].size();
		res1=max(componentsizes[i],res1);
		for(int j=0;j<components[i].size();++j){
			int x=components[i][j].first;int y=components[i][j].second;
			componentids[x][y]=i;
		}
	}
	for(int i=0;i<k;++i){
		for(int j=0;j<components[i].size();++j){
			int x=components[i][j].first;int y=components[i][j].second;
			for(int l=0;l<4;++l){
				int di=x+dirs[l].first;int dj=y+dirs[l].second;
				if(di>=0&&di<n&&dj>=0&&dj<n&&componentids[di][dj]!=-1&&componentids[di][dj]!=componentids[x][y]){
					adjcomponents[i].insert(componentids[di][dj]);
				}
			}
		}
	}
	for(int i=0;i<k;++i){
		for(set<int>::iterator p=adjcomponents[i].begin();p!=adjcomponents[i].end();++p){
			vector<bool>vis(k,false);
			if(!vis[*p]){
				res2=max(res2,dfs2(i,componentteams[*p],componentteams[i],vis));
			}
		}
	}
	o<<res1<<endl;
	o<<res2<<endl;
}
