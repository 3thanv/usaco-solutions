#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll mod=1e9+7;
vector<vector<int>>s;
ll bex(ll a,ll b) {
    ll res = 1;
    while (b>0) {
        if(b&1){res=(res*a)%mod;}
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
int main() {
    int n,q,c;cin>>n>>q>>c;
    s.push_back({-1,0});
    for(int i=0;i<q;++i){
        int a,h;cin>>a>>h;s.push_back({a,h});
    }
    q++;
    sort(s.begin(),s.end());
    for(int i=0;i<s.size();++i){
        if(i>0&&s[i][1]==s[i-1][1]){
            s.erase(s.begin()+i);i--;q--;
        }
    }
    vector<vector<ll>>dp(q,vector<ll>(c+1));
    vector<vector<ll>>pref(q,vector<ll>(c+1));
    vector<vector<ll>>pref2(q,vector<ll>(c+1));
    vector<vector<ll>>pref3(q,vector<ll>(c+1));
    vector<vector<ll>>pref4(q,vector<ll>(c+1));
    for(int i=1;i<q;++i){
        for(int j=1;j<=c;++j){
            pref[i][j]+=pref[i][j-1]+(bex(j,s[i][1]-s[i-1][1]-1)-(bex(j-1,s[i][0]-s[i-1][1])*bex(j,s[i][1]-s[i][0]-1))%mod+mod)%mod;
            pref[i][j]%=mod;
        }
    }
    dp[0][1]=1;
    for(int j=1;j<=c;++j){
        pref2[0][j]=(bex(j,s[1][1]-s[0][1]-1)*dp[0][j])%mod;pref2[0][j]+=pref2[0][j-1];pref2[0][j]%=mod;
        pref3[0][j]=dp[0][j]+pref3[0][j-1];
        pref4[0][j]=dp[0][j]*pref[1][j]+pref4[0][j-1];pref4[0][j]%=mod;
    }
    for(int i=1;i<q;++i){
        for(int j=1;j<=c;++j){
            dp[i][j]+=pref2[i-1][j-1];dp[i][j]%=mod;
            if(j-2>=1){
                dp[i][j]+=(pref3[i-1][j-2]*pref[i][j-1])%mod;
                dp[i][j]-=pref4[i-1][j-2];dp[i][j]+=mod;dp[i][j]%=mod;
            }
        }
        if(i<q-1){
            for(int j=1;j<=c;++j){
                pref2[i][j]=(bex(j,s[i+1][1]-s[i][1]-1)*dp[i][j])%mod;pref2[i][j]+=pref2[i][j-1];pref2[i][j]%=mod;
                pref3[i][j]=dp[i][j]+pref3[i][j-1];pref3[i][j]%=mod;
                pref4[i][j]=dp[i][j]*pref[i+1][j]+pref4[i][j-1];pref4[i][j]%=mod;
            }
        }
    }
    ll res=0;
    for(int i=1;i<=c;++i){
        res+=(dp[q-1][i]*bex(c,n-s[q-1][1]))%mod;res%=mod;
    }
    cout<<res;
}
