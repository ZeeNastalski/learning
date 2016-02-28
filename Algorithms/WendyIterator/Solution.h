#pragma once
#include <iosfwd>
#include <vector>

class Solution
{
private:

	std::vector<int> vec;

public:
	Solution(std::istream& s);
	virtual ~Solution();





	class iterator 
	{
		friend Solution;
		
	
		public: 
		
		inline iterator(int idx, std::vector<int>& v) : itVec(v), idx(idx)
		{
			
		}

		inline iterator& operator++()
		{
			idx++;
			return *this;
		}

		inline bool operator==(iterator& rhs)
		{
			return this->idx == rhs.idx;
		}

		inline bool operator!=(iterator& rhs)
		{
			return this->idx != rhs.idx;
		}

		inline double operator*()
		{
			return itVec[idx];
		}


		private:
			int idx = 0;
			std::vector<int> &itVec;
		


	};


	iterator begin();
	iterator end();


};

