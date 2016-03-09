/*************************************************************************
	> F
	> Author: dong xu
	> Mail: gwmxyd@163.com 
	> Created Time: 2016年03月08日 星期二 16时08分36秒
 ************************************************************************/
#include<stdio.h>
struct ListNode{
	int val;
	struct ListNode *next;
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* head,*tmp,*lt1,*lt2;
    int n = 0;
    lt1 = l1; 
    lt2 = l2; 
    if(l1 != NULL && l2 != NULL){
        head = (struct ListNode*)malloc(sizeof(struct ListNode));
        head->val = (l1->val + l2->val)%10;
        if((l1->val+l2->val)>=10)
            n=1;
            else n = 0;
        lt1 = l1->next;
        lt2 = l2->next;
        tmp = head;
    }
    while(lt1 != NULL && lt2 != NULL)
    {   
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = (lt1->val + lt2->val + n)%10;
        if((lt1->val + lt2->val + n) >= 10)
            n = 1;
        else
            n = 0;
        lt1 = lt1->next;
        lt2 = lt2->next;
    }
    while(lt1 != NULL){
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = (lt1->val + n)%10;
        if((lt1->val + n) >= 10)
            n = 1;
        else
            n = 0;
        lt1 = lt1->next;
    }
    while(lt2 != NULL){
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = (lt2->val + n)%10;
        if((lt2->val + n) >= 10)
            n = 1;
        else
            n = 0;
        lt2 = lt2->next;
    }
    if(n == 1){
        tmp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp = tmp->next;
        tmp->val = 1;
    }
    tmp->next = NULL;
    return head;
}
