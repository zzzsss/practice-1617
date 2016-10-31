class RandomizedCollection {
private:
    unordered_map<int, unordered_set<int>> map;   // key->index
    vector<int> values;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        // 161006-, slightly change to the unique one
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        values.push_back(val);  // put first
        auto iter = map.find(val);
        if(iter != map.end()){
            iter->second.insert(values.size()-1);
            return false;
        }
        // insert it
        map[val] = unordered_set<int>{};
        map[val].insert(values.size()-1);
        return true;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto iter = map.find(val);
        if(iter == map.end())
            return false;
        // always the last one, exchange it with the last element in the vector
        int lastv = values.back();
        int one = *(iter->second.begin());
        if(lastv != val){
            values[one] = lastv;
            map[lastv].erase(values.size()-1);
            map[lastv].insert(one);
        }
        else
            one = values.size()-1;
        values.pop_back();
        map[val].erase(one);
        if(map[val].empty())
            map.erase(val);
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int r = rand()%values.size();
        return values[r];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */