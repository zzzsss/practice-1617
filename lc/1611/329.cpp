class Solution {
private:
    static constexpr int VALUE_UNKNOWN = 0;
public:
    int get_longest(int r, int c, const vector<vector<int>>& matrix, vector<vector<int>>& values){
        // fill in values if have not calculating it before (0)
        int numRows = matrix.size();
        int numColumns = matrix[0].size();
        if(values[r][c] == VALUE_UNKNOWN){
            // calculate the new value for nodes around
            int vCur = matrix[r][c];
            int valMax = 0;
            if(r>0 && vCur<matrix[r-1][c])           // up
                valMax = std::max(valMax, get_longest(r-1,c,matrix,values));
            if(r<numRows-1 && vCur<matrix[r+1][c])   // down
                valMax = std::max(valMax, get_longest(r+1,c,matrix,values));
            if(c>0 && vCur<matrix[r][c-1])           // left
                valMax = std::max(valMax, get_longest(r,c-1,matrix,values));
            if(c<numColumns-1 && vCur<matrix[r][c+1])// right
                valMax = std::max(valMax, get_longest(r,c+1,matrix,values));
            values[r][c] = valMax+1;
        }
        return values[r][c];
    }
    int longestIncreasingPath(const vector<vector<int>>& matrix) {
        // 161115, recursion (we will never dead-loop because using strictly increasing)
        if(matrix.empty())
            return 0;
        vector<vector<int>> values(matrix.size(), vector<int>(matrix[0].size(), 0));
        int vMax = 0;
        for(int r=0; r<matrix.size(); r++)
            for(int c=0; c<matrix[0].size(); c++)
                vMax = std::max(vMax, get_longest(r,c,matrix,values));
        return vMax;
    }
};