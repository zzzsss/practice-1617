class Twitter {
private:
    int time_stamp{0};
    unordered_map<int, vector<int>> posts;   //tweetId
    unordered_map<int, int> post_time;
    unordered_map<int, set<int>> followings;
public:
    /** Initialize your data structure here. */
    Twitter() {   
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if(posts.find(userId) == posts.end())
            posts[userId] = vector<int>{};
        posts[userId].emplace_back(tweetId);
        post_time[tweetId] = time_stamp;
        time_stamp++;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        auto ret = posts[userId];
        if(followings.find(userId) != followings.end()){
            for(auto f: followings[userId])
                if(f!=userId)
                    ret.insert(ret.end(), posts[f].begin(), posts[f].end());
        }
        std::sort(ret.begin(), ret.end(), [this](int i, int j){return this->post_time[i]>this->post_time[j];});
        if(ret.size()>10)
            ret.resize(10);
        return ret;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(followings.find(followerId) == followings.end())
            followings[followerId] = set<int>{};
        followings[followerId].insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(followings.find(followerId) == followings.end())
            followings[followerId] = set<int>{};
        followings[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */