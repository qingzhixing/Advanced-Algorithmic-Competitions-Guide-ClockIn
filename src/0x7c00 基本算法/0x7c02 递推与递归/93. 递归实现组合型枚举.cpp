/*
    使用递归方法的话直接可以复用上一题的代码
    这题我还提供一个非递归的做法
*/
#include <iostream>
using namespace std;

#define NDEBUG
#ifdef NDEBUG
#define DEBUG(code) ((void)0)
#else
#define DEBUG(code) (code)
#endif // NDEBUG

#define MAX_SELECTED 25 + 10

int n, m;
// 用于记录枚举的数字
int selected[MAX_SELECTED], nextIndex = 0;

void PrintSelectedNumbers()
{
    for (int index = 0; index < nextIndex; index++)
    {
        cout << selected[index] << ' ';
    }
    puts("");
}

/*
    timeLast:还能够枚举的数字的个数
    lastNumber:上一个枚举的数字，需要升序枚举
*/
void Enumerate(int timeLast, int lastNumber)
{
    if (timeLast == 0)
    {
        PrintSelectedNumbers();
        return;
    }
    // 枚举当前数字
    /*
        这里注意一下当前数字能枚举的范围，在上一个数字之后，但是不能无限制往后枚举
        不然会出现后面数字不够用的问题，最多到 (n - timeLast + 1)
    */
    for (int currentNumber = lastNumber + 1; currentNumber <= (n - timeLast + 1); currentNumber++)
    {
        // 选择当前数字
        selected[nextIndex++] = currentNumber;
        // 选择下一个数字
        Enumerate(timeLast - 1, currentNumber);
        // 回溯
        nextIndex--;
    }
}

int main()
{
    cin >> n >> m;
    // 枚举选 1 ~ n 个数字的 n 种情况
    Enumerate(m, 0);
    return 0;
}