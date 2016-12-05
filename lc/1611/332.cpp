class Solution {
    vector<string> placeNames;
    unordered_map<string, int> placeIndexes;
    vector<multiset<int>> placeDestinations;
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        // 161110, eular path
        // sort all the names and construct index
        unordered_set<string> places;
        for(auto& x: tickets){
            if(places.find(x.first) == places.end()){
                placeNames.emplace_back(x.first);
                places.insert(x.first);
            }
            if(places.find(x.second) == places.end()){
                placeNames.emplace_back(x.second);
                places.insert(x.second);
            }
        }
        std::sort(placeNames.begin(), placeNames.end());
        for(unsigned i=0; i<placeNames.size(); i++){
            placeIndexes[placeNames[i]] = i;
        }
        placeDestinations = vector<multiset<int>>(placeNames.size());
        // build degree and destinations
        for(auto& x: tickets){
            int indexFrom = placeIndexes[x.first];
            int indexTo = placeIndexes[x.second];
            placeDestinations[indexFrom].insert(indexTo);
        }
        // iteration
        vector<int> path{};
        path.push_back(placeIndexes["JFK"]);   // start
        while(1){
            // get the start node backward
            int postitionInsert = -1;
            for(postitionInsert=path.size()-1; postitionInsert>=0; postitionInsert--){
                if(placeDestinations[path[postitionInsert]].size()>0)
                    break;
            }
            if(postitionInsert<0)
                break;
            // get one path or loop
            int curNode = path[postitionInsert];
            vector<int> thisPath;
            while(1){
                thisPath.emplace_back(curNode);
                multiset<int>& placeGo = placeDestinations[curNode];
                auto iter = placeGo.begin();
                if(iter==placeGo.end())
                    break;
                curNode = *iter;
                placeGo.erase(iter);
            }
            // put it back
            path.erase(path.begin()+postitionInsert);
            path.insert(path.begin()+postitionInsert, thisPath.begin(), thisPath.end());
        }
        vector<string> ret;
        for(int x: path)
            ret.push_back(placeNames[x]);
        return ret;
    }
};