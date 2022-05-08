#include "StructureofData.hpp"
#include <unistd.h>
using namespace std;
enum classifications
{
    food,
    drink,
    others
};
class goods
{
public:
    float price;
    union
    {
        string id_char = "";
        int id_num;
    } id;
    classifications classification;
};
int main()
{
    return 0;
}