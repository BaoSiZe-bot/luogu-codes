#include <bits/stl_algo.h>
#include <stdio.h>
#include <queue>
struct Node
{
    int l, r;  // NOLINT
    bool operator<(const Node &other) const
    {
        return l < other.l;
    }
} a[100005];
int w[100005];
inline int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> q;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &a[i].l, &a[i].r);
        for (int i = 1; i <= m; ++i)
            scanf("%d", w + i);
        std::sort(a + 1, a + n + 1);
        std::sort(w + 1, w + m + 1);
        int res = -1, r = 1;
        for (int l = 1; l <= m; l++)
        {
            while (r <= n && a[r].l <= w[l])
                q.push(a[r++].r);
            while (!q.empty() && q.top() < w[l])
                q.pop();
            if (q.empty())
            {
                res = -1;
                break;
            }
            res = max(res, n - static_cast<int>(q.size()) + 1);
            q.pop();
        }
        if (res == -1)
            puts("IMPOSSIBLE!");
        else
            printf("%d\n", res);
    }
    return 0;
}
