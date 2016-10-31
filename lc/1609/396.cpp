class Solution {
public:
    int maxRotateFunction(const vector<int>& A) {
        // 35min, 160924-1048, bad-one second-order diffs
        // 5min, ok
        // basic calculations
        int N = A.size();
        int max_v = 0;
        int sum = 0;
        for(int i=0; i<N; i++){
            max_v += i*A[i];
            sum += A[i];
        }
        int cur_one = max_v;
        // rotate them, i as the last one
        for(int i=N-1; i>=0; i--){
            cur_one += (sum - A[i]*N);
            max_v = ((cur_one>max_v) ? cur_one : max_v);
        }
        return max_v;
    }
};