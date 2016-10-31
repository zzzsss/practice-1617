class Solution {
public:
    bool isPowerOfFour(int num) {
        // ...
        int one = (num & 0x55555555);
        if(one != num)
            return false;
        one = (one>>16) + (one&0xffff);
        one = (one>>8) + (one&0xff);
        one = (one>>4) + (one&0xf);
        one = (one>>2) + (one&0x3);
        return one == 1;
    }
};