#include <algorithm>
#include <iostream>
#include <string>

using ll = long long;
const int N = 1e6 + 5, P1 = 998244353, P2 = 1e9 + 7, B1 = 20111208, B2 = 20120602;

struct dat
{
    long long va, vd;
    bool operator==(const dat &lover) const
    {
        return va == lover.va && vd == lover.vd;
    }
} h[N], b[N] = {{1, 1}};
inline dat get(int l, int r, dat h[])
{
    return {((h[r].va - (h[l - 1].va * b[r - l + 1].va) % P1) + P1) % P1, ((h[r].vd - (h[l - 1].vd * b[r - l + 1].vd) % P2) + P2) % P2};
}

int n;
std::string a;
inline int lcp(int x, int y)
{
    if (x > y)
        x ^= y ^= x ^= y;

    int lt = 0, rt = n - y, res = 0;
    while (lt <= rt)
    {
        int mid = (lt + rt) >> 1;
        if (get(x, x + mid - 1, h) == get(y, y + mid - 1, h))
        {
            res = mid;
            lt = mid + 1;
        }
        else
            rt = mid - 1;
    }
    return res;
}

inline bool cmp(int x, int y)
{
    bool f = 0;
    
    if (x > y)
    {
        x ^= y ^= x ^= y;
        f = 1;
    }

    int len = lcp(x, y);
    if (len == n - y)
        return f;

    return f ^ (a[x + len] < a[y + len]);
}

int sa[N], ht[N];
int main()
{
    std::cin >> a;
    n = a.size();
    for (int i = 1; i <= n; ++i)
        b[i] = {b[i - 1].va * B1 % P1, b[i - 1].vd * B2 % P2};

    h[0] = {a[0] % P1, a[0] % P2};
    for (int i = 1; i < n; ++i)
        h[i] = {(h[i - 1].va * B1 + a[i]) % P1, (h[i - 1].vd * B2 + a[i]) % P2};

    for (int i = 0; i < n; ++i)
        sa[i] = i;

    std::stable_sort(sa, sa + n, cmp);

    for (int i = 0; i < n; ++i)
        printf("%d ", sa[i]);
    printf("\n0 ");
    for (int i = 1; i < n; ++i)
        printf("%d ", lcp(sa[i], sa[i - 1]));
    return !1314520;
}
// 3 * 28 = 84