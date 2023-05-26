/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: 2303.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: OJ. 2303 征收猫罐头
时间	   	: 2023-05-26 20:41
***************************************************************/

/* 
思路:
    求的是这 b 个人在能收完猫罐头的前提下, 每个人能收罐头的最小值,
问怎么分配?
    
    每个人最少可以只收多少个罐头? 最少的情况是一对一收, 所以最少可以
是 1 个, 那最多就是多少? 最多是一个人收人数最多的那个城市.
在这个范围内, 随着每个人能收罐头数目的增多, 所需的人就越少, 所以
每个人能收罐头数目与所需人是单调的, 存在一个点在之前能满足要求,
在之后就不能满足要求
 */

#include <iostream>

int num_cities  = 0;        /* 城市数目 */
int num_workers = 0;        /* 征粮队员的数目 */
int persons[1000015] = {0}; /* 每个城市中人的数目 */


/* 
    检查在指定每个人收罐头的最大数目时, 看能不能收完全部人
 */
int check(int num_person)
{
    int count_worker = 0;
    for (int i = 0; i < num_cities; i++) {
        int sum = 0;
        while (sum < persons[i]) {
            sum += num_person;
            ++count_worker;     /* 一个人不够, 加人 */
        }
    }

    /* 需要的工作人员少于给的的人, 肯定可以完成任务 */
    if (count_worker <= num_workers) {
        return 1;
    }

    return 0;
}


int main()
{
    std::cin >> num_cities >> num_workers;

    int start = 1, end = 0;
    for (int i = 0; i < num_cities; ++i) {
        std::cin >> persons[i];
        end = std::max(end, persons[i]);
    }

    int res = 0;
    while (start <= end) {
        int mid = (start + end) / 2;

        if (check(mid)) {
            /* 人数充足, 就减少没人收罐子数目 */
            res = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}