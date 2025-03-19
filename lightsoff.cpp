#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=200005;
int n,t;
vector<pair<int,int>>qu;
int dp[41][(1<<20)];
int ans[MAXN];
int shiftright(int mask){
    int p=(mask&1);mask>>=1;mask|=(p<<(n-1));return mask;
}
int rangeset(int l,int r){
    return ((1<<r)-1)^((1<<(l-1))-1);
}
int getxor(int b,int numshift){
    int cnt=numshift+1;
    int curridx=b+1;
    int res=0;
    while(cnt>0){
        if(cnt>=curridx){
            res^=rangeset(1,curridx);
            cnt-=curridx;curridx=n;
        }
        else {
            res^=rangeset(curridx-cnt+1,curridx);cnt=0;
        }
    }
    return res;
}
void calc(){
    for(int i=0;i<=2*n;++i){
        for(int j=0;j<(1<<n);++j){
            dp[i][j]=0;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=2*n;++i){
        for(int j=0;j<(1<<n);++j){
            if(dp[i-1][j]){
                for(int k=0;k<n;++k){
                    dp[i][(j^getxor(k,i-1))]=1;
                }
            }
        }
    }
}
void iter(int move){
    for(int i=0;i<t;++i){
        int sw=qu[i].second;
        int accmask=0;
        for(int j=0;j<move;++j){
            accmask^=sw;sw=shiftright(sw);
        }
        if(dp[move][accmask^qu[i].first]){
            ans[i]=min(ans[i],move);
        }
    }
}
void inp(){
    cin>>t>>n;
    for(int i=0;i<t;++i){
        int light=0;int sw=0;
        for(int j=0;j<n;++j){
            char c;cin>>c;
            light+=((c-'0')<<(n-j-1));
        }
        for(int j=0;j<n;++j){
            char c;cin>>c;
            sw+=((c-'0')<<(n-j-1));
        }
        qu.push_back({light,sw});
    }
    for(int i=0;i<MAXN;++i){
        ans[i]=MAXN;
    }
}
int main() {
    inp();
    calc();
    for(int i=0;i<=2*n;++i){
        iter(i);
    }
    for(int i=0;i<t;++i){
        cout<<ans[i]<<'\n';
    }
}

