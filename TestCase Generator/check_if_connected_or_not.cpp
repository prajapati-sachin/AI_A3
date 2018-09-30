#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);}
#else
#define trace(...)
#endif
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout<<setprecision(25);
#define endl '\n'
#define F first
#define S second
#define I insert
#define pb push_back
#define ll long long
#define ld long double
#define pll pair<ll,ll>
#define vll vector<ll>
#define vpll vector<pll>
#define sz(x) (ll)(x).size()
#define all(x) (x).begin(), (x).end()

ll power(ll a,ll b,ll mod){ll c=1;while(b>0){if(b%2)c*=a,c%=mod;b/=2;a*=a;a%=mod;}return c;}

const ll N = 1e5+5;
const ll M = 320;
ll Mod = 998244353; //1e9+7;
vll adj[1005];
ll vis[1005];

void dfs(ll f){
    vis[f] = 1;
    for(auto z : adj[f]){
        if(!vis[z]) dfs(z);
    }
}

map<pll,ll> mp;

int main()
{
    IOS
    ll n,m,k;
    cin>>n>>m>>k;
    for(ll i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        if(u == v || mp[{u,v}]){
            cout<<"Wrong testcase\n";
            return 0;
        }
        adj[u].pb(v); mp[{u,v}] = 1;
        adj[v].pb(u); mp[{v,u}] = 1;
    }

    ll here = 0;
    for(ll i=1;i<=n;i++){
        if(!vis[i]) here++, dfs(i);
    }
    if(here > 1){
        cout<<"Wrong testcase\n";
    }
    else{
        cout<<"right\n";
    }
}