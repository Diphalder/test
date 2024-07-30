/*Solution
​ Reference Solution 1 Reference Solution 2

​ Consider two special cases first:

​ (1) If all edge weights are equal: For each edge, assume that the number
 of points connected to its two sides is x, y respectively, then the charm
  value of the edge is x∗y∗2
. You only need to build a tree, traverse it and count the number of nodes
 in the subtree with any node as the root, then you can calculate the charm
 value of all edges and get the answer. (If the size of the subtree with rt1
as the root is m, then the charm value of the edge connecting rt1 and its
 parent node is m∗(n−m))

​ (2) If all edge weights are unequal: Consider adding edges to the graph
from small to large weights, and use union-find to maintain connectivity.
 When adding the i-th edge, multiply the size of the union-find set of the
  two vertices before adding it (and then multiply by 2) to get the charm
  value of the edge. After adding all the edges, you get the answer.

​ In this question, there is no restriction on the weight of the edge, that
 is, there are both different and the same. Therefore, it is wrong to
  directly apply the method in (2) above. It can be imagined that the
   weight should be increased from small to large, but instead of
   adding only one edge at a time, all edges with equal weights
   should be added, and then the answers of these edges should be counted
    before the next round of adding edges.

​ Now the question is how to count the charm values ​​of these edges after
adding edges with equal weights at one time. In (2) above, the answers
of the edges are counted before adding the edges, but now it must be
after adding the edges. Consider whether it is possible to determine a
sequence of adding edges when the weights are equal, so that after adding
 these edges, the number of connection points of a certain endpoint of
 the edge will not change.

​ Build a tree with any point as the root, and add equal edges in order
from deep to shallow.  In this way, the number of nodes connected to the
deeper points connected by the edge (or the size of the union-find set,
 or the size of the current subtree) will not change. Record this value
 before adding the edge. After all edges with the same weight are added,
  you can use the previously temporarily recorded value and the total size
   of the union-find set where the edge is located to calculate the answer.
   (It feels a bit abstract, you can imagine it yourself qwq)*/

// by DTTTTTTT 2023.3.14
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1e5 + 5; // 当然不能只写1e5啦

int n, fa[N], Size[N], dep[N], tmp[N];

vector<int> to[N];

ll val[N];

struct edge
{
    int u, v, id, dep;
    ll w;
} e[N];

bool cmp(edge x, edge y)
{
    if (x.w == y.w)
        return x.dep > y.dep; // if w same than take deeper edge
    return x.w < y.w;         // take smaller weight
}

int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void join(int i, int u, int v)
{
    int fu = find(u);
    int fv = find(v);
    //cout<<"join "<<fv<<"<-"<<fu<<" ["<<v<<"," <<u<<"]"<<endl;
    
    tmp[i] = Size[fv];
    
    fa[fu] = fv;
    
    Size[fv] += Size[fu];
    
   // cout<<"tmp = "<< tmp[i]<<"  z="<<Size[fv]<<endl;
}

void dfs(int u, int fa, int depp)
{
    dep[u] = depp;
    for (int i = 0; i < to[u].size(); ++i)
    {
        int v = to[u][i];
        if (v == fa)
            continue;
        dfs(v, u, depp + 1);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].id = i;
        to[e[i].u].push_back(e[i].v);
        to[e[i].v].push_back(e[i].u);
    }

    for (int i = 1; i <= n; ++i)
        fa[i] = i, Size[i] = 1;

    dfs(1, 0, 0);

    for (int i = 1; i < n; ++i)
    {
        if (dep[e[i].u] > dep[e[i].v])
        {
            swap(e[i].u, e[i].v);
        } // e[i].v is the deeper point
        e[i].dep = dep[e[i].v];
    }

    sort(e + 1, e + n, cmp);

    int num = 0;
    for (int i = 1; i < n; ++i)
    {
        int u = e[i].u;
        int v = e[i].v;
        int w = e[i].w;
        join(i, u, v);
        num++;
        //cout<<"num="<<num<<endl<<endl;;
        if (i == n - 1 || w != e[i + 1].w)
        {
            for (int j =i-num+1; j <= i; ++j)
            {
                int fu=find(e[j].u);
                val[e[j].id] = 1ll * tmp[j] * (Size[fu] - tmp[j]) * 2;
                cout<<e[j].u<<"-"<<e[j].v<<" = "<<val[e[j].id]/2<<endl;
            }
            num = 0;
        }
    }

    num = 0;
    ll maxval = 0; // 写ll！！！
    for (int i = 1; i < n; ++i)
        if (maxval < val[i])
        {
            maxval = val[i];
            num = 1;
        }
        else if (maxval == val[i])
        {
            ++num;
        }

    cout << maxval << " " << num << endl;
    for (int i = 1; i < n; ++i)
        if (maxval == val[i])
            cout << i << " ";

    return 0;
}
