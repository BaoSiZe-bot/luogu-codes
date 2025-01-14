#include <cstdio>
const int N = 1000005;
using ll = long long;
char s[N];
int nx[N];
int main()
{
    int n;
    scanf("%d%s", &n, s + 1);
    int p = 0;
    ll res = 0;
    for (int i = 2; i <= n; ++i)
    {
        while (p && s[i] ^ s[p + 1])
            p = nx[p];
        if (s[i] == s[p + 1])
            ++p;
        nx[i] = p;
    }
    p = 2;
    for (int i = 2; i <= n; ++i)
    {
        while (nx[p])
            p = nx[p];
        if (nx[i])
            nx[i] = p;
        res += i - p;
        p = i;
    }
    printf("%lld", res);
    return 0;
}
