#include"lru.h"
#include<algorithm>
#include <iomanip>
#include<fstream>
int Lru::reference(long starting_block, int number_of_blocks)
{
	for(long page = starting_block; page < starting_block + number_of_blocks; page++)
	{

		vector<long>::iterator it = std::find(_cache.begin(), _cache.end(), page);
		vector<long>::iterator itTemp ;
		if (it != _cache.end()) 
		{
			_hit++;
			
			_cache.erase(it);
			itTemp = _cache.begin();
			_cache.insert(itTemp,page);
		}
		else
		{
			_miss++;
			if(_sizeOfCache == _cache.size())
			{
				it = _cache.end();
				if(_cache.size()!=0)
				_cache.erase(it-1);
				
			}
			it = _cache.begin();
			_cache.insert(it, page);
		}
		
	}
}
double Lru::getHitRatio()
{
	double ratio = (double)_hit/(_miss + _hit);
	return ratio*100;
}
main(int argc,char *argv[])
{

	long size;
	size = atoi(argv[1]);
	Lru lru(size);
		
	string line;
	ifstream in_stream;
	in_stream.open(argv[2]);
	if(!in_stream.is_open())
	{
		cout<<"Unable to open file"<<endl;
		return 0;
	}
	long a,b,c,d,i;
	i=0;
	//Reading the file
	while(in_stream >> a>>b>>c>>d)
	{
			lru.reference(a,b);
	}
	cout<<"Hit Ratio:"<<fixed<<setprecision(2)<<lru.getHitRatio()<<endl;	
	in_stream.close();
}
