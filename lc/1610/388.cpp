class Solution {
public:
    int lengthLongestPath(string input) {
        // 161003-1045, straight-forward
        vector<int> prefix(1000, 0);
        int max_len = 0;
        auto iter = input.begin();
        while(1){
            // eat up to one-line
            int one_len = 0;
            int level = 0;
            bool ext = false;
            while(iter != input.end() && *iter != '\n'){
                if(*iter == '\t')
                    level ++;
                else{
                    if(*iter == '.')
                        ext = true;
                    one_len ++;
                }
                iter ++;
            }
            // get one
            if(ext){    //file
                int this_len = prefix[level] + one_len;
                if(this_len > max_len)
                    max_len = this_len;
            }
            else{       //dir
                prefix[level+1] = prefix[level] + one_len + 1;
            }
            // break
            if(iter == input.end())
                break;
            else
                iter ++;
        }
        return max_len;
    }
};