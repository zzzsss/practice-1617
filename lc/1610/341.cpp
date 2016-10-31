/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
    vector<const vector<NestedInteger>*> stack_list;
    vector<int> stack_index;    //next number
    
public:
    NestedIterator(const vector<NestedInteger> &nestedList) {
        const vector<NestedInteger>* cur = &nestedList;
        stack_list.push_back(cur);
        stack_index.push_back(0);
    }

    int next() {
        int x = stack_list.back()->at(stack_index.back()).getInteger();
        stack_index.back() ++;
        return x;
    }

    bool hasNext() {
        // travel to the next one that is Integer
        while(1){
            if(stack_list.empty())
                return false;
            const vector<NestedInteger>* one = stack_list.back();
            int one_index = stack_index.back();
            if(one_index >= one->size()){   // pop them
                stack_list.pop_back();
                stack_index.pop_back();
                if(!stack_index.empty())
                    stack_index.back() ++;
            }
            else if(one->at(one_index).isInteger())
                return true;
            else{   // push new vector
                stack_list.push_back(&one->at(one_index).getList());
                stack_index.push_back(0);
            }
        }
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */