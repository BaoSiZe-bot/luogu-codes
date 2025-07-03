#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
int s[50005][26], fl[50005], q[50005], nct, hd, tl;
std::vector<std::string> cnt[50005];
std::string ss[155];
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while (std::cin >> n, n)
    {
        memset(s, 0, sizeof s);
        memset(fl, 0, sizeof fl);
        memset(q, 0, sizeof q);
        for (int i = 0; i <= nct; i++)
            cnt[i].clear();
        nct = 0;
        std::string t;
        __gnu_pbds::gp_hash_table<std::string, int> mp;
        for (int i = 1; i <= n; i++)
        {
            std::cin >> ss[i];
            int now = 0;
            for (auto i : ss[i])
                now = (!s[now][i - 'a'] && (s[now][i - 'a'] = ++nct), s[now][i - 'a']);
            cnt[now].push_back(ss[i]);
        }
        hd = 1;
        tl = 0;
        for (int i = 0; i < 26; i++)
            if (s[0][i])
            {
                fl[s[0][i]] = 0;
                q[++tl] = s[0][i];
            }
        while (hd <= tl)
        {
            int u = q[hd++];
            for (int i = 0; i < 26; i++)
                if (s[u][i])
                {
                    fl[s[u][i]] = s[fl[u]][i];
                    q[++tl] = s[u][i];
                }
                else
                    s[u][i] = s[fl[u]][i];
        }
        std::cin >> t;
        int now = 0;
        for (auto i : t)
        {
            now = s[now][i - 'a'];
            for (int t = now; t; t = fl[t])
                for (const auto &j : cnt[t])
                    mp[j]++;
        }
        int res = 0;
        for (const auto &i : mp)
            res = std::max(res, i.second);
        std::cout << res << '\n';
        for (int i = 1; i <= n; ++i)
            if (mp[ss[i]] == res)
                std::cout << ss[i] << '\n';
    }
    return 0;
}
