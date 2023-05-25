/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2304.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: OJ. 2304 编程猫买罐头
时间	   	: 2023-05-25 21:23
***************************************************************/

/* 
思路:
    问的是要带至少多少钱能买到 m 个罐头
编程猫买到 m 个罐头可以带钱, 最少可以带 1, 最多可以所有罐头总钱数
但是在这个范围内, 带的钱少并不意味着可以买的罐头就少,
假如店里有五个罐头, 价格分别是: 10, 1, 1, 1, 1
如果小猫带了 10 块钱, 那它就只能买 1 个 10 块的罐头
如果小猫带了 9 块钱, 那它就能买 4 个 1 块的罐头
所以在这个区间内, 带钱数关于买到的罐头总数并不是单调的
所以不能用二分法.

从小开始枚举, 找到那一个可以买 M 个罐头的前
 */

#include <iostream>

int max_money           = 0;        /* 最多能带的前 */
int cans_want_to_buy    = 0;        /* 想买的罐头数目 */
int num_cans            = 0;        /* 罐头总数 */
int prices[10005]       = {0};


/* 判断带指定的钱能否买到所需的罐头 */
int check(int money)
{   
    int count_cans = 0;             /* 买到的罐头数目 */
    for (int i = 0; i < num_cans; ++i) {
        if (money >= prices[i]) {
            money -= prices[i];
            ++count_cans;
        }

        if (money == 0) {           /* 没钱了 */
            break;
        }
    }

    if (count_cans >= cans_want_to_buy) {
        return 1;
    } 

    return 0;
}


int main()
{
    std::cin >> max_money >> cans_want_to_buy >> num_cans;

    int start = 0, end = max_money;
    for (int i = 0; i < num_cans; ++i) {
        std::cin >> prices[i];
    }

    for (int money = start; money <= end; ++money) {
        if (check(money)) {
            std::cout << money << std::endl;
            return 0;
        }
    }

    std::cout << "Poor Cat!\n";
    return 0;
}