class Solution {
public:
    // 40min, 1st submit, 160921-10:41
	// about 20min for debugging (but not focus on this), final-ok on 10:59
    pair<bool, double> search_it(unordered_map<string, vector<pair<string, double>>>& graph, unordered_map<string, bool>& visited, 
        double v, string cur, string end){
        // search the graph, current is cur, ending is end, return {valid?, value}
        // 1. mark visit
        visited[cur] = true;
        // 2. tell the ending
        if(cur == end)
            return {true, v};
        // 3. for-each
        for(auto& one: graph[cur]){
            if(!visited[one.first]){
                auto r = search_it(graph, visited, v*one.second, one.first, end);
                if(r.first)
                    return r;
            }
        }
        return {false, v};
    }
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        // store the graph and do DFS
        // 1. store the graph
        unordered_map<string, vector<pair<string, double>>> g;
        for(int i=0; i<equations.size(); i++){
            // construct it, Assuming no zeros or contradiction
            if(g.find(equations[i].first) == g.end())
                g[equations[i].first] = vector<pair<string, double>>{};
            if(g.find(equations[i].second) == g.end())
                g[equations[i].second] = vector<pair<string, double>>{};
            g[equations[i].first].emplace_back(make_pair(equations[i].second, values[i]));
            g[equations[i].second].emplace_back(make_pair(equations[i].first, 1/values[i]));
        }
        // 2. DFS search for each query
        vector<double> answers;
        for(auto& q: queries){
            string s0 = q.first;
            string s1 = q.second;
            if(g.find(s0)==g.end() or g.find(s1)==g.end())
                answers.push_back(-1.0);
            else{
                //prepare the search
                unordered_map<string, bool> visited;
                for(auto& pp: g)
                    visited[pp.first] = false;
                // start it
                auto r = search_it(g, visited, 1.0, s0, s1);
                if(r.first)
                    answers.push_back(r.second);
                else
                    answers.push_back(-1.0);
            }
        }
        return answers;
    }
};