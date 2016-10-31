class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        // 161021, exceed memory with whole size*size vector
        // 161021, smaller one, time exceed
        // 161021, ..., forget: finding longest sum ...
        // prepare firstly
        int rows = matrix.size();
        int columns = matrix[0].size();
        vector<vector<vector<int>>> area(rows, vector<vector<int>>(columns, vector<int>(columns, 0)));  // r*c*c
        int max_one = INT_MIN;
        // prepare area
        for(int r = 0; r < rows; r++){
            for(int sta = 0; sta < columns; sta++){
                int acc = 0;
                for(int end = sta; end < columns; end++){
                    acc += matrix[r][end];
                    area[r][sta][end] = acc;
                }
            }
        }
        // scan them all
        for(int c_start = 0; c_start < columns; c_start++){
            for(int c_end = c_start; c_end < columns; c_end++){
                // now dimension is one
                // ------------------ this is from discuss place --------------
                set<int> cumset;
                cumset.insert(0);
                int best=INT_MIN,cum=0;
                for(int i=0;i<rows;i++)
                {
                    cum+=area[i][c_start][c_end];
                    set<int>::iterator sit=cumset.upper_bound(cum-k-1);
                    if(sit!=cumset.end())
                        best=max(best,cum-*sit);
                    cumset.insert(cum);
                }
                max_one = std::max(max_one, best);
                // ------------------ this is from discuss place --------------
            }
        }
        return max_one;
    }
};
