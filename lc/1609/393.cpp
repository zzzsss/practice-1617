class Solution {
public:
    int check_head(unsigned char x){
        if((x&0x80) == 0x00)
            return 1;
        if((x&0xE0) == 0xC0)
            return 2;
        if((x&0xF0) == 0xE0)
            return 3;
        if((x&0xF8) == 0xF0)
            return 4;
        return -1;
    }
    int check_rest(unsigned char x){
        if((x&0xC0) == 0x80)
            return 0;
        return -1;
    }
    bool validUtf8(const vector<int>& data) {
        // ?, 160929-1033, check them by hand
        // 7min, 160929-1041, two bugs
        int index = 0;
        while(index < data.size()){
            // decode them
            unsigned char cur = data[index];
            int n = check_head(cur);
            if(n<0 || (index+n>data.size()))
                return false;
            // check the rest
            for(int i=1; i<n; i++){
                unsigned char cur = data[index+i];
                if(check_rest(cur)<0)
                    return false;
            }
            index += n;
        }
        return true;
    }
};