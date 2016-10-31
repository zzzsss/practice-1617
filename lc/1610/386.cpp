class Solution {
public:
    void append_them(vector<int>& v, int base, int bound, int start){
        for(;start <= 9; start++){
            int one = base*10+start;
            if(one <= bound){
                v.push_back(one);
                append_them(v, one, bound, 0);
            }
            else
                break;
        }
    }
    vector<int> lexicalOrder(int n) {
        // 20min 161016, recursively generating them
        vector<int> v;
        append_them(v, 0, n, 1);
        return v;
    }
};