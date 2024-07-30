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

class Trie
{

public:
    bool find;
    Trie *nxt[26];

    Trie()
    {

        find = 0;

        loopN(26)
        {
            nxt[i] = nullptr;
        }
    }

    void insert(string word)
    {

        lld x;
        Trie *cur = this;

        for (auto a : word)
        {
            x = a - 'a';
            if (cur->nxt[x] != nullptr)
            {
                cur = cur->nxt[x];
            }
            else
            {
                cur->nxt[x] = new Trie();
                cur = cur->nxt[x];
            }
        }
        cur->find = 1;
    }

    bool search(string word)
    {

        lld x;
        Trie *cur = this;

        for (auto a : word)
        {
            x = a - 'a';
            if (cur->nxt[x] != nullptr)
            {
                cur = cur->nxt[x];
            }
            else
            {
                return 0;
            }
        }
        return cur->find;
    }

    bool startsWith(string prefix)
    {

        lld x;
        Trie *cur = this;

        for (auto a : prefix)
        {
            x = a - 'a';
            if (cur->nxt[x] != nullptr)
            {
                cur = cur->nxt[x];
            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */