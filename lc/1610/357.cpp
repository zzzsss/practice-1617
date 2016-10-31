class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        // 161022, 
        if(n==0)
            return 1;
        if(n==1)
            return 10;
        int sum = 10;
        int m_digit = std::min(n, 10);
        for(int i=2; i<=m_digit; i++){
            int cur = 9;    // msd has 9 choices
            for(int j=1; j<i; j++)
                cur *= (10-j);
            sum += cur;
        }
        return sum;
    }
};