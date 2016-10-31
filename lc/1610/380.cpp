class RandomizedSet {
private:
    unordered_map<int, int> map;   // key->index
    vector<int> values;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        // 151006-1035, using a hashmap and value list
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto iter = map.find(val);
        if(iter != map.end())
            return false;
        // insert it
        map[val] = values.size();
        values.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto iter = map.find(val);
        if(iter == map.end())
            return false;
        // exchange it with the last element
        int lastv = values.back();
        if(lastv != val){
            values[iter->second] = lastv;
            map[lastv] = iter->second;
        }
        values.pop_back();
        map.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int r = rand()%values.size();
        return values[r];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */