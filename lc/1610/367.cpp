class Solution {
public:
    bool isPerfectSquare(int num) {
        // ...
        for(int i=0; i<=num; i++){
            int x = i*i;
            if(x<0 || x>num)
                return false;
            if(x==num)
                return true;
        }
        return false;
    }
};