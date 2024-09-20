#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
char s[100005];
std::bitset<100005> fd[26];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%100000s", s + 1);
        int n = strlen(s + 1);
        for (int i = 0; i < 26; ++i)
        {
            fd[i].reset();

        }
    }
    return 0;
}
