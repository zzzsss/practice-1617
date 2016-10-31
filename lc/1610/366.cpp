class Solution {
public:
    int calc_gcd(int x, int y){
        int small = std::min(x,y);
        int large = std::max(x,y);
        if(y%x == 0)
            return x;
        return calc_gcd(y%x, x);
    }
    bool canMeasureWater(int x, int y, int z) {
        // 161019, |a*x - b*y| == z
        if(z>(x+y))
            return false;
        if(z==x || z==y || z==(x+y))
            return true;
        if(x==0 || y==0)
            return false;
        int a = calc_gcd(x,y);
        return (z%a)==0;
    }
};