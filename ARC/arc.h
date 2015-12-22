#include<vector>
#include<iostream>
using namespace std;
class Arc
{
        int _size;
	int temp;	
	int p;
        int _miss;
        int _hit;
        vector<long> _T1;
	vector<long> _B1;
        vector<long> _T2;
        vector<long> _B2;
public:
        Arc(int size)
        {
                _size = size;
                _miss = 0;
                _hit = 0;
		p = 0;
        }
	~Arc(){}
        int getSizeOfCache() { return _size;}
        int getMiss() { return _miss; }
        int getHit() { return _hit; }
        void getHitRatio() ;
        void reference(long starting_block, int number_of_blocks);
	void CaseNum1(long block_number);
	void CaseNum2(long block_number);
	void CaseNum3(long block_number);
	void CaseNum4(long block_number);
	void Replace(long block_number, int p);
};

