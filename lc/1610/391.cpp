struct qelement{
    int x1, x2, h;
    qelement(int a, int b, int hh): x1(a), x2(b), h(hh){}
    qelement(const qelement&)=default;
};
bool operator<(const qelement& a, const qelement& b){
    return a.h>b.h || (a.h == b.h && a.x1>b.x1);
}
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
		// 2 submits in 1 hour, 161001-1124, mainly for maintaining the data-structure using priority_queue (sorted by height of the span)
        // first sort the rectangles by the left-most point: first on y, then on x
        std::sort(rectangles.begin(), rectangles.end(),
            [](const vector<int>& a, const vector<int>& b){return a[1]<b[1]||(a[1]==b[1]&&a[0]<b[0]);});
        // maintain the priority queue sorted by the same criterion
        priority_queue<qelement> queue;
        // scan the first line and construct the queue
        int sx=rectangles[0][0], sy=rectangles[0][1];
        auto before = vector<int>{sx, sy, sx, sy};
        auto iter = rectangles.begin();
        while(iter!=rectangles.end() && (*iter)[1]==sy){
            if((*iter)[0] != before[2])
                return false;   // not match
            queue.push(qelement{(*iter)[0], (*iter)[2], (*iter)[3]});
            before = *iter;
            iter ++;
        }
        // scan the rest
        while(iter!=rectangles.end()){
            // pop the queue element
            qelement one = queue.top(); queue.pop();
            if((*iter)[0] != one.x1 || (*iter)[1] != one.h)
                return false;   // not match
            // check the width and expand/add
            while(one.x2 < (*iter)[2]){
                if(queue.empty())
                    return false;   // no more
                qelement tmp_one = queue.top(); queue.pop();
                if(tmp_one.h != one.h || tmp_one.x1 != one.x2)
                    return false;   // not adjencent
                one = tmp_one;
            }
            queue.push(qelement((*iter)[0], (*iter)[2], (*iter)[3]));
            if(one.x2 > (*iter)[2]) // add new one
                queue.push(qelement((*iter)[2], one.x2, one.h));
            iter ++;
        }
        // must remian the same height
        int final_h = queue.top().h;
        while(!queue.empty()){
            if(queue.top().h != final_h)
                return false;
            queue.pop();
        }
        return true;
    }
};