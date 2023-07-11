/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: greed.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 贪心算法
时间	   	: 2023-07-11 20:54
***************************************************************/
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>   //std::setprecision函数需要引入该头文件

/**
 *     计算独木舟的数目
 * 
 *  每次最轻的和最重的一起放, 能放下, 就放下, 放不下, 重的单独一条
 *
 * @param [in]  w               每条独木舟最大载重两
 * @param [in]  person_weight   每个人的体重
 * @return     所需独木舟的个数
 */
int compute_boat_num(int w, std::vector<int>& person_weight)
{
    /* 1. 先将行人体重按小到大进行排序 */
    std::sort(person_weight.begin(), person_weight.end());

    /* 2. 最小最大组合进行装船 */
    int num = 0;    /* 已装满的船数 */

    int start = 0, end = person_weight.size() - 1;

    while (start < end) {
        if (person_weight[start] + person_weight[end] <= w) {
            /* 能够同时放下, 就放下 */
            ++start;
            --end;
        } else {
            --end;
        }
        ++num;

        if (start == end) { /* 只剩一个人也要乘船 */
            ++num;
        }
    }

    return num ;
}

int main_boat()
{   
    // int w, n;
    // std::cin >> w;  /* 每条船最大载重 */
    // std::cin >> n;  /* 人数 */

    // std::vector<int> people_weight(n);
    // for (int i = 0; i < n; ++i) {
    //     std::cin >> people_weight[i];
    // }
    
    int w = 100, n = 9;
    std::vector<int> people_weight{ 90, 20, 20, 30, 50, 60, 70, 80, 90};


    std::cout << "所需独木舟数目: " << compute_boat_num(w, people_weight) << std::endl;
    return 0;
}


/**
 *     排队接水
 *  排队接水等待的最短时间就是, 一起等短的时间, 让长的时间越少人等
 *
 * @param [in]  times   每个人的打水时间
 * @param [out] id      排队序号
 * @return     平均时间
 */
float water(std::vector<int>& times, std::vector<int>& ids)
{
    ids.clear();
    for (int i = 0; i < times.size(); ++i) {
        ids.emplace_back(i);
    }

    /* 排队序号也就是排序后序号 */
    std::sort(ids.begin(), ids.end(), [&times] (int a, int b) { return times[a] < times[b]; });
    std::transform(ids.begin(), ids.end(), ids.begin(), [] (int& v) {return v + 1;});  /* 序号 + 1 */

    /* 等待时所有人都需要等 */
    float sum_time = 0.f;

    std::sort(times.begin(), times.end());
    int num = times.size();             /* 人数 */
    for (int i = 0; i < num - 1; i++) { /* 最后一个人的时间不需要等 */
        sum_time += (num - i - 1) * times[i];
    }

    return sum_time / num;
}

int main_water()
{
    std::vector<int> times {56, 12, 1, 99, 1000, 234, 33, 55, 99, 812 };
    std::vector<int> ids;
    float mean_time = water(times, ids);

    std::cout << "排序序号为: ";
    for (auto i : ids) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "平均时间为: " ;
    // cout固定输出2位小数，整数部分完整保留
    std::cout << std::fixed << std::setprecision(2) << mean_time << std::endl;
    return 0;
}


/**
 *     删数
 * 
 *     找的就是从高到低位, 第一次出现减小的值, 因为其后比它小, 前面也比它小
 *  拼起来之后, 数字肯定会是当前删除后最小的
 * 
 * @param [in out]  num     待删除数字序列
 * @param [in]      s       删除次数 
 * @return     无
 */
void delete_num(std::vector<int>& num, int s)
{
    for (int i = 0; i < s; ++i) {

        for (auto it = num.begin(); it != num.end() - 1;) {
            if (*it > *(it + 1)) {  /* 小于后一个数的就删掉 */
                num.erase(it);
                break;
            } else if (*it == *(it + 1)) {  /* 相等不做处理 */
            
            } else {
                if ((it + 1) == (num.end() - 1)) {  /* 这里还要判断的一个条件是, 这是一个递增数列, 要删除最后一项 */
                    num.erase(it + 1);
                    break;
                }
            }
            ++it;
        }
    }
}

int main_num()
{   
    std::vector<int> num { 1, 2, 1, 3, 7, 8, 5, 4, 4, 3 };
    int s = 4;
    delete_num(num, s);
    std::cout << "删除后序列: ";
    for (auto v : num) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}

int main()
{
    // main_boat();
    // main_water();
    main_num();
    return 0;
}