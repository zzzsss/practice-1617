class Solution {
public:
    string parse_bracket(const string& s, int* ind){
        // parse from ind, s[ind] must be '[', and jump to next one after ']' (eat up [])
        *ind += 1;
        string one = parse_tillend(s, ind);
        if(*ind < s.size()) //skip ']'
            *ind += 1; 
        return one;
    }
    string parse_tillend(const string& s, int* ind){
        // scan until ']' or EOF (eat up number and plain char)
        string cur{""};
        while(1){
            if(*ind>=s.size() || s[*ind]==']')
                return cur;
            if(isdigit(s[*ind])){
                // if digit, eat it up
                int times = 0;
                while(isdigit(s[*ind])){
                    int num = static_cast<int>(s[*ind]-'0');
                    times = times*10+num;
                    *ind += 1;
                }
                string one = parse_bracket(s, ind);
                for(int i=0; i<times; i++)
                    cur += one;
            }
            else{
                cur += s[*ind];
                *ind += 1;
            }
        }
    }
    string decodeString(string s) {
		// 20min, one-time ac, recursive parsing, 160928-1113
        int n = 0;
        return parse_tillend(s, &n);
    }
};