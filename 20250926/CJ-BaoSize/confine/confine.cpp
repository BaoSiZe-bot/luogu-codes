#include "confine.h"
#include <string>

using std::string;

string s;
int gn, f;
void dfs(int x)
{
    if (x == 0)
    {
        f = dodoco(s);
        return;
    }
    s.push_back('0');
    dfs(x - 1);
    if (f == gn)
        return;
    s.back() = '1';
    dfs(x - 1);
    s.pop_back();
};
void confine(int n)
{
    gn = n;
    dfs(n);
}
