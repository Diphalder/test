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
lld n, m, k;

vii ad[sz];
vii adr[sz];
lld a[sz];

vii ad2[sz];

vii topo;

bool vis[sz];

vector<vii> compo;
vii tmp;

lld color[sz];

void dfstopo(lld u)
{
    vis[u] = 0;

    for (auto v : ad[u])
    {
        if (vis[v])
        {
            dfstopo(v);
        }
    }

    topo.pb(u);
}

void dfscompo(lld u, lld idx)
{
    vis[u] = 0;
    color[u] = idx;
    tmp.pb(u);
    for (auto v : adr[u])
    {
        if (vis[v])
        {
            dfscompo(v, idx);
        }
    }
}

void slv()
{
    cin >> n >> m >> k;
    loopN(n) cin >> a[i];
    lld x, y;
    loopN(m)
    {
        cin >> x >> y;
        x--;
        y--;
        ad[x].pb(y);
        adr[y].pb(x);
    }
    mem(vis, 1);
    loopN(n)
    {
        if (vis[i])
        {
            dfstopo(i);
        }
    }
    reverse(all(topo));

    mem(vis, 1);
    lld idx = 0;
    for (auto u : topo)
    {
        if (vis[u])
        {
            tmp.clear();
            dfscompo(u, idx++);
            compo.pb(tmp);
        }
    }

    loopN(n)
    {
        x = i;

        loopN2(ad[i].size())
        {
            y = ad[i][j];
            if (color[x] != color[y])
            {
                ad2[color[x]].pb(color[y]);
            }
        }
    }

    

   




}
/*
 for (auto c : compo)
    {
        cout << "comp =";
        for (auto u : c)
        {
            cout << u + 1 << " ";
        }
        cout << endl;
    }
    loopN(n)
    {
        cout << i + 1 << " color=" << color[i] << endl;
    }

    loopN(compo.size())
    {
        cout << i << " -> ";
        loopN2(ad2[i].size())
        {
            cout << ad2[i][j] << ",";
        }
        cout << endl;
    }


    */
int main()
{
    ISO;
    lld idx = 1;
    // lld t;cin>>t;while(t--)
    {
        // case(idx++);
        slv();
    }
    return 0;
}

/*




*/
