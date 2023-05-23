/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 1_binary_answer.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 二分答案法
https://blog.csdn.net/Mr_dimple/article/details/114656142?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-114656142-blog-128239899.235%5Ev36%5Epc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-114656142-blog-128239899.235%5Ev36%5Epc_relevant_default_base3&utm_relevant_index=2
时间	   	: 2023-05-17 22:17
***************************************************************/
#include <iostream>

int books       = 0;        /* 书本数 */
int cats        = 0;        /* 猫猫数目 */
int pages[1005] = {0};      /* 书本页数 */

/**
 *     检查所有猫是否能在指定的抄写能力下, 完成所有书本的抄写
 *
 * @param [in]  capacity:  每只猫的抄写能力
 * @return      1:  可以完成
 *              0:  不可以完成
 */
int check_2293_1(int capacity)
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


int check_2293_2(int capacity)
{
    int cnt_cat             = 1;    /* 抄写书本的猫猫数目 */
    int sum_page            = 0;    /* 已抄写的总页数 */
    int current_book_idx    = 0;    /* 当前抄写数目的索引 */

    while (cnt_cat <= cats) {        /* 一只猫一只猫的计算 */
        if (current_book_idx >= books) {
            return 1;
        }

        /* 当前猫还没有达到抄书的能力极限, 就可以继续抄书 */
        if (sum_page + pages[current_book_idx] <= capacity) {
            sum_page += pages[current_book_idx];
            ++current_book_idx;
        } else {
            ++cnt_cat;
            sum_page = 0;
        }
    }

    return 0;
}

/* OJ. 2293 抄的完吗? */
int main_2293()
{
    int T, x;
    std::cin >> books >> cats >> T;

    for (int i = 0; i < books; i++) {
        std::cin >> pages[i];
    }

    while (T--) {
        std::cin >> x;
        if (check_2293_1(x)) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}


/* OJ.2295 超多少页 */
int main_2295()
{
    std::cin >> books >> cats;

    int start = 0, end = 0;

    for (int i = 0; i < books; i++) {
        std::cin >> pages[i];

        start = std::max(start, pages[i]);  /* 寻找包含最多书页的书作为枚举起点 */
        end += pages[i];                    /* 总书页作为枚举终点 */
    }

    for (int x = start; x <= end; ++x) {
        if (check_2293_1(x)) {
            std::cout << x << std::endl;
            break;                          /* 只要找到第一个能抄完的书页数, 猫猫就可以完成任务 */
        }
    }

    return 0;
}


/* OJ.2297 编程猫抄书 */
int main_2297()
{
    std::cin >> books >> cats;

    int start = 0, end = 0;

    for (int i = 0; i < books; i++) {
        std::cin >> pages[i];

        start = std::max(start, pages[i]);  /* 寻找包含最多书页的书作为枚举起点 */
        end += pages[i];                    /* 总书页作为枚举终点 */
    }

    int res = 0;                            /* 答案 */
    while (start <= end) {
        int mid = (start + end) / 2;
        if (check_2293_1(mid)) {            /* mid 可以完成抄书, 那可能还有更小值, 所以向左边继续搜索 */
            res = mid;
            end = mid - 1;
        } else {                            /* mid 抄不完, 那就是说, 每只猫需要更强的抄书能力 */
            start = mid + 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}

int main()
{   
    // main_2293();

    // main_2295();
    
    main_2297();

    return 0;
}