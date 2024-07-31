#include <cstdio>
using ll = long long;
inline ll cl(ll x, ll y)
{
    return x / y + bool(x % y);
}
int main()
{
    ll t;
    scanf("%lld", &t);
    while (t--)
    {
        ll x, y, k;
        scanf("%lld%lld%lld", &x, &y, &k);
        if (x > y)
        {
            printf("%lld\n", k);
            continue;
        }
        ll _ = 11 * x * k;
        ll $ = 2 * x + 11 * y;
        printf("%lld\n", _ / $);
    }
    return 0;
}
/*
                  -`
                 .o+`
                `ooo/
               `+oooo:
              `+oooooo:
              -+oooooo+:
            `/:-:++oooo+:
           `/++++/+++++++:                           _       _      _                   __     ____     _______   _____ _ 
          `/++++++++++++++:           /\            | |     | |    (_)                  \ \   / /\ \   / /  __ \ / ____| |
         `/+++ooooooooooooo/`        /  \   _ __ ___| |__   | |     _ _ __  _   ___  __  \ \_/ /  \ \_/ /| |  | | (___ | |
        ./ooosssso++osssssso+`      / /\ \ | '__/ __| '_ \  | |    | | '_ \| | | \ \/ /   \   /    \   / | |  | |\___ \| |
       .oossssso-````/ossssss+`    / ____ \| | | (__| | | | | |____| | | | | |_| |>  <     | |      | |  | |__| |____) |_|
      -osssssso.      :ssssssso.  /_/    \_\_|  \___|_| |_| |______|_|_| |_|\__,_/_/\_\    |_|      |_|  |_____/|_____/(_)
     :osssssss/        osssso+++.
    /ossssssss/        +ssssooo/-
  `/ossssso+/:-        -:/+osssso+
 `+sso+:-`                 `.-/+oso:
`++:.                           `-/+/
.`                                 `/
*/
