#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
int main(int argc, char **argv)
{
    string str;
    cin >> str;
    if (str.size() <= 0)
        return 0;
    unordered_map<char, int> myMap;
    vector<int> ans;
    int len = str.size();
    for (int i = 0; i < len; ++i)
        myMap[str[i]] = i;
    for (int i = 0; i < len;)
    {
        int cur = myMap[str[i]], count = 0;
        while (i <= cur)
        {
            cur = max(cur, myMap[str[i]]);
            count++;
            ++i;
        }
        ans.push_back(count);
    }
    return 0;
}