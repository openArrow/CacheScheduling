#include<vector>
#include<iostream>
using namespace std;
class Lru
{
	int _sizeOfCache;
	int _miss;
	int _hit;
	vector<long> _cache; //lru cache
public:
	Lru(int size)
	{
		_sizeOfCache = size;
		_miss = 0;
		_hit = 0;
	}
	int getSizeOfCache() { return _sizeOfCache;}
	int getMiss() { return _miss; }
	int getHit() { return _hit; }
	double getHitRatio() ;
	int reference(long starting_block, int number_of_blocks);
};
