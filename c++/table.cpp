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