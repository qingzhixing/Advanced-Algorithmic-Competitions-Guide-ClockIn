/*
    这题同样可以使用递归和非递归，分别是DFS和BFS思路
    这里使用递归
*/
#include <iostream>
using namespace std;

#define NDEBUG
#ifdef NDEBUG
#define DEBUG(code) ((void)0)
#else
#define DEBUG(code) (code)
#endif // NDEBUG

#define MAX_N 9 + 10

int n;
int selected[MAX_N], nextId;
bool isSelected[MAX_N];

void PrintSelected()
{
    for (int i = 0; i < nextId; i++)
    {
        cout << selected[i] << ' ';
    }
    puts("");
}

void Enumerate(int timeLast)
{
}

int main()
{

    return 0;
}