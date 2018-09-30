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

map<pll,ll> mp;

int main()
{
    IOS
    srand(time(NULL));

    ll n,m,k;
    n = 300 + rand() % 500;
    ll bound = n-1;
    ll bound1 = n*(n-1)/2;
    if(bound1-bound <= 0){
    	cout<<"-1\n";
    	return 0;
    }

    m = bound + rand() % (bound1 - bound);

    int cnt = 0;
    while(1){
    	k = n / ( 5 + rand()%5);
    	if(cnt == 1000){
    		k = n; break;
    	}
		if(k > n){
			cnt++;
			continue;
		}
		else{
			cnt = 0; break;
		}
    }

    cout << n << ' ' << m << ' ' << k << endl;
    for(ll i=0;i<m;i++){
    	ll u,v;
    	while(1){
	    	u = rand() % n; u++;
	    	v = rand() % n; v++;
	    	if(mp[{u,v}]) continue;
	    	mp[{u,v}] = 1;
	    	mp[{v,u}] = 1;
	    	break;
    	}
    	cout << u << ' ' << v << endl;
    }
}