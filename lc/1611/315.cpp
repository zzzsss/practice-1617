class Solution {
private:
	template<class T>
	class BstNode{
	public:
		T elem;
		int num{1};
		BstNode* left{nullptr};
		BstNode* right{nullptr};
		BstNode(const T& one): elem{one}{}
	};
	template<class T>
	class Bst{
	private:
		BstNode<T>* root{nullptr};
	public:
		int insert_and_count(const T& one){
			int number = 0;
			BstNode<T>** start = &root;
			while((*start) != nullptr){
			    (*start)->num++;
				if(one <= (*start)->elem)	// here use <=
					start = &((*start)->left);
				else{
					number += 1;	// current start node
					if((*start)->left)
						number += (*start)->left->num;
					start = &((*start)->right);
				}
			}
			*start = new BstNode<T>{one};
			return number;
		}
	};
public:
	vector<int> countSmaller(const vector<int>& nums) {
		// 161121, multiset
		vector<int> ret;
		Bst<int> readins;
		for(int i = nums.size() - 1; i >= 0; i--){
			int n = readins.insert_and_count(nums[i]);
			ret.push_back(n);
		}
		std::reverse(ret.begin(), ret.end());
		return ret;
	}
};