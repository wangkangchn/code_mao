/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: list.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 单向链表的简易实现
    https://github.com/wangkangchn/code_mao.git
时间	   	: 2023-07-17 21:40
***************************************************************/
#include <iostream>

struct list_node
{
    int value{0};          /* 当前节点保存的值 */
    list_node* next{nullptr};    /* 当前节点的下一节点, 最后一个节点的 next 指针指向 nullptr */
};

struct list
{
    int count{0};          /* 链表中元素数目 */
    list_node* head{nullptr};    /* 链表的头指针 */
};


/**
 *     将一个数值插入到 list 中
 *  这里选择头插法
 *
 * @param [in]  li      待插入链表
 * @param [in]  value   待插入的值
 * @return     无
 */
void push(list* li, int value)
{
    /* 1. 每次插入新值都需要先申请一个新节点 */
    list_node* new_node = new list_node;
    new_node->value = value;            /* 保存要储存的值 */

    /* 2. 调整指针将新节点加入到链表中 */
    new_node->next = li->head;
    li->head = new_node;
    ++li->count;
}

/**
 *     找到某一节点进行删除, 存在多个时, 只删除第一个
 *
 * @param [in]  li      待操作链表
 * @param [in]  value   待删除值
 * @return     无
 */
void pop(list* li, int value)
{
    /* 链表不支持随机存储, 所以在链表中找一个元素, 需要遍历完整个链表 */
    list_node* prev = li->head;
    if (prev == nullptr) {   /* 空链表 */
        return;
    }

    list_node* tmp = prev->next;    /* tmp 为当前要判断的节点, prev 为当前节点的前一个节点 */

    while (tmp != nullptr) {    /* 最后一个节点的 next 指向 nullptr */
        if (tmp->value == value) {
            /* 找到了, 调整指针将其删除 */
            prev->next = tmp->next;     /* 前一节点的 next 指向后一节点 */
            delete tmp;         /* 删除节点, 这里有个问题是, 可以先删除再调整吗? */
            tmp = prev->next;
            --li->count;
        } else {
            /* 没有找到继续遍历 */
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

/**
 *     显示整个链表
 *
 * @param [in]  li      待操作链表
 * @return     无
 */
void show(list* li)
{
    list_node* tmp = li->head;

    while (tmp != nullptr) {
        std::cout << tmp->value << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

/**
 *     清空整个链表
 *
 * @param [in]  li      待操作链表
 * @return     无
 */
void clear(list* li)
{
    list_node* head = li->head;

    while (head != nullptr) {
        list_node* tmp = head;  /* 这里为什么要保存一下 */
        head = head->next;
        delete tmp;
        --li->count;
    }
    li->head = nullptr;         /* 赋空, 以表示链表结束, 一定要记得对指针初始化或清空!!! */
}


int main()
{
    list my_list;

    for (int i = 0; i < 10; ++i) {
        push(&my_list, i);
    }
    std::cout << "初始 my_list 节点个数为: " << my_list.count << std::endl;  
    std::cout << "初始 my_list 内值为: ";
    show(&my_list); 


    pop(&my_list, 2);
    pop(&my_list, 4);
    pop(&my_list, 6);
    pop(&my_list, 8);
    std::cout << "删除偶数后, my_list 内节点个数为: " << my_list.count << std::endl;  
    std::cout << "my_list 内值为: ";
    show(&my_list); 


    clear(&my_list);
    std::cout << "清空后 my_list 个数为: " << my_list.count << std::endl;  
    std::cout << "my_list 内值为: ";
    show(&my_list); 
    return 0;
}