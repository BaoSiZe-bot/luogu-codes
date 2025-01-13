#include <stdio.h>
using ll = long long;
ll l[55], p[55];
ll solve(int n, ll x)
{
    if (n == 0 && x == 1)
        return 1;
    if (x < 2)
        return 0;
    if (x == l[n])
        return p[n];
    if (x > l[n - 1] + 1)
        return p[n - 1] + 1 + solve(n - 1, x - l[n - 1] - 2);
    else
        return solve(n - 1, x - 1);
}
int main()
{
    int n;
    ll x;
    scanf("%d%lld", &n, &x);
    l[0] = p[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        l[i] = 2 * l[i - 1] + 3;
        p[i] = 2 * p[i - 1] + 1;
    }
    printf("%lld", solve(n, x));
    return 0;
}

//P
//B(P)P(P)B
//B(B(P)P(P)B)P  (B(P)P(P)B)B
