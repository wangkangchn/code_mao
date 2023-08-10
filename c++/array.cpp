/***************************************************************
 * @copyright  Copyright © 2023 wkangk.
 * @file       array.cpp
 * @author     wkangk <wangkangchn@163.com>
 * @version    v1.0
 * @brief      
 * @date       2023-08-04 20:53
 **************************************************************/

#include <iostream>

int main()
{
    int num[2] = {0};
    for (int i = 0; i < 3; ++i) {
        std::cout << num[i] << std::endl;
    }

    std::cout << num << std::endl;
    std::cout << num + 1 << std::endl;

    return 0;
}