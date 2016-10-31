/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    unordered_map<TreeNode*, int> values_rnot;
    unordered_map<TreeNode*, int> values_rok;
    int rob_r(TreeNode* root, bool root_ok){
        if(!root)
            return 0;
        unordered_map<TreeNode*, int>* values = &values_rnot;
        if(root_ok)
            values = &values_rok;
        if(values->find(root) != values->end())
            return (*values)[root];
        // 1. no root robbing
        int v = rob_r(root->left, true) + rob_r(root->right, true);
        // 2. root robbing
        if(root_ok){
            int vok = rob_r(root->left, false) + rob_r(root->right, false) + root->val;
            v = std::max(v, vok);
        }
        // record
        (*values)[root] = v;
        return v;
    }
public:
    int rob(TreeNode* root) {
        // 161030, dp
        return rob_r(root, true);
    }
};