#include <iostream>
#include <set>
#include <string>
const int N = 105;
std::string s[N];
int main(int argc, char *argv[])
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> s[i];
    }
    std::set<std::string> st;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i ^ j)
            {
                st.insert(s[i] + s[j]);
            }
        }
    }
    std::cout << st.size();
    return 0;
}
