/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	/*
	 * 148
	 * Sort List
	 * Sort a linked list in O(n log n) time using constant space complexity.
	 *
	 * 快慢指针，归并排序
	 */
    ListNode *sortList(ListNode *head){
        if(!head || !head->next)
            return head;
        
        ListNode *p = head, *q = head->next;
        while(q && q->next){
            p = p->next;
            q = q->next->next;
        }
             
        ListNode *left = sortList(p->next);
        p->next = NULL;
        ListNode *right = sortList(head);

        return merge(left,right);
    }
    ListNode *merge(ListNode *left, ListNode *right){
        ListNode dumy(0);
        ListNode *p = &dumy;
        while(left && right){
            if(left->val < right->val){
                p->next = left;
                left = left->next;
            }else{
                p->next = right;
                right = right->next;
            }
            p = p->next;
        }
        if(left)
            p->next = left;
        if(right)
            p->next = right;
        return dumy.next;
    }
};