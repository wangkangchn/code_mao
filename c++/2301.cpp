/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2301.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: OJ. 2301 砍树
时间	   	: 2023-05-25 21:03
***************************************************************/

/* 思想:
题目中问的是需要升高多少米, 能至少得到 M 的木材, 
那么伐木工人伐木时可以升高的米数最少可以是 0 米, 最大可以是最高树的高度,
并且在这个范围内, 随着米数的升高, 得到的木材总长度必然减少, 区间内单调
所以可以用二分在这个范围内搜索
这里的单调指的是, 升高米数越高, 得到木材长度越少, 那么必然存在一个点, 
使得升高 x 时, 刚好得到 M 的木材
 */

#include <iostream>

int num_trees       = 0;    /* 树木的总数 */
int needed_length   = 0;    /* 需要木材的总长度 */
int heighs[1000009] = {0};


/*  */
int check(int cut_height)
{
    int length = 0;         /* 已获得的木材长度 */
    for (int i = 0; i < num_trees; ++i) {
        int remain_height = heighs[i] - cut_height;
        if (remain_height > 0) {   /* 这棵树够长, 要了剩余的 */
            length += remain_height;
        }
    }

    if (length >= needed_length) {
        return 1;
    }

    return 0;
}

int main()
{
    std::cin >> num_trees >> needed_length;
    
    int start = 0, end = 0;
    for (int i = 0; i < num_trees; ++i) {
        std::cin >> heighs[i];

        end = std::max(end, heighs[i]);
    }

    int ans;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (check(mid)) {       /* 当前可以, 说明不是极限, 继续向上 */
            start = mid + 1;
            ans = mid;  
        } else {
            end = mid - 1;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}