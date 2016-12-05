class Solution {
public:
    bool isPowerOfThree(int n) {
        // see this one in discuss
        return ( n>0 &&  1162261467%n==0);
    }
};