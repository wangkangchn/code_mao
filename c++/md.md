```
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
```

```
/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: table.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 循环比赛
时间	   	: 2023-06-08 21:42
***************************************************************/
#include <iostream>


/**
 *
 * @param [in]  left:    参与比赛的选手起始 ID, 左闭右闭
 * @param [in]  right:   参与比赛的选手结束 ID
 */
void create_table(int left, int right, int* table)
{
    int num = right - left + 1;     /* 人数 */
    if (num == 1) {
        return;
    }

    /* 只有两个人 */
    if (num == 2) {
        table[0] = left;     table[1] = right;
        table[2] = right;    table[3] = left;
        return;
    }

    int half_num = num / 2;
    int tmp[half_num * half_num];

    /* 拷贝左半部分 */
    create_table(left, left + half_num - 1, tmp);
    int i = 0;
    for (int r = 0; r < half_num; ++r) {            /* 行 */
        for (int c = 0; c < half_num; ++c) {
            table[r * num + c] = tmp[i];
            table[(r + half_num) * num + c + half_num] = tmp[i];
            ++i;
        }
    }

    /* 拷贝右半部分 */
    create_table(left + half_num, right, tmp);
    i = 0;
    for (int r = 0; r < half_num; ++r) {            /* 行 */
        for (int c = 0; c < half_num; ++c) {
            table[r * num + c + half_num] = tmp[i];
            table[(r + half_num) * num + c] = tmp[i];
            ++i;
        }
    }
}

void show_table(int* table, int row, int col)
{
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << table[i * row + j] << " ";
        }
        std::cout << std::endl;
    }
}


int main()
{   
    int M;
    std::cin >> M;

    int num = 1 << M;
    int table[num * num];
    create_table(1, num, table);

    /* 打印 */
    show_table(table, num, num);
    return 0;
}
```