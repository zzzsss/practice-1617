class Solution {
public:
    int get_it(unordered_map<int, int>& v, int num)
    {
        // if already ok
        if(v.find(num)!=v.end())
            return v[num];
        // find it
        int what = -1;
        if(num%2==0)
            what = get_it(v, num/2)+1;
        else{
            int s_minus = get_it(v, (num-1)/2)+2;
            int s_plus = get_it(v, (num-1)/2+1)+2;    // crazy of overflow
            what = ((s_minus>s_plus) ? s_plus : s_minus);
        }
        v[num] = what;
        return what;
    }
    
    int integerReplacement(int n) {
        // 10min, 1st submit, 160923-1025, dynamic programming
        unordered_map<int, int> steps;
        steps[1] = 0;
        return get_it(steps, n);
    }
};