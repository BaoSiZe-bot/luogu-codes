#include <bits/extc++.h>

#define int __int128
#pragma clang diagnostic ignored "-Wregister"
#pragma clang diagnostic ignored "-Wshift-op-parentheses"

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

const int M = 1e19;

vector<int> g[100005];
pair<int, int> res[100005], t[100005];

inline int rd()
{
    long long x;
    scanf("%lld", &x);
    return x;
}
inline void pt(int x)
{
    unsigned long long u = x / M, v = x % M;
    if(u)
        printf("%llu", u);
    printf("%llu", v);
}

inline void yf(pair<int, int> &a)
{
    int g = __gcd(a.first, a.second);
    a.first /= g;
    a.second /= g;
}
inline pair<int, int> add(pair<int, int> a, pair<int, int> b)
{
    if(!a.first)
        return b;
    pair<int, int> tmp = make_pair(a.first * b.second + b.first * a.second, a.second * b.second);
    yf(tmp);
    return tmp;
}

inline void dfs(int rt)
{
    if (g[rt].empty())
        res[rt] = add(res[rt], t[rt]);
    pair<int, int> s = {t[rt].first, t[rt].second * g[rt].size()};
    yf(s);
    for (int i : g[rt])
    {
        t[i] = add(t[i], s);
        dfs(i);
    }
    t[rt] = {0, 1};
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n = rd(), m = rd();
    for (int i = 1; i <= n; ++i)
    {
        int d = rd();
        while(d--)
            g[i].emplace_back(rd());
    }
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
            t[j] = {0, 1};
        t[i] = {1, 1};
        dfs(i);
    }
    for (int i = 1; i <= n; ++i)
    {
        if(g[i].size())
            continue;
        pt(res[i].first);
        putchar(' ');
        pt(res[i].second);
        putchar('\n');
    }
    return 0;
}
