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
    ListNode* oddEvenList(ListNode* head) {
        // 161115, straightforward as it is ...
        if(!head)
            return NULL;
        ListNode* headOdd = new ListNode{0};
        ListNode* headEven = new ListNode{0};
        ListNode* curOrigin = head;
        vector<ListNode*> curHeads = {headOdd, headEven};
        int curIndex = 0;
        while(curOrigin){
            curHeads[curIndex]->next = new ListNode{curOrigin->val};
            curHeads[curIndex] = curHeads[curIndex]->next;
            curIndex = 1 - curIndex;
            curOrigin = curOrigin->next;
        }
        ListNode* headFinal = headOdd->next;
        curHeads[0]->next = headEven->next;
        return headFinal;
    }
};