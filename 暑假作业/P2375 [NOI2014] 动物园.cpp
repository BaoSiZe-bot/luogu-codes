#include <string.h>
#include <stdio.h>
#define int long long
int nx[1000005], nu[1000005];
char s[1000005];
signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%s", s + 1);
        int n = strlen(s + 1), p = 0, m = 1;
        memset(nu, 0, sizeof(int) * (n + 5));
        memset(nx, 0, sizeof(int) * (n + 5));
        nu[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            while (p && s[i] ^ s[p + 1])
                p = nx[p];
            p += !(s[i] ^ s[p + 1]);
            nx[i] = p;
            nu[i] = nu[p] + 1;
        }
        p = 0;
        for (int i = 2; i <= n; ++i)
        {
            while (p && s[i] ^ s[p + 1])
                p = nx[p];
            p += !(s[i] ^ s[p + 1]);
            while (p + p > i)
                p = nx[p];
            m = (m * (nu[p] + 1)) % 1000000007;
        }
        printf("%lld\n", m);
    }
    return 0;
}
