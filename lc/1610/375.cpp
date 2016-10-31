class Solution {
public:
    int n = 0;
    int* l;
    int get_amount(int a, int b){
        // a,b \in [1, n], return [0, n^2)
        if(a>=b)
            return 0;
        else{
            int index = (a-1)*n+(b-1);
            if(l[index]>=0)
                return l[index];
            else{   // need to calculate recursively
                int min = a + get_amount(a+1, b);
                for(int i=a+1; i<=b; i++){
                    int max = std::max(i+get_amount(a, i-1), i+get_amount(i+1, b));
                    min = std::min(min, max);
                }
                l[index] = min;
                return min;
            }
        }
    }
    int getMoneyAmount(int n) {
        // 161015, with the help of hints and discuss
        this->n = n;
        l = new int[n*n];
        for(int i=0; i<n*n; i++)
            l[i] = -1;
        return get_amount(1,n);
    }
};