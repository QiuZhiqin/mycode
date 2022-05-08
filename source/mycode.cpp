#include "StructureofData.hpp"
using namespace std;
/*
编写一个程序，将输入字符串中的字符按如下规则排序。

规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。

如，输入： Type 输出： epTy

规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。

如，输入： BabA 输出： aABb

规则 3 ：非英文字母的其它字符保持原来的位置。
*/
void func1()
{
    string ans;
    getline(cin, ans);
    vector<pair<char, bool>> letters; //用于存储字母并排序，使用pair是为了保存大小写信息，将所有字母小写化方便排序
    bool isaletter[ans.size()];       //用于判断该位置是否为字母
    int index = 0, n = ans.size();
    for (const char &a : ans)
    {
        if (a >= 'a' && a <= 'z')
        {
            letters.push_back({a, false});
            isaletter[index++] = true;
        }
        else if (a >= 'A' && a <= 'Z')
        {
            letters.push_back({a + 32, true});
            isaletter[index++] = true;
        }
        else
        {
            isaletter[index++] = false;
        }
    }
    int j;
    for (int i = 1; i < letters.size(); i++) //插排稳定，故可保证同级字母相对位置不变
    {
        pair<char, bool> temp = letters[i];
        for (j = i; j > 0 && letters[j - 1].first > temp.first; --j)
            letters[j] = letters[j - 1];
        letters[j] = temp;
    }
    index = 0;
    for (int i = 0; i < n; ++i)
    {
        if (isaletter[i] == true) //如果该位置是字母，则修改为排序好的数组元素；若不是字母，保持原样
        {
            if (letters[index].second == true)
                ans[i] = letters[index++].first - 32;
            else
                ans[i] = letters[index++].first;
        }
    }
    cout << ans;
}
