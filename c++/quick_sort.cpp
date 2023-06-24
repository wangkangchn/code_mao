/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: quick_sort.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 快排
时间	   	: 2023-06-07 21:32
***************************************************************/
#include <iostream>
#include <vector>


void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


/**
 *     
 *
 * @param [in]  data:   待排序数据
 * @param [in]  left:   待排序数据的起始索引
 * @param [in]  right:  待排序数据的终止索引
 */
void quick_sort(int* data, int left, int right)
{   
    if (left >= right) {
        return;
    }

    /* 1. 选取基准元素 */
    int t = data[(left + right) / 2];
    int i = left, j = right;

    while (i < j) {

        /* 2. 先从左到右, 找到第一个大于等于基准元素的值 */
        while (data[i] < t) {
            ++i;
        }

        /* 3. 再从右向左, 找第一个小于等于基准元素的值 */
        while (data[j] > t) {
            --j;
        }

        if (i < j) {
            swap(data + i, data + j);
            if (i + 1 == j) {
                break;
            }
        }
    }

    quick_sort(data, left, i);
    quick_sort(data, j + 1, right);
}


int main()
{
    int data[] = { 12, 10, 8, 22, 5, 5, 13, 28, 132, 21, 23, 22, 11, 3233, 222, 444, 222};
    int num = sizeof(data) / sizeof(data[0]);

    quick_sort(data, 0, num - 1);

    for (int i = 0; i < num; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}