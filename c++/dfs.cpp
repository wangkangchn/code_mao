/***************************************************************
 * @copyright  Copyright © 2023 wkangk.
 * @file       dfs.cpp
 * @author     wkangk <wangkangchn@163.com>
 * @version    v1.0
 * @brief      深度优先搜索练习题
 * @date       2023-08-10 20:19
 **************************************************************/
#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;
int n;
int a[1000];
int count = 0;

/**
 *     数的拆分 
 *  https://www.cnblogs.com/chen-kaige/p/14590424.html
 * 
 * @param [in]  x 表示当前要确定的位置
 * @param [in]  u 标识当前剩余的数, 就是 n 减去前一个位置的数剩下的数
 */
int dfs1(int x, int u) 
{   
    /* u == 0 表示已经没有数可减了, 意味着和为 n
    x > 2 意味着有超过两个数相加, 满足条件, x 从 1 开始记为有效位 */
    if( (u == 0) && (x > 2) ) {
        /* 将之前记录的结果全部输出 */
        std::cout << n << " = ";
        for(int i = 1; i < x; ++i) {
            std::cout << a[i];
            if (i < (x - 1)) {
                std::cout << " + ";
            }
        }
        std::cout << "\n";
        return 1;
    }

    /* u 是当前可选数据范围, 上界不会超过 u */
    for (int i = 1; i <= u; ++i) {
        /* 为何加上下面这个条件就可以防止重复输出??? 
        如果不加这个条件, 当第一次位置遍历到 6 时, 每次都会从 1 开始尝试,
        这样就会找到 6 1 和 1 6 是一致的, 但是我们想要的仅仅是 1 6 是一个递增序列
        */
        if (i >= a[x - 1]) {       
            a[x] = i;//数组中x的位置为i
            u -= i;//剩余的数减去i
            
            count += dfs1(x + 1, u);
            
            // 回溯, 寻找当前位的下一个数据
            a[x] = 0;
            u += i;
        } 
    }

    return 0;
}

/**
 *     数的划分 
 * 
 * @param [in]  x 表示当前要确定的位置
 * @param [in]  u 标识当前剩余的数, 就是 n 减去前一个位置的数剩下的数
 * @param [in]  k 要划分的份数
 */
int dfs2(int x, int u, int k) 
{   
    /* u == 0 表示已经没有数可减了, 意味着和为 n
    x > 2 意味着有超过两个数相加, 满足条件, x 从 1 开始记为有效位 */
    if( (u == 0) && (x == (k + 1)) ) {
        /* 将之前记录的结果全部输出 */
        std::cout << n << " = (";
        for(int i = 1; i < x; ++i) {
            std::cout << a[i];
            if (i < (x - 1)) {
                std::cout << ", ";
            }
        }
        std::cout << ")\n";
        return 1;
    }

    /* u 是当前可选数据范围, 上界不会超过 u */
    for (int i = 1; i <= u; ++i) {
        /* 为何加上下面这个条件就可以防止重复输出??? 
        如果不加这个条件, 当第一次位置遍历到 6 时, 每次都会从 1 开始尝试,
        这样就会找到 6 1 和 1 6 是一致的, 但是我们想要的仅仅是 1 6 是一个递增序列
        */
        if (i >= a[x - 1]) {       
            a[x] = i;//数组中x的位置为i
            u -= i;//剩余的数减去i
            
            count += dfs2(x + 1, u, k);
            
            // 回溯, 寻找当前位的下一个数据
            a[x] = 0;
            u += i;
        } 
    }

    return 0;
}

/**
 *  全排列问题    
 *
 * @param [in]      x 当前要存的位数
 * @return     无
 */
int dfs3(int x) 
{   
    /* u == 0 表示已经没有数可减了, 意味着和为 n
    x > 2 意味着有超过两个数相加, 满足条件, x 从 1 开始记为有效位 */
    if (x == n + 1) {
        /* 将之前记录的结果全部输出 */
        std::cout << "(";
        for(int i = 1; i < x; ++i) {
            std::cout << a[i];
            if (i < (x - 1)) {
                std::cout << ", ";
            }
        }
        std::cout << ")\n";
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        bool ok = true; /* 标记是否和之前重复 */
        for (int j = 1; j < x; ++j) {
            if (i == a[j]) {            /* 不重复才接受 */
                ok = false;
                break;
            }
        }

        if (ok) {
            a[x] = i;//数组中x的位置为i
            
            count += dfs3(x + 1);
            
            // 回溯, 寻找当前位的下一个数据
            a[x] = 0;
        }
    }

    return 0;
}


char ch[100000] = {0}, res[100000] = {0};
int b[256] = {0}, len = 0;

/**
 *     有重复的全排列
 *
 * @param [in]  x   当前待排序的位数
 * @return     无
 */
void dfs4(int x)
{
    if (x >= n) {   /* 已经满足了位数 */
        std::cout << res << std::endl;
        ++count;
        return;
    }

    for (int i = 1; i <= len; ++i) {
        if (b[ch[i]] != 0) { /* 相同字符, 仅能使用有限次数 */
            b[ch[i]]--;
            res[x] = ch[i];
            dfs4(x + 1);
            
            /* 回溯 */
            b[ch[i]]++;
        }
    }
}



int S[100000] = {0};

/**
 *     子集和问题 
 * 
 * @param [in]  x 表示当前要确定的位置
 * @param [in]  u 标识当前剩余的数, 就是 n 减去前一个位置的数剩下的数
 */
void dfs5(int x, int u)
{
    if (u == 0) {   /* 已经满足了位数 */
        std::cout << "(";
        for(int i = 0; i < x; ++i) {
            std::cout << a[i];
            if (i < (x - 1)) {
                std::cout << ", ";
            }
        }
        std::cout << ")\n";
        return;
    } else if ( u < 0 ) {
        return;
    }

    for (int i = 1; i <= len; ++i) {
        if (b[S[i]] != 0) { /* 相同字符, 仅能使用有限次数 */
            b[S[i]]--;
            a[x] = S[i];
            u -= S[i];
            dfs5(x + 1, u);
            
            /* 回溯 */
            b[S[i]]++;
            u += S[i];
        }
    }
}





int main()
{
    /* 数的拆分 */
    // while (cin >> n) {
    //     a[0] = 1;//算式中第一个数是1 
    //     count = 0;
    //     dfs1(1, n);
    //     std::cout << "total = " << count << std::endl;
    // }

    /* 数的划分 */
    // while (true) {
    //     int  k;
    //     cin >> n >> k;
    //     a[0] = 1;//算式中第一个数是1 
    //     count = 0;
    //     dfs2(1, n, k);
    //     std::cout << "total = " << count << std::endl;
    // }

    /* 全排列 */
    // while (cin >> n) {
    //     a[0] = 1;//算式中第一个数是1 
    //     count = 0;
    //     dfs3(1);
    //     std::cout << "total = " << count << std::endl;
    // }

    /* 带重复字符的排列 */
    // while (true) {
    //     char s[100];
    //     cin >> n;
    //     cin >> s;
    //     /* 统计次数 */
    //     for (int i = 0; i < strlen(s); ++i) {
    //         if (b[s[i]] == 0) {         /* ooo 这里做去重, 只留不重复的字符 */
    //             ch[++len] = s[i];
    //         }
    //         b[s[i]]++;          /* 用 ascii 码做键, 另类散列表 */
    //     }

    //     dfs4(0);
    // }

    /* 子集和问题 */
    while (true) {
        int s[100];
        int u;      /* 和 */
        cin >> n >> u;
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }

        /* 统计次数 */
        len = 0;
        for (int i = 0; i < n; ++i) {
            if (b[s[i]] == 0) {         /* ooo 这里做去重, 只留不重复的字符 */
                S[++len] = s[i];
            }
            b[s[i]]++;          /* 用 ascii 码做键, 另类散列表 */
        }

        dfs5(0, u);
    }

    return 0;
}
