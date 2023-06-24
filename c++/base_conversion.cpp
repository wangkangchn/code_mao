/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: base_conversion.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 进制转换
时间	   	: 2023-06-16 20:46
***************************************************************/
#include <iostream>

int base(const std::string& s, int b)
{
    
    int res = 0;
    for(auto x : s)
    {   
        if (x <= '9') {
            res = res * b + x - '0';
        } else {
            res = res * b + std::tolower(x) - 'a' + 10;
        }
    }
    return res;
}

int main()
{
    std::cout << base("01A21ED", 16) << std::endl;
    return 0;
}