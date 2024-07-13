#include <bits/stdc++.h>
#define lld long long int
#define llf long double
#define pb push_back
#define pushf(v, a) v.insert(v.begin(), a)
#define popf(v) v.erase(v.begin())
#define popb pop_back
#define mp make_pair
#define in insert
#define minheap priority_queue<lld, vector<lld>, greater<lld>>
#define maxheap priority_queue<lld>
#define loopN(n) for (lld i = 0; i < n; i++)
#define loopN2(n) for (lld j = 0; j < n; j++)
#define loop(p, n) for (lld i = p; i <= n; i++)
#define rloop(p, n) for (lld i = n; i >= p; i--)
#define loop2(p, n) for (lld j = p; j <= n; j++)
#define looop(p, n, i) for (lld i = p; i <= n; i++)
#define rlooop(p, n, i) for (lld i = n; i >= p; i--)
#define iloop(it, m) for (it = m.begin(); it != m.end(); it++)
#define all(v) v.begin(), v.end()
#define ff first
#define ss second
#define INF 2e18
#define FILE                          \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout)
#define pi (2 * acos(0.0))
#define mod (1e9 + 7)
#define ISO                      \
    ios::sync_with_stdio(false); \
    cin.tie(0)
#define mem(a, b) memset(a, b, sizeof(a))
#define case(z) cout << "Case " << z << ": "
#define setprec(a) fixed << setprecision(a)
#define pii pair<lld, lld>
#define vii vector<lld>
#define retdp(a) \
    if (a != -1) \
    return a
#define yes cout << "YES"
#define no cout << "NO"
#define nl cout << endl
#define low(a, n, x) lower_bound(a, a + n, x) - a;
#define up(a, n, x) upper_bound(a, a + n, x) - a;
#define bug(a) std::cout << #a " -> " << (a) << "\t"

//_______________________________________________
#define on(m, p) (m | (1LL << p))
#define off(m, p) (~(~m | (1LL << p)))
#define ison(m, p) ((bool)(m & (1LL << p)))
#define flip(m, p) (m ^ (1LL << p))
#define nbitON(p) ((1LL << p) - 1)
//__________Fenwick Tree__________________________
#define rmvLastBit(n) n = n - (n & -n)
#define child_node(n) n = n - (n & -n)
#define par_node(n) n = n + (n & -n)
//_______________________________________________
using namespace std;

/*
fstream fin;
    fin.open ("mytext.txt");

map< , > :: iterator it


*/
lld fx[] = {1, 0, -1, 0, 1, 1, -1, -1};
lld fy[] = {0, 1, 0, -1, 1, -1, 1, -1};
//_______________________________________________

lld const sz = 2e5 + 10;
lld a[sz];
lld n;
vii ad[sz];

vii ad2[sz];

vii rad[sz];
vii topo;
bool vis[sz];

lld z[sz];

lld sum[sz];
lld cnt[sz];

lld mxpath;

void dfs(lld u)
{
    vis[u] = 0;
    for (lld v : ad[u])
    {
        if (vis[v])
        {
            dfs(v);
        }
    }
    topo.pb(u);
}

vector<vii> compo;
vii cur;

lld add;

void dfs2(lld u, lld clr)
{
    vis[u] = 0;
    cur.pb(u);
    z[u] = clr;
    add += a[u];

    for (lld v : rad[u])
    {
        if (vis[v])
        {
            dfs2(v, clr);
        }
    }
}

void dfs3(lld u)
{
    vis[u] = 0;
    for (lld v : ad2[u])
    {
        if (vis[v])
        {
            dfs3(v);
        }
    }
    topo.pb(u);
}


lld dp[sz];
lld fun(lld u)
{
    retdp(dp[u]);
    lld ans=cnt[u];
    for(lld v : ad2[u])
    {
        ans=max(ans,cnt[u]+fun(v));

    }
    return dp[u]=ans;

}

void print(vii p)
{
    for(lld u : p)
    {
        cout<<u<<",";
    }
    cout<<endl;
}

lld ans;


lld dp2[sz];

lld fun2(lld u, lld d)
{
    //bug(u);
   // bug(d)<<endl;
    retdp(dp2[u]);
    
    lld ans=INF;

    if(d==mxpath)
    {
        return sum[u];
    }


    for(lld v : ad2[u])
    {
        ans=min(ans,sum[u]+fun2(v,d+cnt[v]));
    }

    if(ans!=INF)
    {
        dp[u]=ans;
    }
    return ans;

}






void slv()
{
    lld m;
    cin >> n >> m;
    loopN(n) cin >> a[i];
    lld x, y;

    loopN(n) ad[i].clear();
    loopN(n) rad[i].clear();

    loopN(m)
    {
        cin >> x >> y;
        x--;
        y--;
        ad[x].pb(y);
        rad[y].pb(x);
    }
    topo.clear();

    loopN(n) vis[i] = 1;

    loopN(n)
    {
        if (vis[i])
        {
            dfs(i);
        }
    }
    reverse(all(topo));

    loopN(n) vis[i] = 1;

    lld clr = 0;
    compo.clear();

    //cout<<"____  compo ____\n";

    for (lld u : topo)
    {
        if (vis[u])
        {
            cur.clear();
            add = 0;

            dfs2(u, clr);
            compo.pb(cur);

            sum[clr] = add;

            cnt[clr] = cur.size();
            
            //print(cur);

            clr++;
        }
    }

    loopN(clr) ad2[i].clear();

    loopN(n)
    {
        for (lld j : ad[i])
        {
            if (z[i] != z[j])
            {
                ad2[z[i]].pb(z[j]);
                //bug(z[i]);
                //bug(z[j])<<endl;
            }
        }
    }


    topo.clear();

    loopN(clr) vis[i] = 1;

    loopN(clr)
    {
        if (vis[i])
        {
            dfs3(i);
        }
    }
    reverse(all(topo));

    mxpath=0;

    loopN(clr)dp[i]= -1;
    lld k;


    
    for (lld u : topo)
    {
        k=fun(u);
        mxpath=max(mxpath,k);
        //bug(u);
       // bug(k)<<endl;
        
    }
    //cout<<endl;
    lld ans=INF;

    loopN(clr)dp2[i]=-1;

    

    for (lld u : topo)
    {
        if(mxpath==fun(u))
        {
            k=fun2(u,cnt[u]);
            ans=min(ans,k);

            //cout<<"___end___\n";

        }

    }

    cout<<mxpath<<" "<<ans<<endl;




}

int main()
{
    ISO;
    lld idx = 1;
    lld t;
    cin >> t;
    while (t--)
    {
        // case(idx++);
        slv();
    }
    return 0;
}

/*




*/
