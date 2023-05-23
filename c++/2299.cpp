/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2299.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 编程猫分数列
时间	   	: 2023-05-23 21:26
***************************************************************/
/* 问题

对于给定的一个长度为N的正整数数列A[i]，现要将其分成M（M≤N）段，并要求每段连续，且每段和的最大值最小。
关于最大值最小：
例如一数列4 2 4 5 1要分成3段
将其如下分段：[4 2][4 5][1]
第一段和为6，第2段和为9，第3段和为1，和最大值为9。
将其如下分段：[4][2 4][5 1]
第一段和为4，第2段和为6，第3段和为6，和最大值为6。
并且无论如何分段，最大值不会小于6。
所以可以得到要将数列4 2 4 5 1要分成3段，每段和的最大值最小为6。

输入
第1行包含两个正整数 N，M。
第2行包含 N个空格隔开的非负整数 A[i]，含义如题目所述。

数据范围：
对于 50% 的数据有 1 <= N <= 100
对于 80% 的数据有 1 <= N <= 10000
对于 100% 的数据有 1 <= N <= 100000, A[i] 之和不超过 10^9

输出
仅包含一个正整数，即每段和最大值最小为多少。

输入样例
5 3
4 2 4 5 1

输出样例 
6
*/

#include <iostream>


int array_length    = 0;
int segments        = 0;
int array[100005]   = {0};

/**
 *     给定一个每段的最大值, 判断当前数列能够依据这个最大值划分成我们
 * 所需的段数
 *
 * @return      1:  可以完成
 *              0:  不可以完成
 */
int check(int max_value)
{
    int cnt_segment                 = 1;
    int sum_current_segment         = 0;

    for (int i = 0; i < array_length; ++i) {

        if (array[i] > max_value) {      
            return 0; 
        }

        if (sum_current_segment + array[i] <= max_value) {
            sum_current_segment += array[i];
        } else {
            ++cnt_segment;
            sum_current_segment = array[i];
        }
    }

    /* 所需要的猫猫数量少于指定的数目 */
    if (cnt_segment <= segments) {
        return 1;
    }
    return 0;
}


int main()
{
    std::cin >> array_length >> segments;

    int start = 0, end = 0;

    for (int i = 0; i < array_length; i++) {
        std::cin >> array[i];

        start = std::max(start, array[i]);  /* 寻找起点 */
        end += array[i];                    /* 寻找终点 */
    }

    int res = 0;                            /* 答案 */
    while (start <= end) {
        int mid = (start + end) / 2;
        if (check(mid)) {
            res = mid;
            end = mid - 1;
        } else {                           
            start = mid + 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}
