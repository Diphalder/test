#include "bits/stdc++.h"
 
using namespace std;
 
using ll = long long;
using ld = long double;
template<class T> 
using vec = vector<T>;
using vi = vec<int>;
using vl = vec<ll>;
using vd = vec<ld>;
using vvi = vec<vi>;
using vvl = vec<vl>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vpi = vec<pi>;
using vpl = vec<pl>;
template<class T> 
using mxpq = priority_queue<T>;
template<class T> 
using mnpq = priority_queue<T, vec<T>, greater<T>>;
#define pb push_back
#define eb emplace_back
#define acc accumulate
 
 
 
#define MULTI_TESTS
// #define FLOAT_PRECISION 13
 
 
 
void solve(int testIdx) {
    int n, m;
    cin >> n >> m;
 
    vi a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    
    vvi adj(n + 1), rev(n + 1);
    {
        vec<set<int>> tmp(n + 1);
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            if (u == v)
                continue;
            tmp[u].insert(v);
        }
        for (int i = 1; i <= n; ++i) {
            for (auto e : tmp[i])
                adj[i].pb(e), rev[e].pb(i);
        }
    }
 
    vec<bool> vis(n + 1, false);
    vi top;
    auto dfs = [&] (auto &f, int u) -> void {
        vis[u] = true;
        for (auto v : adj[u]) {
            if (!vis[v])
                f(f, v);
        }
        top.pb(u);
    };
    for (int i = 1; i <= n; ++i) {
        if (!vis[i])
            dfs(dfs, i);
    }
    reverse(begin(top), end(top));
 
    // for (auto e : top)
    //     cout << e << ' ';
    // cout << '\n';
 
    vi roots;
    vvi cmp(n + 1);
    vi cnt(n + 1, 0);
    vl sum(n + 1, 0);
    vi par(n + 1, -1);
 
    vis.assign(n + 1, false);
    auto dfs2 = [&] (auto &f, int u, int rt) -> pl {
        vis[u] = true;
        par[u] = rt;
        cmp[rt].pb(u);
        ll uc = 1, us = a[u];
        for (auto v : rev[u]) {
            if (!vis[v]) {
                auto [cc, cs] = f(f, v, rt);
                uc += cc;
                us += cs;
            }
        }
        return { uc, us };
    };
    for (auto u : top) {
        if (!vis[u]) {
            roots.pb(u);
            auto [uc, us] = dfs2(dfs2, u, u);
            cnt[u] = uc;
            sum[u] = us;
        }
    }
 
    vec<set<int>> nadj(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (auto v : adj[i]) {
            if (par[i] != par[v])
                nadj[par[i]].insert(par[v]);
        }
    }
 
    // for (auto e : roots)
    //     cout << e << ' ';
    // cout << "\n";
 
    ll lp = 0, ms = LLONG_MAX;
    vl dplp(n + 1, 0);
    vl dpms(n + 1, LLONG_MAX);
    for (int i = (int)roots.size() - 1; i >= 0; --i) {
        int u = roots[i];
        ll clp = cnt[u], cms = sum[u];
        for (auto v : nadj[u]) {
            if (dplp[v] + cnt[u] > clp or (dplp[v] + cnt[u] == clp and dpms[v] + sum[u] < cms)) {
                clp = dplp[v] + cnt[u];
                cms = dpms[v] + sum[u];
            }
        }
        dplp[u] = clp;
        dpms[u] = cms;
 
        if (dplp[u] > lp or (dplp[u] == lp and dpms[u] < ms)) {
            lp = dplp[u];
            ms = dpms[u];
        }
    }
 
    cout << lp << ' ' << ms << '\n';
 
 
}
 
void init() {
    
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);
    
    #ifdef FLOAT_PRECISION
        cout << fixed;
        cout.precision(FLOAT_PRECISION);
    #endif
    
    init();
    
    int numTests = 1;
    #ifdef MULTI_TESTS
        cin >> numTests;
    #endif
    for (int testIdx = 1; testIdx <= numTests; testIdx++) {
        solve(testIdx);
    }
    
    return 0;
}