/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2302.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: OJ. 2302 木材加工
时间	   	: 2023-05-26 20:13
***************************************************************/

/* 
思路:
    切割的小木段越短是不是越容易完成任务, 而切的越长越不容易完成任务
所以在小木段可以切割的范围内, 切割木段长度的与能否切除 k 段是单调的.
所以我们可以再小木段的切割范围内使用二分法去找能满足条件的最大的长度
 */

#include <iostream>

int num_wood            = 0;        /* 木材的总数目 */
int lengths[100005]     = {0};      /* 每段木材的长度 */
int num_segments        = 0;        /* 想要得到的木段数目 */


/**
 *     检查在给定小木段长度下, 看能不能切出指定数目的小木段
 */
int check(int length_segment)
{
    int count_segment = 0;

    for (int i = 0; i < num_wood; ++i) {
        /* 计算没跟木材能截多少段 */
        count_segment += lengths[i] / length_segment;   
    }

    if (count_segment >= num_segments) {
        return 1;
    }

    return 0;
}


int main()
{   
    std::cin >> num_wood >> num_segments;

    int start = 0, end = 0, sum = 0;
    for (int i = 0; i < num_wood; ++i) {
        std::cin >> lengths[i];
        end = std::max(end, lengths[i]);
        sum += lengths[i];
    }

    if (sum < num_segments) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int res = 0;

    while (start <= end) {
        int mid = (start + end) / 2;
        if (check(mid)) {
            res = mid;
            start = mid + 1;    /* 能砍完说明不是最长的, 可以继续向上砍砍 */
        } else {
            end = mid - 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}