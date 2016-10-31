class Solution {
public:
    int getSum(int a, int b) {
        // 161017, ...
        int bits = 8 * sizeof(int);
        bool carry = false;
        int final = 0;
        int mask = 1;
        for(int i=0;i<bits;i++){
            if((a&mask)^(b&mask)){  //0,1
                if(carry);
                else{
                    carry = false;
                    final |= mask;
                }
            }
            else if(a&b&mask){  // 1,1
                if(!carry);
                else
                    final |= mask;
                carry = true;
            }
            else{   // 0,0
                if(carry)
                    final |= mask;
                carry = false;
            }
            mask = (mask << 1);
        }
        return final;
    }
};