/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2299.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 编程猫分数列
时间	   	: 2023-05-23 21:26
***************************************************************/

/* 思路:

    划分的段数越多, 也就是说每段和的值越大, 越难划分成 M 段.
也就是说每段和和划分段数是单调的, 每段越大, 能划分的段数就越少
所以在每段和可能存在的范围内, 存在一个刚好划分成 M 段的点

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
