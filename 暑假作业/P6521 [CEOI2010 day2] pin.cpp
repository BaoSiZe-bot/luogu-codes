#include <string>
#include <iostream>
const int b0 = 1, b1 = 37, b2 = 1369, b3 = 50653, b4 = 1874161;
int s[50005][4], mp[2000005], sm[5], res[5];
inline int conv(char c)  // conversion char to base37 int
{
    return c >= '0' && c <= '9' ? c - '0' + 1 : c >= 'a' && c <= 'z' ? c - 'a' + 11 : -999;  //c - 86 = c - 'a' + 11
}
inline int gcnt(int x)  // get count of how many zero digit in base37 x
{
    static int cnt;
    cnt = 0;
    while (x)
    {
        cnt += bool(x % 37);
        x /= 37;
    }
    return cnt;
}
int main()
{
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i)
    {
        std::string t;
        std::cin >> t;
        s[i][0] = conv(t.at(0));
        s[i][1] = conv(t.at(1));
        s[i][2] = conv(t.at(2));
        s[i][3] = conv(t.at(3));
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                for (int p = 0; p < 2; ++p)
                    for (int l = 0; l < 2; ++l)
                        ++mp[s[i][0] * b0 * j + s[i][1] * b1 * k + s[i][2] * b2 * p + s[i][3] * b3 * l];
    for (int i = 1; i < b4; i++)
        sm[gcnt(i)] += mp[i] * (mp[i] - 1) / 2;
    res[4] = sm[4];
    res[3] = sm[3] - res[4] * 4;
    res[2] = sm[2] - res[3] * 3 - res[4] * 6;
    res[1] = sm[1] - res[2] * 2 - res[3] * 3 - res[4] * 4;
    res[0] = n * (n - 1) / 2 - res[1] - res[2] - res[3];
    printf("%d", res[4 - d]);
    return 0;
}
