#include <stdio.h>
#include <string.h>
const int N = 1005;
bool vis[N][N];  // 填充标记
char str[N][N];  // 原字符集
int res[N];  // 答案数组
char hor[N];  // 横向字符集
char ver[N];  // 纵向字符集
char vtp[N];  // check 所用的临时字符串
char htp[N];  // check 所用的临时字符串
int n;  // 题面中的 n
int m;  // 题面中的 m
int cnt;  // 答案总数
// 取 x 和 y 的最大值
__always_inline int max(int x, int y)
{
    return x < y ? y : x;
}

// 判断长度 len 是否合法
__always_inline bool chk(int len, const char tmp[])
{
    printf("I need to check the string %s and it's length is %d\n", tmp, len);
    memset(vis, 0, sizeof vis);  // 初始化填充标记
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (!vis[i][j])
            {
                bool flg = true;  // 判断该长条是否可填充
                if (m - j + 1 >= len)  // 横向填充
                {
                    for (int k = 1; k <= len; ++k)
                        if (vis[i][j + k - 1] || str[i][j + k - 1] != tmp[k])
                        {
                            flg = false;  // 无法填充
                            break;
                        }
                    if (flg)  // 可以填充
                        for (int k = 1; k <= len; ++k)
                            vis[i][j + k - 1] = true;
                }
                else if (n - i + 1 >= len)  // 纵向填充
                {
                    for (int k = 1; k <= len; ++k)
                        if (vis[i + k - 1][j] || str[i + k - 1][j] != tmp[k])
                        {
                            flg = false;  // 无法填充
                            break;
                        }
                    if (flg)  // 可以填充
                        for (int k = 1; k <= len; ++k)
                            vis[i + k - 1][j] = true;
                }
                else  // 无法填充
                    return false;
                if (vis[i][j] == false)  // 无法填充
                    return false;
            }
    return true;  // 填充成功
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%1000s", str[i] + 1);
    for (int i = 1; i <= n; ++i)
        ver[i] = str[i][1];  // 初始化纵向字符集
    for (int i = 1; i <= m; ++i)
        hor[i] = str[1][i];  // 初始化横向字符集
    for (int i = 1; i <= n || i <= m; ++i)
    {
        vtp[i] = ver[i];
        htp[i] = hor[i];
        if (n % i == 0 || m % i == 0)  // 判断是否为约数
        {
            if (i <= m && chk(i, htp + 1))  // 判断是否合法
                res[++cnt] = i;
            if (i <= n && chk(i, vtp + 1))  // 判断是否合法
                res[++cnt] = i;
        }
    }
    printf("%d\n", cnt);  // 输出答案数量
    for (int i = 1; i <= cnt; ++i)
        printf("%d ", res[i]);  // 输出答案
    return 0;
}
