
#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int v, p;
}e[100005];int ed[100005], mx[100005], cnt, id;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline void dfs(int x)
{
    mx[x] = id;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if(!mx[to])
            dfs(to);
    }
}
int main()
{
    int n, m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(v, u);
    }
    for (int i = n; i; --i)
        if (!mx[i])
        {
            id = i;
            dfs(i);
        }
    for (int i = 1; i <= n; ++i)
        printf("%d ", mx[i]);
    return 0;
}


//3 -> 4 -> 2 -> 1
