#include <stdio.h>
#include <string.h>
using ll = long long;
using bl = bool;
int c[2000005], pr[2000005];
char s[2000005];
inline ll min(ll a, ll b)
{
    return a < b ? a : b;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%2000000s", s + 1);
        int n = static_cast<int>(strlen(s + 1)), l = 0, t = -1;
        ll cnt = 0, res = 0x3f3f3f3f3f3f3f3fll;
        memset(pr, 0, sizeof(int) * (n * 2 + 5));
        for (int i = 1; i <= n; ++i)
            s[i + n] = s[i];
        for (int i = 1; i <= n * 2; i++)
            c[i] = c[i - 1] + bl(s[i] ^ 'B');
        for (int i = n * 2; i; i--)
            if (s[i] ^ 'R')
            {
                pr[i] = l;
                l = i;
            }
        for (int i = l; l && i <= n && c[i] <= c[n] - c[i - 1]; i = pr[i])
        {
            t = i;
            cnt += c[i];
        }
        if (!~t || !l)
        {
            printf("0\n");
            continue;
        }
        for (int i = pr[t]; i <= n; i = pr[i])
            cnt += c[n] - c[i - 1];
        for (int i = 2; i <= n; i++)
        {
            res = min(res, cnt);
            cnt += bl(s[i + n - 1] == 'R') * ll(i + n - 1 - t - c[i + n - 1] + c[t]) + bl(s[i - 1] == 'R') * ll(i - t - 1 - c[i - 1] + c[t]);
            while (pr[t] && c[pr[t]] - c[i - 1] <= c[i + n - 1] - c[pr[t]])
                cnt += c[t = pr[t]] * 2 - c[i - 1] - c[i + n - 1];
        }
        printf("%lld\n", min(res, cnt));
    }
    return 0;
}
