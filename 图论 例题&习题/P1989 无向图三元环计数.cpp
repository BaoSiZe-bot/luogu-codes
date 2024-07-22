#include <cstdio>
int d[200005], ev[200005], ep[200005], u[200005], v[200005], ed[200005], cnt, res;
int at[200005];
inline void add(int u, int v)
{
    ev[++cnt] = v;
    ep[cnt] = ed[u];
    ed[u] = cnt;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u[i], &v[i]);
        d[u[i]]++;
        d[v[i]]++;
    }
    for (int i = 1; i <= m; ++i)
    {
        if (d[u[i]] < d[v[i]] || (d[u[i]] == d[v[i]] && u[i] < v[i]))
            add(u[i], v[i]);
        else
            add(v[i], u[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = ed[i]; j; j = ep[j])
            at[ev[j]] = i;
        for (int j = ed[i]; j; j = ep[j])
            for (int k = ed[ev[j]]; k; k = ep[k])
                if (at[ev[k]] == i)
                    ++res;
    }
    printf("%d", res);
    return 0;
}
