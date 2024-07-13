#include <cstdio>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <stdint.h>
#define lld long long int



std::map<lld, lld> par;
std::vector<lld> box[16];
long long box_sum[16];

std::map<lld, std::vector<lld>> neededby;
std::map<lld, lld> needs;

std::map<lld, lld> vis;
std::vector<lld> cycle;


bool dfs(lld x)
{
    if (vis[x] == 2)
        return false;
    
    if (vis[x] == 1)
    {
        cycle.erase(cycle.begin(), std::find(cycle.begin(), cycle.end(), x));
        return true;
    }
    vis[x] = 1;
    cycle.push_back(x);
    for (lld y : neededby[x])
    {
        if (dfs(y))
        {
            vis[x] = 2;
            return true;
        }
    }
    cycle.pop_back();
    vis[x] = 2;
    return false;
}


std::map<lld, std::vector<lld>> single;

bool dp[1 << 15];

lld cs[16];
lld ps[16];

void recover(lld mask)
{
    if (single.count(mask))
    {
        std::vector<lld> cycle = single[mask];
        for (lld y : cycle)
        {
            lld x = needs[y];
            lld i = par[x];
            cs[i] = x;
            ps[i] = par[y];
        }
        return;
    }
    for (lld sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask)
    {
        lld rest = mask & ~sub;
        if (dp[sub] && dp[rest])
        {
            recover(sub);
            recover(rest);
            return;
        }
    }
    assert(0);
}

int main()
{
    lld K;
    scanf("%lld", &K);
    long long total_sum = 0;

    for (lld i = 0; i < K; i++)
    {
        lld N;
        scanf("%lld", &N);
        for (lld j = 0; j < N; j++)
        {
            lld A;
            scanf("%lld", &A);
            box[i].push_back(A);
            
            box_sum[i] += A;
            
            total_sum += A;
            
            par[A] = i;
        }
    }


    long long target = total_sum / K;

    for (auto it : par)
    {
        lld i = it.second;
        lld x = it.first;
        lld y = x + target - box_sum[i];
        
        if (par.count(y))
        {
            needs[x] = y;
            neededby[y].push_back(x);
        }
    }
    
    for (lld i = 0; i < K; i++)
    {
        for (lld x : box[i])
        {
            if (dfs(x))
            {
                lld mask = 0;
                bool bad = false;
                for (lld v : cycle)
                {
                    if (mask & (1 << par[v]))
                    {
                        bad = true;
                        break;
                    }
                    mask |= (1 << par[v]);
                }
                if (!bad)
                {
                    single[mask] = cycle;
                }
                cycle.clear();
            }
        }
    }
    
    
    for (lld mask = 0; mask < (1 << K); mask++)
    {
        if (single.count(mask))
        {
            dp[mask] = true;
            continue;
        }
        for (lld sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask)
        {
            lld rest = mask & ~sub;
            dp[mask] |= dp[sub] & dp[rest];
        }
    }


    if (!dp[(1 << K) - 1])
    {
        printf("No\n");
        return 0;
    }
    recover((1 << K) - 1);
    printf("Yes\n");
    for (lld i = 0; i < K; i++)
    {
        printf("%lld %lld\n", cs[i], ps[i] + 1);
    }
}
