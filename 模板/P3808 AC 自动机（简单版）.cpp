#include <string>
#include <vector>
#include <iostream>
int s[1000005][26], fl[1000005], q[1000005], nct, hd, tl;
std::vector<std::string> cnt[1000005];
std::string t;
bool vis[1000005];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> t;
        int now = 0;
        for (auto i : t)
            now = (!s[now][i - 'a'] && (s[now][i - 'a'] = ++nct), s[now][i - 'a']);
        cnt[now].push_back(t);
    }
    hd = 1;
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
    int now = 0, res = 0;
    for (auto i : t)
    {
        now = s[now][i - 'a'];
        for (int t = now; t && !vis[t]; t = fl[t])
        {
            res += static_cast<int>(cnt[t].size());
            vis[t] = true;
        }
    }
    printf("%d\n", res);
    return 0;
}
