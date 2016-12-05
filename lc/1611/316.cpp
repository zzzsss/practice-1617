class Solution {
public:
	string removeDuplicateLetters(string s) {
		// 161120,
		// build next position
		vector<int> prevChar(26, -1);
		vector<int> nextPosition(s.size(), -1);
		for(unsigned i = 0; i<s.size(); i++){
			char x = s[i];
			int prevPos = prevChar[x - 'a'];
			if(prevPos >= 0)
				nextPosition[prevPos] = i;
			prevChar[x - 'a'] = i;
		}
		// scan them
		string ret;
		vector<bool> hasInclude(26, false);
		int curIndex = 0;
		while(curIndex < s.size()){
			// select from a run
			char selectChar = 'z' + 1;    // guarantee larger
			int selectIndex = -1;
			int thisIndex = curIndex;
			while(thisIndex<s.size()){
				char thisChar = s[thisIndex];
				bool thisIncluded = hasInclude[thisChar - 'a'];
				bool thisHasNext = (nextPosition[thisIndex] >= 0);
				if(!thisIncluded && thisChar<selectChar){  // find smaller one
					selectChar = thisChar;
					selectIndex = thisIndex;
				}
				if(thisIncluded || thisHasNext)
					thisIndex++;
				else
					break;
			}
			// pick the smallest one
			if(selectIndex >= 0){
				ret += s[selectIndex];
				hasInclude[ret.back()-'a'] = true;
				curIndex = selectIndex + 1;
			}
			else
				break;
		}
		return ret;
	}
};