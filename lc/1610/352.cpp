/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
 
bool operator< (const Interval& a, const Interval& b){
    return a.start < b.start;
}
 
class SummaryRanges {
    set<Interval> ranges;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        // 161024, ...
    }
    
    void addNum(int val) {
        set<Interval>::iterator l = ranges.lower_bound(Interval{val,val});
        // fisrt with the after one
        if(l == ranges.end() || l->start>val+1)  // new one
            ranges.emplace(Interval{val,val});
        else{    // expand the latter one
            int s = l->end;
            ranges.erase(l);
            ranges.emplace(Interval{val,s});
        }
        l = ranges.lower_bound(Interval{val,val});
        // combine with the before one??
        if(l != ranges.begin()){
            auto lm1 = l;
            lm1 --;
            if(lm1->end >= val-1){
                int s0=lm1->start, s1=std::max(l->end, lm1->end);
                ranges.erase(l);
                ranges.erase(lm1);
                ranges.emplace(Interval{s0,s1});
            }
        }
    }
    
    vector<Interval> getIntervals() {
        vector<Interval> v;
        for(auto x: ranges)
            v.emplace_back(x);
        return v;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */