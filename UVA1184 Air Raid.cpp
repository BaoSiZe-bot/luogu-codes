#include <cstring>
#include <stdio.h>
#include <vector>
int md[1005], vs[1005], n;
std::vector<int> g[1005];
inline bool Hungarian(int x)
{
    for (int i : g[x])
        if (!vs[i])
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
        memset(md, 0, sizeof md);
        for (int i = 1; i <= n; ++i)
            g[i].clear();
    }
    return 0;
}
