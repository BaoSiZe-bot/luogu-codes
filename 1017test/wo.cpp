#include <stdio.h>
using ll = long long;
const int N = 1e6 + 5, M = 998244353;
int p[N];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n + n; ++i)
        {
            scanf("%d", p + i);
            cnt += !p[i];
        }
    }
    return 0;
}
