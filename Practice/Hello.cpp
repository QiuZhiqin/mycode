#include "StructureofData.hpp"
#include <unistd.h>
using namespace std;
enum classifications
{
    food,
    drink,
    others
};
struct goods
{
    float price;
    union
    {
        char id_char[20];
        int id_num;
    } id;
    classifications classification;
};
int main()
{
    const char *str = "i love you";
    cout << str;
    return 0;
}