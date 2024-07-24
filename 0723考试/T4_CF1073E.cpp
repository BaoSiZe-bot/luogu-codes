#include <cstdio>
#include <cstring>
#include <string>
#define int long long
using std::string;

const int M = 998244353;
int ff[15][2][2][2005], dp[15][2][2][2005];
int l, r, k;
inline int clc(const int &x)
{
    memset(ff, 0, sizeof ff);
    memset(dp, 0, sizeof dp);
    string st = std::to_string(x);
    ff[0][0][0][0] = 1;
    int len = st.size(), res = 0;
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < 2; ++j)
            for (int p = 0; p < 2; ++p)
                for (int l = 0; l < 1024; ++l)
                    if (ff[i][j][p][l])
                    {
                        int of = ff[i][j][p][l], od = dp[i][j][p][l], lm = j ? 9 : st[i] ^ 48;
                        for (int q = 0; q <= lm; ++q)
                        {
                            int tp = p || q ? l | (1 << q) : l;
                            dp[i + 1][j || (q < lm)][p || q][tp] = ((dp[i + 1][j || (q < lm)][p || q][tp] + (od << 1) + (od << 3)) % M + q * of) % M;
                            ff[i + 1][j || (q < lm)][p || q][tp] = (ff[i + 1][j || (q < lm)][p || q][tp] + of) % M;
                        }
                    }
    for (int j = 0; j < 2; ++j)
        for (int p = 0; p < 2; ++p)
            for (int l = 0; l < 1024; ++l)
                if (__builtin_popcount(l) <= k)
                    res = (res + dp[len][j][p][l]) % M;
    return res;
}
signed main()
{
    scanf("%lld%lld%lld", &l, &r, &k);
    printf("%lld\n", (clc(r) - clc(l - 1) + M) % M);
    return 0;
}
