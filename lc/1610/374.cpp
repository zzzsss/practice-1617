// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        // 161015, binary search
        unsigned a1 = 1;
        unsigned a2 = n;
        while(true){
            unsigned g = (a1+a2)/2;
            int ans = guess(g);
            if(ans==1)
                a1 = g+1;
            else if(ans==-1)
                a2 = g-1;
            else
                return g;
        }
    }
};
