#include <algorithm>
#include <iostream>
#include <string>

using ull = unsigned long long;
const int N = 1e6 + 5, B1 = 111208, B2 = 120602;

struct dat
{
    ull va, vd;
    bool operator==(const dat &lover) const
    {
        return va == lover.va && vd == lover.vd;
    }
} h[N], b[N];
inline dat get(int l, int r, dat h[])
{
    return {h[r].va - (h[l - 1].va * b[r - l + 1].va), h[r].vd - (h[l - 1].vd * b[r - l + 1].vd)};
}

int n;
std::string a;
inline bool check(int x, int y, int mid)
{
    return get(x, x + mid - 1, h) == get(y, y + mid - 1, h);
}
inline int lcp(int x, int y)
{
    if (x > y)
        x ^= y ^= x ^= y;

    int lt = 0, rt = n - y, res = 0;
    while (lt <= rt)
    {
        int mid = (lt + rt) >> 1;
        if (check(x, y, mid))
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

int sa[N];
int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::getline(std::cin, a, '\n');
    n = a.size();
    b[0] = {1, 1};
    for (int i = 1; i <= n; ++i)
        b[i] = {b[i - 1].va * B1, b[i - 1].vd * B2};
    h[0] = {(ull)a[0], (ull)a[0]};
    for (int i = 1; i < n; ++i)
        h[i] = {h[i - 1].va * B1 + a[i], h[i - 1].vd * B2 + a[i]};
    for (int i = 0; i < n; ++i)
        sa[i] = i;

    std::stable_sort(sa, sa + n, cmp);
    for (int i = 0; i < n; ++i)
        std::cout << sa[i] + 1 << " ";
    return !1314520;
}
// 3 * 28 = 84