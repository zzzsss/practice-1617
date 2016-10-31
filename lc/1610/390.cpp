class Solution {
public:
    int f(int n){
        // return possition
        switch(n){
        case 1: return 0;
        case 2: return 1;
        default:
            int t = f(n/2); // for both even and odd
            if(n%2 == 0)
                return n+1-2*(t+1);
            else
                return n-2*(t+1);
        }
    }
    int lastRemaining(int n) {
        // 161003-1001, 1st solution, just perform those: bug1(need reverse)
        // 161003-1024, recursive f(n)
        return f(n)+1;
    }
};