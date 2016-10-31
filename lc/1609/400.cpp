class Solution {
public:
    int findNthDigit(int n) {
        // 10 mins, on 1st submit, 16-09-19:10-17
        // 5 mins, on 2nd submit, debug
        // 3 mins, on 3rd submit, debug
        int cur_num = 1;
        int cur_temp = 10;
        while(1){
            // it must have an end
            int cur_all = cur_temp - cur_temp/10;
            if(n/cur_num <= cur_all){   //fix3: overflow
                // ok, find the range
                int which_n = cur_temp/10 + (n-1)/cur_num;
                int which_d = (n-1)%cur_num+1;
                for(int i=0; i<cur_num-which_d; i++)
                    which_n /= 10;
                return which_n%10;
            }
            // next round
            n -= cur_all*cur_num;   //fix2: wrong-order
            cur_num ++;
            cur_temp *= 10;
        }
    }
};