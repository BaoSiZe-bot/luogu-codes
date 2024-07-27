#include <cstdio>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int a, b, x = 1, y = 2;
        scanf("%d%d", &a, &b);
        for (int i = 1; i <= a * 2 + b; ++i)
        {
            printf("%d %d\n", x, y);
            ++y;
            if (y == a + 1)
            {
                x++;
                y = x + 1;
            }
        }
    }
    return 0;
}
