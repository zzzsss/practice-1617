class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        // 161108
        if(x.size() < 4)
            return false;
        const int HSIT_SIZE = 6;
        vector<int> history{-10000, -10000, x[0], x[1], x[2], x[3]};
        int index = 4;
        while(1){
            // check 4
            if(history[2]>=history[4] && history[5]>=history[3])
                return true;
            // check 5
            if(history[2]==history[4] && (history[5]+history[1])>=history[3])
                return true;
            // check 6
            if(history[3]>history[1] && (history[5]+history[1])>=history[3] &&
                    history[2]>history[4] && (history[0]+history[4])>=history[2])
                return true;
            // new one
            for(int i=0; i<HSIT_SIZE-1; i++)
                history[i] = history[i+1];
            if(index >= x.size())
                break;
            history[HSIT_SIZE-1] = x[index];
            index++;
        }
        return false;
    }
};