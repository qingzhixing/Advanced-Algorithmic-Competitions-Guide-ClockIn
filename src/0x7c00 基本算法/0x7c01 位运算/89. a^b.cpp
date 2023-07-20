// 一眼快速幂

#include <iostream>
using namespace std;

int a, b, p;

uint64_t answer = 1;

int main()
{
    // 特殊判断一下0
    cin >> a >> b >> p;
    if (b == 0)
    {
        cout << 1 % p;
        return 0;
    }

    // 接下来是快速幂
    // 我们在快速幂中多次 %p,结果保持不变，证明：
    // https://www.acwing.com/community/content/432/#answer_380
    /*
        证明 (a * b) mod p = [(a mod p) * (b mod p)] mod p:
            令 a = kp + r, b = mp + n
            左式 = (a * b) mod p = (kp + r)(mp + n)mod p =
                (kmp^2 + knp + rmp) mod p = rn mod p
            右式 = [(a mod p) * (b mod p)] mod p =
                {[(kp + r) mod p] * [(mp + n) mod p]} mod p =
                rn mod p
            故 左式 = 右式
    */
    uint64_t aPow = a;
    do
    {
        if (b & 1)
        {
            answer = (answer * aPow) % p;
        }
        b >>= 1;
        aPow = (aPow * aPow) % p;
    } while (b);

    cout << answer;
    return 0;
}