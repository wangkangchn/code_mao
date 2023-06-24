/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: high_precision_operation.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 高精度计算
时间	   	: 2023-06-22 20:50
***************************************************************/
#include <iostream>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>


void add(int a[], int num_a, int b[], int num_b, int c[], int& num_c)
{
    int min_len = 0;
    int max_len = 0;
    int* min_num = nullptr;
    int* max_num = nullptr;

    /* 先找到短的长度 */
    if (num_a <= num_b) {
        min_len = num_a;    min_num = a;
        max_len = num_b;    max_num = b;
    } else {
        min_len = num_b;    min_num = b;
        max_len = num_a;    max_num = a;
    }

    /* 结果总长度 */
    num_c = max_len;

    for (int i = 0; i < min_len; ++i) {
        int sum = min_num[i] + max_num[i] + c[i];
        if (sum >= 10) {
            c[i] = sum - 10;
            c[i + 1] += 1;
        } else {
            c[i] = sum;
        }
    }

    /* 长度长的数字剩余部分保留下来 */
    for (int i = min_len; i < max_len; ++i) {
        int sum = max_num[i] + c[i];
        if (sum >= 10) {
            c[i] = sum - 10;
            c[i + 1] += 1; 
            
            if (i == min_len - 1) {
                num_c += 1;
            }
        } else {
            c[i] = sum;
        }
    }

    /* 反转结果 */
    for (int i = 0; i < num_c / 2; ++i) {
        std::swap(c[i], c[num_c - 1 - i]);
    }
}

void multiplication(int a[], int num_a, int b[], int num_b, int c[], int& num_c)
{
    int min_len = 0;
    int max_len = 0;
    int* min_num = nullptr;
    int* max_num = nullptr;

    /* 先找到短的长度 */
    if (num_a <= num_b) {
        min_len = num_a;    min_num = a;
        max_len = num_b;    max_num = b;
    } else {
        min_len = num_b;    min_num = b;
        max_len = num_a;    max_num = a;
    }

    /* 结果总长度 */
    num_c = 1;

    for (int i = 0; i < min_len; ++i) {
        int v = min_num[i];

        for (int j = 0; j < max_len; ++j) {
            int res = v * max_num[j] + c[i + j];

            c[i + j] = res % 10; 
            c[i + j + 1] += res / 10; 

            num_c = i + j + 1;
            if (c[i + j + 1]) {
                num_c += 1;
            }
        }
    }

    /* 反转结果 */
    for (int i = 0; i < num_c / 2; ++i) {
        std::swap(c[i], c[num_c - 1 - i]);
    }
}

void factorial(int n, int b[], int& num_b)
{
    if (n == 0 || n == 1) {
        b[0] = 1;
        num_b = 1;
        return;
    }

    int tmp[4096] = { 0 };

    factorial(n - 1, tmp, num_b);

    /* 反转结果, 满足乘法的输入要求 */
    for (int i = 0; i < num_b / 2; ++i) {
        std::swap(tmp[i], tmp[num_b - 1 - i]);
    }

    int a[4] = {0};
    int num_a = 1;
    for (int i = 0; i < 4; ++i) {
        int v = (int)std::pow(10, i + 1);
        a[i] = n % v;
        n /= v;
        if (n == 0) {
            num_a = i + 1;
            break;
        }
    }

    multiplication(a, num_a, tmp, num_b, b, num_b);
}


/* 
    c = a - b

    a 要大于 b
 */
void subtraction(int a_[], int num_a, int b[], int num_b, int c[], int& num_c)
{
    int a[num_a] = {0};
    memcpy(a, a_, num_a * sizeof(int));

    num_c = num_a;
    for (int i = 0; i < num_b; ++i) {
        if (a[i] < b[i]) {
            a[i] += 10;
            a[i + 1] -= 1;
        }
        c[i] = a[i] - b[i];
    }

    for (int i = num_b; i < num_a; ++i) {
        c[i] = a[i];
    }

    if (c[num_a - 1] == 0) {
        num_c -= 1;
    }
}

/* 高精度 / 低精度 */
/**
 *     
 *
 * @param [in]  a:          被除数, 倒序输入
 * @param [in]  num_a:      被除数长度
 * @param [in]  b:          除数
 * @param [in out]  q:      商
 * @param [in out]  num_q:  商的长度
 * @param [in out]  r:      余数
 * @param [in out]  num_r:  余数的长度
 */
void division(int a[], int num_a, int b, int q[], int& num_q, int& r)
{   
    num_q = 0;
    r = 0;
    for (int i = num_a - 1; i >= 0; --i) {
        int x = r * 10 + a[i];
        int v = x / b;
        r = x % b;

        if (v == 0 && num_q == 0) {
            continue;
        }
        q[num_q++] = v;
    }
}


/**
 *     判断 a 是否大于等于 b
 * @param a:    倒序排序
 * @param b:    倒序排序
 */
bool gt(int a[], int num_a, int b[], int num_b)
{
    if (num_a > num_b) {
        return true;
    } else if (num_a < num_b) {
        return false;
    } else {
        for (int i = num_a - 1; i >= 0; --i) {
            if (a[i] > b[i]) {
                return true;
            } else if (a[i] < b[i]) {
                return false;
            }
        }
    }

    return  true;
}


/* 高精 / 高精 */
/**
 *     高精度除法, 要求被除数远大于除数
 *
 * @param [in]  a:      被除数  (倒序存储)
 * @param [in]  num_a:  被除数长度
 * @param [in]  b:      除数    (倒序存储)
 * @param [in]  num_b:  除数长度
 * @param [out] q:      商
 * @param [out] num_q:  商的长度
 * @param [out] r:      余数
 * @param [out] num_r:  余数的长度
 */
void division(int a[], int num_a, 
              int b[], int num_b, 
              int q[], int& num_q, 
              int r[], int& num_r)
{   
    num_r = 0;
    for (int i = num_a - num_b + 1; i < num_a; ++i) {
        r[num_r++] = a[i];
    }
    
    for (int i = num_a - num_b; i >= 0; --i) {
        /* 将新数字加到 r 的前段 */
        for (int j = num_r; j >= 1; --j) {
            r[j] = r[j - 1];
        }
        r[0] = a[i];
        ++num_r;


        auto sd = gt(r, num_r, b, num_b);
        if (!sd) {           /* 除数大于等于余数了, 这一位就可以结束了 */
            q[num_q++] = 0;
            continue;
        }

        for (int j = 0; j < 10; ++j) {
            int res[num_b] = {0};
            int num_res = 0;

            subtraction(r, num_r, b, num_b, res, num_res);

            memset(r, 0, num_r);
            memcpy(r, res, num_res * sizeof(int));  /* 将结果拷贝到余数中 */
            num_r = num_res;



            sd = gt(b, num_b, res, num_res);
            if (sd) {           /* 除数大于等于余数了, 这一位就可以结束了 */
                q[num_q++] = j + 1;
                break;
            } else {   /* 余数大于除数, 继续向下减 */
            } 
        }
    }
}

int main()
{
    std::cout << "INT_MIN: " << INT_MIN << std::endl;
    std::cout << "INT_MAX: " << INT_MAX << std::endl;
    std::cout << "LONG_MIN: " << LONG_MIN << std::endl;
    std::cout << "LONG_MAX: " << LONG_MAX << std::endl;
    std::cout << "FLT_MIN: " << FLT_MIN  << std::endl;
    std::cout << "FLT_MAX: " << FLT_MAX  << std::endl;
    std::cout << "DBL_MIN: " << DBL_MIN  << std::endl;
    std::cout << "DBL_MAX: " << DBL_MAX  << std::endl;

    const int LENGTH = 10000;
    int a[LENGTH] = {0};
    int b[LENGTH] = {0};
    int c[LENGTH] = {0};

    char aa[LENGTH] = {0};
    std::cin >> aa;
    int l_a = strlen(aa);
    for (int i = 0; i < l_a; ++i) {
        a[l_a - 1 - i] = aa[i] - '0';
    }

    char bb[LENGTH] = {0};
    std::cin >> bb;
    int l_b = strlen(bb);
    for (int i = 0; i < l_b; ++i) {
        b[l_b - 1 - i] = bb[i] - '0';
    }

    int c_length = 0;

    add(a, l_a, b, l_b, c, c_length);

    std::cout << "add 结果: ";
    for (int i = 0; i < c_length; ++i) {
        std::cout << c[i];
    }
    std::cout << std::endl;
    
    memset(c, 0x00, LENGTH);
    multiplication(a, l_a, b, l_b, c, c_length);

    std::cout << "multiplication 结果: ";
    for (int i = 0; i < c_length; ++i) {
        std::cout << c[i];
    }
    std::cout << std::endl;


    memset(c, 0x00, LENGTH);
    int v = 100;
    factorial(v, c, c_length);
    std::cout << "c_length: " << c_length << std::endl;
    std::cout << v << " 的阶乘结果: ";
    for (int i = 0; i < c_length; ++i) {
        std::cout << c[i];
    }
    std::cout << std::endl;


    memset(c, 0x00, LENGTH);
    subtraction(a, l_a, b, l_b, c, c_length);

    /* 反转结果, */
    for (int i = 0; i < c_length / 2; ++i) {
        std::swap(c[i], c[c_length - 1 - i]);
    }

    std::cout << "subtraction 结果: ";
    for (int i = 0; i < c_length; ++i) {
        std::cout << c[i];
    }
    std::cout << std::endl;


    /* 除法 */
    for (int k = 2; k < 22; ++k) {
        memset(c, 0x00, LENGTH);
        int r = 0;

        division(a, l_a, k, c, c_length, r);
        std::cout << "division / " << k << " 结果: ";
        std::cout << "商: ";
        for (int i = 0; i < c_length; ++i) {
            std::cout << c[i];
        }
        std::cout << std::endl;
        std::cout << "余数: " << r << std::endl;
    }

    std::cout << "高精 / 高精: \n";

    int q[LENGTH] = {0};
    int r[LENGTH] = {0};
    int num_q = 0, num_r = 0;
    division(a, l_a, b, l_b,
             q, num_q, 
             r, num_r);

    std::cout << "商: ";
    for (int i = 0; i < num_q; ++i) {
        std::cout << q[i];
    }
    std::cout << std::endl;

    std::cout << "余数: ";
    for (int i = 0; i < num_r / 2; ++i) {
        std::swap(r[i], r[num_r - 1 - i]);
    }

    for (int i = 0; i < num_r; ++i) {
        std::cout << r[i];
    }
    std::cout << std::endl;
    return 0;
}