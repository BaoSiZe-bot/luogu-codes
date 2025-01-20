#include <queue>
#include <stdio.h>
const int N = 2e5 + 5;
int a[N], res = 0;
inline int min(int x, int y)
{
    return x < y ? x : y;
}
inline int max(int x, int y)
{
    return x < y ? y : x;
}
std::priority_queue<int> q1;
std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
int main()
{
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    int mn = a[p], len = q - p + 1;
    for (int i = p; i <= n; ++i)
    {
        mn = min(mn, a[i]);
        q1.push(a[i]);
        if (len < q1.size())
            q1.pop();
        res = max(res, q1.top() - mn);
    }
    int mx = a[q];
    for (int i = q; i; --i)
    {
        mx = max(mx, a[i]);
        q2.push(a[i]);
        if (len < q2.size())
            q2.pop();
        res = max(res, mx - q2.top());
    }
    printf("%d", res);
    return 0;
}
