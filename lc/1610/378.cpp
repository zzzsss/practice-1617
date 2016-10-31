struct Elem{
        int value;
        int row;  // which row
    };
bool operator<(const Elem& a, const Elem& b){return a.value>b.value;}

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // 161007-1057 ignore column: k*log(n)
        int n = matrix.size();
        priority_queue<Elem> q;
        vector<int> next(n, 1);
        for(int i=0;i<n;i++)
            q.emplace(Elem{matrix[i][0],i});
        while(1){
            Elem one{q.top()};
            if(k==1)
                return one.value;
            k--;
            q.pop();
            if(next[one.row]<n){
                q.emplace(Elem{matrix[one.row][next[one.row]],one.row});
                next[one.row]++;
            }
        }
    }
};