/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    NestedInteger parse(string& s, int* i){
        // scan from s[i], return the parsed expression, may change i
        // -- no checking, assuming well-formed
        if(s[*i]=='['){
            (*i)++;
            NestedInteger ret;
            if(s[*i]==']'){
                (*i) ++;
                return ret; // return empty one
            }
            while(1){
                NestedInteger one = parse(s, i);
                ret.add(one);
                if(s[*i]==',')
                    (*i)++;
                else if(s[*i]==']'){
                    (*i)++;
                    break;
                }
            }
            return ret;
        }
        else{    // a number
            int num = 0;
            bool minus = false;
            if(s[*i]=='-'){
                (*i)++;
                minus = true;
            }
            while(isdigit(s[*i])){
                num = num*10 + (s[*i]-'0');
                (*i)++;
            }
            if(minus)
                num = 0 - num;
            return NestedInteger(num);
        }
    }
    NestedInteger deserialize(string s) {
        // 20min, 161004, ...
        int i=0;
        return parse(s, &i);
    }
};