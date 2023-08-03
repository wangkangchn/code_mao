/***************************************************************
 * @copyright  Copyright © 2023 wkangk.
 * @file       8_queue.cpp
 * @author     wkangk <wangkangchn@163.com>
 * @version    v1.0
 * @brief      八皇后问题
 * @date       2023-08-03 20:24
 **************************************************************/
#include <iostream>
#include <stack>
#include <vector>


struct Position
{
    int x;
    int y;
};


/**
 *     检查皇后 2 会不会被皇后 1 攻击
 *
 * @return     会被攻击 false, 不会被攻击 true
 */
bool check(Position queue1, Position queue2)
{
    /* 1. 判断是否同行 */
    if (queue1.y == queue2.y) {
        return false;
    }

    /* 2. 判断是否同列 */
    if (queue1.x == queue2.x) {
        return false;
    }

    /* 3. 判断是否在主对角线上 k = 1 */
    int k = 1;
    int b = queue1.y - k * queue1.x;
    if ((k * queue2.x + b - queue2.y) == 0) {
        return false;
    }

    /* 4. 判断是否在副对角线上 k = -1 */
    k = -1;
    b = queue1.y - k * queue1.x;
    if ((k * queue2.x + b - queue2.y) == 0) {
        return false;
    }

    return true;
}

/**
 *  检查当前皇后是否和所有之前皇后冲突     
 */
bool check_all(const std::vector<Position>& queue_all, Position queue)
{
    for (int i = 0; i < queue_all.size(); ++i) {
        if (!check(queue_all[i], queue)) {      /* 只要会被一个攻击就返回 false */
            return false;
        }
    }
    return true;
}


/**
 *     
 *
 * @param [in]  n       确定第 n 行的皇后位置
 * @param [in]  queues  已有皇后的位置
 */
std::vector<Position> compute()
{
    std::vector<Position> queue_ok;      /* 以确认好的皇后位置 */
    std::vector<std::vector<bool>> table;           /* 标记是否搜索过 */
    for (size_t i = 0; i < 8; ++i) {
        table.emplace_back( std::vector<bool>(8, false) );
    }

    /* 第一个皇后的位置 */
    Position pos;
    pos.x = 1;
    pos.y = 0;
    queue_ok.push_back(pos);
    table[pos.y][pos.x] = true;

    while (queue_ok.size() < 8) {
        /* 先找到上一个皇后的位置, 由上一个皇后位置确定下一皇后的 y 坐标 */
        Position& last_q = queue_ok.back();
        
        Position current_q;
        current_q.y = last_q.y + 1;         /* 我们一行一行的确定皇后 */

        int x = 0;
        for (x = 0; x < 8; ++x) {       /* 每列确定皇后位置是否可行 */
            current_q.x = x;

            if (table[current_q.y][current_q.x] || !check_all(queue_ok, current_q)) {    /* 当前皇后被之前的皇后攻击, 退出 */
                continue;
            }

            queue_ok.push_back(current_q);
            table[current_q.y][current_q.x] = true;
            break;
        }

        /* 当前皇后没有地方安放了 */
        if (x >= 8) {
            for (int x = 0; x < 8; ++x) {
                table[current_q.y][x] = false;
            }

            table[last_q.y][last_q.x] = true;       /* 上一个皇后, 下一次就会变为当前皇后, 所以这里要记录它不能走的位置 */
            queue_ok.pop_back();
        }
    }
    return queue_ok;
}


int main()
{
    auto queues = compute();
    std::cout << queues.size() << std::endl;
    for (auto& q : queues) {
        std::cout << q.x << ", " << q.y << std::endl;
    }
    return 0;
}

/* 

0, 0
4, 1
7, 2
5, 3
2, 4
6, 5
1, 6
3, 7


1, 0
3, 1
5, 2
7, 3
2, 4
0, 5
6, 6
4, 7
 */