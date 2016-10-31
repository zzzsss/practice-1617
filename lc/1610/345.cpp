class Solution {
public:
    string reverseVowels(string s) {
        // 161027, ...
        bool is_vowel[128] = {false, };
        is_vowel['a'] = is_vowel['i'] = is_vowel['u'] = is_vowel['e'] = is_vowel['o'] = true;
        is_vowel['A'] = is_vowel['I'] = is_vowel['U'] = is_vowel['E'] = is_vowel['O'] = true;
        string those;
        for(char x: s)
            if(is_vowel[x])
                those += x;
        string ret;
        for(char x: s){
            if(is_vowel[x]){
                ret += those.back();
                those.pop_back();
            }
            else
                ret += x;
        }
        return ret;
    }
};