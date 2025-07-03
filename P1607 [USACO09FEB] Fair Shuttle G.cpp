#include <algorithm>
#include <climits>
#include <stdio.h>
const int N = 2e5 + 5;
struct Abacow
{
    int s, e, m;
    bool operator<(const Abacow &others) const
    {
        return e ^ others.e ? e < others.e : s < others.s;
    }
} a[N];
int t[N], res;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    int k, n, c;
    scanf("%d%d%d", &k, &n, &c);
    for (int i = 1; i <= k; ++i)
        scanf("%d%d%d", &a[i].s, &a[i].e, &a[i].m);
    std::sort(a + 1, a + k + 1);
    for (int i = 1; i <= k; ++i)
    {
        int mn = INT_MAX;
        if (t[a[i].s] < c)
        {
            for (int j = a[i].s; j < a[i].e; ++j)
                if (!(mn = min(mn, c - t[j])))
                    break;
            if (mn)
            {
                int tmp = min(mn, a[i].m);
                for (int j = a[i].s; j < a[i].e; ++j)
                    t[j] += tmp;
                res += tmp;
            }
        }
    }
    printf("%d", res);
    return 0;
}
