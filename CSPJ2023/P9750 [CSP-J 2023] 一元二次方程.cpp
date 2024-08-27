#include <stdio.h>
#include <math.h>
#define int long long
int gcd(int a, int b)
{
    while (b)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
signed main()
{
    int t, m;
    scanf("%lld%lld", &t, &m);
    while (t--)
    {
        int a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        int dlt = b * b - 4 * a * c;  //x1 = (-b + sqrt(dlt)) / 2a, x2 = (-b - sqrt(dlt)) / 2a
        if (dlt < 0)
        {
            printf("NO\n");
            continue;
        }
        int tmp = (int)sqrt(dlt);
        if (tmp * tmp == dlt)  // 开得尽
        {
            int u = -b + (a > 0 ? 1 : -1) * tmp, v = a * 2;
            int gc = abs(gcd(u, v));
            u /= gc;
            v /= gc;
            if (v < 0)
            {
                u *= -1;
                v *= -1;
            }
            if (v ^ 1)
                printf("%lld/%lld", u, v);
            else
                printf("%lld", u);
            printf("\n");
        }
        else
        {
            int u = -b, v = 2 * a, t = 1, s = dlt, tt = v;
            for (int i = 2; i * i <= s; ++i)
                if (dlt % i == 0)
                {
                    int j = s / i;
                    int cnt = 0;
                    while (dlt % i == 0)
                    {
                        ++cnt;
                        dlt /= i;
                    }
                    if (cnt & 1)
                        t *= i;
                }
            if (dlt != 1)
                t *= dlt;
            s = sqrt(s / t);  //NOLINT
            // printf("t=%lld,s=%lld\n", t, s);
            int gg = gcd(s, tt);
            s /= gg;
            tt /= gg;
            if (u)
            {
                int gc = abs(gcd(u, v));
                u /= gc;
                v /= gc;
                if (v < 0)
                {
                    u *= -1;
                    v *= -1;
                }
                if (v ^ 1)
                    printf("%lld/%lld+", u, v);
                else
                    printf("%lld+", u);
            }
            s = abs(s);
            tt = abs(tt);
            if (s ^ 1)
                printf("%lld*", s);
            printf("sqrt(%lld)", t);
            if (tt ^ 1)
                printf("/%lld", tt);
            printf("\n");
        }
    }
    return 0;
}
