#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <bits/stl_pair.h>
#include <iostream>
#include <string>
struct Edge
{
    int v, p;
} e[505];
std::pair<int, int> pr[105];
int ed[505], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int ep[505], dfn[505], low[505], stk[505], pos[505], top, gtm, pts, tot;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline void tarjan(int x)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!dfn[to])
        {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        }
        else if (!pos[to])
            low[x] = min(low[x], dfn[to]);
    }
    if (dfn[x] == low[x])
    {
        ++pts;
        int t = 0;
        do
            pos[t = stk[top--]] = pts;
        while (t != x);
    }
}
__gnu_pbds::gp_hash_table<std::string, int> gp;
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        if (!gp[s1])
            gp[s1] = ++tot;
        if (!gp[s2])
            gp[s2] = ++tot;
        add(gp[s1], gp[s2]);
        pr[i] = {gp[s1], gp[s2]};
    }
    std::cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        if (!gp[s1])
            gp[s1] = ++tot;
        if (!gp[s2])
            gp[s2] = ++tot;
        add(gp[s2], gp[s1]);
    }
    for (int i = 1; i <= tot; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        std::cout << (pos[pr[i].first] ^ pos[pr[i].second] ? "Safe\n" : "Unsafe\n");
    return 0;
}
