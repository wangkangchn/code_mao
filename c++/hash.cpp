/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: hash.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 散列表
    https://cplusplus.com/reference/string/string/?kw=string
时间	   	: 2023-07-26 21:21
***************************************************************/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <algorithm>


/**
 *     计算数组中两数和为 target 的数对数目
 *
 *  从头编译到尾, 计算 target - a[i] 存在散列表中, 就说明满足条件, 数对 +1
 *  不满足条件就将其加入到散列表中, 以备后续使用
 * 
 * @param [in]  nums    待搜索数组
 * @param [in]  target  目标数据 
 * @return     数对数目
 */
size_t twoSum(const std::vector<int>& nums, int target) 
{
    std::unordered_map<int, int> tab;
    size_t num = 0;

    /* 建表 */
    for (int i = 0; i < nums.size(); ++i)
    {   
        auto it = tab.find(target - nums[i]);
        if (it != tab.end()) {   /* 找到 */
            ++num;
        }

        /* 没找到就入队 */
        tab.insert({nums[i], i});
    }
    return num;
}


int main_two_sum()
{
    std::cout << twoSum({5, 12, 7, 10, 9, 1, 2, 3, 11}, 13) << std::endl;
    return 0;
}


#define ELAPSED(name) \
    for (auto _start_ = std::chrono::high_resolution_clock::now(), _end_ = _start_;\
        _start_ == _end_;\
        _end_ = std::chrono::high_resolution_clock::now(),\
        std::cout << name << "耗时: " << std::chrono::duration_cast<std::chrono::milliseconds>(_end_ - _start_).count() << " ms" << std::endl)

int main_time()
{   
    const int num = 100000;
    std::vector<int> array(num);
    std::unordered_map<int, int> myhash(num);
    for (int i = 0; i < num; ++i) {
        array[i] = i;
        myhash.emplace(i, i);
    }

    std::cout << "数组查找\n";
    /* 查找时间对比 */
    ELAPSED("数组查找") {
        for (int i = 0; i < num; ++i) {
            std::find(array.begin(), array.end(), i);
        }
    }

    std::cout << "散列查找\n";
    ELAPSED("散列查找") {
        for (int i = 0; i < num; ++i) {
            myhash.count(i);
        }
    }

    return 0;
}

int main()
{
    main_two_sum();
    main_time();
    return 0;
}