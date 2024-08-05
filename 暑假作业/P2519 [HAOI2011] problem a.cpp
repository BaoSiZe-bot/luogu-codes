#include <stdio.h>
#include <algorithm>
std::pair<int, int> s[100005];
int a[100005], dp[100005], rl[100005], rr[100005];  //re-genterated l and r
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
//~auto~ generated by archlinux, Hyprland, neovim, lazyvim, clangd, rofi.
int main()
{
    int n, k = 0, t = 0;
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n; ++i)
    {
        scanf("%d%d", &u, &v);
        if (u + v < n)
            s[++k] = {n - v, u + 1};
    }
    std::sort(s + 1, s + k + 1);
    for (int i = 1; i <= k; ++i)
    {
        t += s[i] != s[i - 1];
        a[t] = min(a[t] + 1, s[i].first - s[i].second + 1);
        rl[t] = s[i].second;
        rr[t] = s[i].first;
    }
    int lst = 1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1];
        for (; lst <= t && rr[lst] == i; ++lst)
            dp[i] = max(dp[i], dp[rl[lst] - 1] + a[lst]);
    }
    printf("%d", n - dp[n]);
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
