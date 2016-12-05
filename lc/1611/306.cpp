class Solution {
public:
    bool isAdditiveNumber(string num) {
        // 161126, 
        int size = num.size();
        if(size <= 2)
            return false;
        // first calculate the values
        vector<vector<int>> values(size, vector<int>(size, -1));
        for(int step=0; step<size; step++){
            for(int i=0; i<size-step; i++){
                int j = i+step;
                if(i==j)
                    values[i][j] = num[i]-'0';
                else if(values[i][i]>0)
                    values[i][j] = values[i][j-1]*10 + values[j][j];
            }
        }
        // calculate them
        int num1Val = 0;
        for(int num1End=0; num1End<=size/2; num1End++){
            int n1V = values[0][num1End];
            if(n1V<0)
                break;
            for(int num2End=num1End+1; num2End<size-1; num2End++){
                int n1 = n1V;
                int n2 = values[num1End+1][num2End];
                if(n2<0)
                    break;
                // loop it
                int n1Size = num1End+1;
                int n2Size = num2End-num1End;
                int n1End = num1End;
                int n2End = num2End;
                while(1){
                    int n3 = n1+n2;
                    int n3Size = std::max(n1Size, n2Size);
                    int n3End = n2End + n3Size;
                    if(n3End>=size || n3!=values[n2End+1][n3End]){
                        n3Size++;
                        n3End++;
                        if(n3End>=size || n3!=values[n2End+1][n3End]){
                            break;
                        }
                    }
                    if(n3End == size-1)
                        return true;
                    else{
                        n1 = n2;
                        n1End = n2End;
                        n1Size = n2Size;
                        n2 = n3;
                        n2End = n3End;
                        n2Size = n3Size;
                    }
                }
            }
        }
        return false;
    }
};