
#include<bits/stdc++.h>
#define lld             long long int
#define llf             long double
#define pb              push_back
#define pushf(v,a)      v.insert(v.begin(), a)
#define popf(v)         v.erase(v.begin())
#define popb            pop_back
#define mp              make_pair
#define in              insert
#define minheap         priority_queue<lld, vector<lld>, greater<lld>>
#define maxheap         priority_queue<lld>
#define loopN(n)        for(lld i=0;i<n;i++)
#define loopN2(n)       for(lld j=0;j<n;j++)
#define loop(p,n)       for(lld i=p;i<=n;i++)
#define rloop(p,n)      for(lld i=n;i>=p;i--)
#define loop2(p,n)      for(lld j=p;j<=n;j++)
#define looop(p,n,i)    for(lld i=p;i<=n;i++)
#define rlooop(p,n,i)   for(lld i=n;i>=p;i--)
#define iloop(it,m)     for(it=m.begin();it!=m.end();it++)
#define all(v)          v.begin(),v.end()
#define ff              first
#define ss              second
#define INF             2e18
#define FILE            freopen("input.txt","r",stdin);freopen("output.txt","w",stdout)
#define pi              (2*acos(0.0))
#define mod             (1e9+7)
#define ISO             ios::sync_with_stdio(false);cin.tie(0)
#define mem(a,b)        memset(a,b,sizeof(a))
#define case(z)         cout<<"Case "<<z<<": "
#define setprec(a)      fixed<< setprecision(a)
#define pii             pair<lld,lld>
#define retdp(a)        if(a!=-1)return a
#define yes             cout<<"YES"
#define no              cout<<"NO"
#define nl              cout<<endl
#define low(a,n,x)      lower_bound(a,a+n,x)-a;
#define up(a,n,x)       upper_bound(a,a+n,x)-a;
#define bug(a)          std::cout << #a " -> " << (a) << "\t"

//_______________________________________________
#define on(m,p)         (m|(1LL<<p))
#define off(m,p)        (~(~m|(1LL<<p)))
#define ison(m,p)       ((bool)(m&(1LL<<p)))
#define flip(m,p)       (m^(1LL<<p))
#define nbitON(p)       ((1LL<<p)-1)
//__________Fenwick Tree__________________________
#define rmvLastBit(n)   n=n-(n&-n)
#define child_node(n)   n=n-(n&-n)
#define par_node(n)     n=n+(n&-n)
//_______________________________________________
using namespace std;

/*
fstream fin;
    fin.open ("mytext.txt");

map< , > :: iterator it


*/
lld fx[]= {1,0,-1, 0,1, 1,-1,-1};
lld fy[]= {0,1,0,-1,1,-1,1,-1};
//_______________________________________________

lld const sz=2e5+50;


vector< lld >ad[sz];

stack<lld>stk;

bool onstack[sz];


lld n;

vector<lld>circle;

map<pair <lld, lld >, lld > wt;



bool circlefound=0;

bool oncircle[sz];

void dfs(lld u, lld last)
{
    if(circlefound)
    {
        return ;
    }

    if(onstack[u])
    {
        while(!stk.empty())
        {
            lld cur=stk.top();

            oncircle[cur]=1;
            circle.pb(cur);

            if(cur==u)
            {
                break;
            }
            stk.pop();
        }
        circlefound=1;
        return;
    }
    stk.push(u);
    onstack[u]=1;

    loopN(ad[u].size())
    {
        lld v=ad[u][i];
        if(v!=last)
        {
            dfs(v,u);
        }
    }
    stk.pop();
    onstack[u]=0;

}



lld dpth[sz]; // max depth of subtree


lld mx;
lld ep;

map< pii, lld >intersting;


void dfs2(lld u, lld last, lld len)
{
    if(len>mx)
    {
        mx=len;
        ep=u;
    }
    loopN(ad[u].size())
    {
        lld v=ad[u][i];
        if(v!=last && !oncircle[v])
        {
            dfs2(v,u,len+wt[mp(u,v)]);
        }
    }

}


void dfs3(lld u, lld last, lld len)
{

    if(len>mx)
    {
        mx=len;
        ep=u;
    }
    loopN(ad[u].size())
    {
        lld v=ad[u][i];

        if(v!=last && intersting[mp(u,v)]!=1)
        {
            dfs3(v,u,len+wt[mp(u,v)]);
        }
    }

}



lld LC[sz],L[sz],RC[sz],R[sz];





void slv()
{
    cin>>n;
    // Clear all previous data
    for(lld i=0; i<n; i++)
    {
        ad[i].clear();
    }
    circle.clear();
    while(!stk.empty()) stk.pop();
    wt.clear();
    intersting.clear();

    loopN(n)
    {
        lld x,y,w;
        cin>>x>>y>>w;
        x--;
        y--;

        ad[x].pb(y);
        ad[y].pb(x);

        wt[mp(x,y)]=w;
        wt[mp(y,x)]=w;
    }

    mem(onstack,0);
    mem(oncircle,0);

    dfs(0,-1);

    mem(dpth,0);
    lld k=circle.size();

    loopN(k)
    {
        lld u=circle[i];
        mx=0;
        ep=u;
        dfs2(u,-1,0);
        dpth[u]=mx;

    }



    circle.pb(circle[0]);

    L[0]=dpth[circle[0]];
    LC[0]=dpth[circle[0]];
    lld len=0;
    lld far=-INF;
    lld u,v;

    loop(1,k-1)
    {
        v=circle[i-1];
        u=circle[i];
        len+=wt[mp(u,v)];
        far=max(far,dpth[v])+wt[mp(u,v)];
        LC[i]=max(LC[i-1],len + dpth[u]);
        L[i]=max(L[i-1], far + dpth[u]);

    }



    R[k]=-INF;
    RC[k]=-INF;
    len=0;
    far=-INF;

    u,v;

    rloop(1,k-1)
    {
        v=circle[i+1];
        u=circle[i];
        len+=wt[mp(u,v)];
        far=max(far, dpth[v])+wt[mp(u,v)];
        RC[i]=max(RC[i+1],len + dpth[u]);
        R[i]=max(R[i+1], far + dpth[u]);

    }


    lld ans =INF;
    lld id=-1;
    lld kk;

    loopN(k)
    {
        kk= max(LC[i] + RC[i + 1], max(L[i], R[i + 1])) ;

        if(kk<ans)
        {
            id=i;
            ans=kk;
        }

    }

    u=circle[id];
    v=circle[id+1];


    intersting[mp(u,v)]=1;
    intersting[mp(v,u)]=1;



    mx=0;
    dfs3(0,-1,0);


    mx=0;
    dfs3(ep,-1,0);

    cout<<max(ans,mx)<<endl;
}






int main()
{
    ISO;
    lld idx=1;
    //lld t;cin>>t;while(t--)
    {
        //case(idx++);
        slv();
    }
    return 0;
}

/*


5
2 3 7
3 1 9
4 1 8
3 5 4
4 5 5




11
2 3 7
3 1 9
4 1 8
3 5 4
4 5 5
3 6 8
6 7 10
6 8 10
4 9 5
8 10 4
2 11 20




*/
