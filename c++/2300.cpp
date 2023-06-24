/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2300.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: OJ. 2300 严厉的贡菊
时间	   	: 2023-05-24 20:18
***************************************************************/

/* 思路:
    跳跃最短距离的最大值
    在每只猫能跳跃距离的范围内, 如果某一个跳跃距离 x 能满足条件, 
x - 1 也是可行的(少拿几个柱子嘛)
 */


#include <iostream>

const size_t MAX_NUM    = 5005;

int length                  = 0;            /* 起点到终点的距离 */
int num_cabinets            = 0;            /* 柜子数目 */
int num_cabinets_moved      = 0;            /* 需要移走的柜子数目 */
int distances[MAX_NUM]      = {0};

/**
 *     检查按照指定的最小跳跃距离, 移除柜子时, 能否满足条件
 * 
 *  起点  a1, a2, a3, a4, a5, ..., 终点
 */
int check(int min_jump_distance)
{
    int num_move                = 0;          /* 移走柜子的数目 */
    int last_cabinet_distance   = 0;          /* 上一个柜子的位置距起点的距离 */
    for (int i = 0; i < num_cabinets; ++i) {
        /* 当前两个柜子间的距离比指定的最小距离要大, 说明可以保留, 
        因为我们最小 min_jump_distance, 大于它就可以保留 */
        if (distances[i] - last_cabinet_distance >= min_jump_distance) {
            last_cabinet_distance = distances[i];
        } else {
            /* 小于了最小距离, 那就需要移走柜子 */
            ++num_move;
        }
    }

    if (length - last_cabinet_distance < min_jump_distance) {
        ++num_move;
    }

    if (num_move <= num_cabinets_moved) {
        return 1;
    }
    return 0;
}


int main()
{   
    std::cin >> length >> num_cabinets >> num_cabinets_moved;

    for (int i = 0; i < num_cabinets; i++) {
        std::cin >> distances[i];
    }

    int start = 1, end = length;
    int res = 0;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (check(mid)) {                   /* 可以移走, 那就说明这个距离不是最大的, 就往右走 */
            res = mid;
            start = mid + 1;
        } else {                           
            end = mid - 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}