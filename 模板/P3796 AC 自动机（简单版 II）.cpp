#include <bits/extc++.h>
using __gnu_pbds::gp_hash_table;
using std::cin;
using std::cout;
using std::string;
using std::vector;

int s[155][26], fl[155], q[155], nct, hd, tl;
vector<string> cnt[155];
string t;
bool vis[155];

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int Q;
    cin >> Q;
    while (Q--)
    {
        memset(s, 0, sizeof s);
        memset(fl, 0, sizeof fl);
        memset(vis, 0, sizeof vis);
        nct = 0;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> t;
            int now = 0;
            for (auto i : t)
                now = (!s[now][i - 'a'] && (s[now][i - 'a'] = ++nct), s[now][i - 'a']);
            cnt[now].clear();
            cnt[now].push_back(t);
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
        cin >> t;
        int now = 0;
        gp_hash_table<string, int> mp;
        for (auto i : t)
        {
            now = s[now][i - 'a'];
            for (int t = now; t && !vis[t]; t = fl[t])
            {
                for (const auto &j : cnt[t])
                    mp[j]++;
                vis[t] = true;
            }
        }
        int res = 0;
        for (const auto &i : mp)
            res = std::max(res, i.second);
        cout << res << '\n';
        for (const auto &i : mp)
            if (i.second == res)
                cout << i.first << '\n';
    }
    return 0;
}
