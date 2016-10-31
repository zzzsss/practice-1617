/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    int num{0};
    ListNode* h;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        num = 0;
        h = head;
        while(head != nullptr){
            num ++;
            head = head->next;
        }
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        // 161005, no checking, again prob = 1/n
        auto iter = h;
        int n = num;
        while(rand()%n != 0){
            iter = iter->next;
            n--;
        }
        return iter->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */