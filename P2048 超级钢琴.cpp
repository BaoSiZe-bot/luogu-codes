#include <cstdio>
#include <queue>
#define smex(x, y) s[x] < s[y] ? y : x
const int N = 5e5 + 5;
int sp[20][N], lg[N];
long long s[N], res;
inline void init(int n)
{
    for (int i = 1; i <= n; ++i)
        sp[0][i] = i;
    for (int i = 1; (1 << i) <= n; ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            sp[i][j] = smex(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
}
inline int qry(int l, int r)
{
    int j = lg[r - l + 1];
    return smex(sp[j][l], sp[j][r - (1 << j) + 1]);
}
struct st
{
    int mn, ml, mr, mx;
    bool operator<(const st &others) const
    {
        return s[mx] - s[mn - 1] < s[others.mx] - s[others.mn - 1];
    }
};
std::priority_queue<st> pq;
int main()
{
    for (int i = 2; i <= 5e5; ++i)
        lg[i] = lg[i >> 1] + 1;
    int n, k, L, R;
    scanf("%d%d%d%d", &n, &k, &L, &R);
    for (int i = 1, x; i <= n; ++i)
    {
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
    }
    init(n);
    for (int i = 1; i <= n; ++i)
        if (i <= n - L + 1)
        {
            int l = i + L - 1, r = std::min(i + R - 1, n);
            pq.push({i, l, r, qry(l, r)});
        }
    while (k--)
    {
        auto t = pq.top();
        pq.pop();
        res += s[t.mx] - s[t.mn - 1];
        if (t.mx ^ t.ml)
            pq.push({t.mn, t.ml, t.mx - 1, qry(t.ml, t.mx - 1)});
        if (t.mx ^ t.mr)
            pq.push({t.mn, t.mx + 1, t.mr, qry(t.mx + 1, t.mr)});
    }
    printf("%d\n", res);
    return 0;
}
// Abalone!
