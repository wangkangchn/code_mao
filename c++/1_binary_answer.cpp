/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 1_binary_answer.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二分答案法
时间	   	: 2023-05-17 22:17
***************************************************************/
#include <iostream>

int books{0};           /* 书本数 */
int cats{0};            /* 猫猫数目 */
int pages[1005]{0};     /* 书本页数 */

/**
 *     检查所有猫是否能在指定的抄写能力下, 完成所有书本的抄写
 *
 * @param [in]  capacity:  每只猫的抄写能力
 * @return      1:  可以完成
 *              0:  不可以完成
 */
int check(int capacity)
{
    int cnt_cat     = 1;    /* 抄写书本的猫猫数目 */
    int sum_page    = 0;    /* 已抄写的总页数 */

    for (int i = 0; i < books; ++i) {   /* 一本书一本书的计算 */
        /* 当存在某一本书的数目大于猫猫的抄写能力时, 
        代表着猫猫肯定不能完成任务, 因为一本书只能由一只猫猫来完成 */
        if (pages[i] > capacity) {      
            return 0; 
        }

        if (sum_page + pages[i] <= capacity) {
            sum_page += pages[i];
        } else {
            /* 已达到当前猫猫的最大抄写能力, 换下一只 */
            ++cnt_cat;
            sum_page = pages[i];
        }
    }

    /* 所需要的猫猫数量少于指定的数目 */
    if (cnt_cat <= cats) {
        return 1;
    }
    return 0;
}

int main()
{
    int T, x;
    std::cin >> books >> cats >> T;

    std::cout << T << std::endl;

    for (int i = 0; i < books; i++) {
        std::cin >> pages[i];
    }
    while (T--) {
        std::cin >> x;
        if (check(x)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}