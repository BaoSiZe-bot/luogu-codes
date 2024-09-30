#include <cstdio>
#include <cstring>
int mp[205][205], md[205], vs[205], n;  //adjacency matrix and the matched array, visited array, node count of the graph
//Hungarian Algorithm
inline bool Hungarian(int x)
{
    for (int i = 1; i <= n; ++i)
        if (mp[x][i] && !vs[i])
        {
            vs[i] = 1;
            if (!md[i] || Hungarian(md[i]))
            {
                md[i] = x;
                return 1;
            }
        }
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                scanf("%d", &mp[i][j]);
            md[i] = 0;
        }
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            memset(vs, 0, sizeof vs);
            cnt += Hungarian(i);
        }
        puts(cnt ^ n ? "No" : "Yes");
    }
    return 0;
}
