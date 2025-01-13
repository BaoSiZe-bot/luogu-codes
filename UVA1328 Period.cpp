#include <cstdio>
const int N = 1e6 + 5;
char s[N];
int nx[N];
int main()
{
    int n, id = 0;
    while (scanf("%d", &n), n)
    {
        printf("Test case #%d\n", ++id);
        scanf("%s", s + 1);
        int p = 0;
        for (int i = 2; i <= n; ++i)
        {
            while (p && s[i] ^ s[p + 1])
                p = nx[p];
            if (s[i] == s[p + 1])
                ++p;
            nx[i] = p;
            if (p && i % (i - p) == 0)
                printf("%d %d\n", i, i / (i - p));
        }
        printf("\n");
    }
    return 0;
}
