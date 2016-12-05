class Solution {
private:
    int sum_ok(int x, long lower, long upper){
        return (x>=lower && x<=upper) ? 1 : 0;
    }
    int count_partial(const vector<int>& nums, int a, int b, long lower, long upper){
        // count in the partial vector [a,b]
        if(a==b){
            // end of recursion
            return (sum_ok(nums[a], lower, upper));
        }
        else{
            // partition: a, ..., m | m+1, ... , b
            int count = 0;
            int m = (a+b)/2;
            count += count_partial(nums,a,m,lower,upper) + count_partial(nums,m+1,b,lower,upper);
            // get the ranges of the right part
            multimap<long, int> ranges;
            for(int i=m+1, s=0; i<=b; i++){
                s += nums[i];
                ranges.insert({s, 0});
            }
            {
                // set ranking of the nodes
                int i=0;
                for(auto iter=ranges.begin(); iter!=ranges.end(); iter++)
                    iter->second = i++;
            }
            // search for the left part
            for(int i=m, s=0; i>=a; i--){
                s += nums[i];
                auto r1 = ranges.lower_bound(lower-s);
                auto r2 = ranges.upper_bound(upper-s);
                if(r1 != ranges.end()){
                    if(r2 != ranges.end())
                        count += (r2->second - r1->second);
                    else
                        count += (ranges.size() - r1->second);
                }
            }
            return count;
        }
    }
public:
    int countRangeSum(const vector<int>& nums, int lower, int upper) {
        // 161116, nlognlogn, divide and conquer
        if(nums.empty())
            return 0;
        return count_partial(nums, 0, nums.size()-1, lower, upper);
    }
};