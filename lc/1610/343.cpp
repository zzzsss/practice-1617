class Solution {
public:
    int integerBreak(int n) {
        // 161027, dp
        vector<int> values(n+1, 1);
        values[1] = values[2] = 1;
        for(int i=3; i<=n; i++){
            for(int step=1; step<i; step++){
                values[i] = std::max(values[i], step*(i-step));
                values[i] = std::max(values[i], values[step]*(i-step));
                values[i] = std::max(values[i], step*values[i-step]);
                values[i] = std::max(values[i], values[step]*values[i-step]);
            }
        }
        return values[n];
    }
};