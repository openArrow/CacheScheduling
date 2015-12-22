#include"arc.h"
#include <fstream>
#include <algorithm>
#include <time.h>
#include <iomanip>
//utility function used by the class
float max(float a , float b)
{
	if(a>b)
		return a;
	else
		return b;
}
float min(float a , float b)
{
	if(a>b)
		return b;
	else
		return a;
}

/******************class function definitions*******************/


/******************Function to get page from cache*******************/
void Arc::reference(long block_number, int number_of_blocks)
{
	for (int i = 0; i < number_of_blocks; i++) {
		CaseNum1(block_number + i);
	}
}


/******************Case 1 of the Adaptive Replacement Cache*******************/
void Arc::CaseNum1(long block_number)
{

	//cout<<"case 1"<<endl;
	vector<long>::iterator itT1 = std::find(_T1.begin(), _T1.end(), block_number);
	vector<long>::iterator itT2 = std::find(_T2.begin(), _T2.end(), block_number);
	vector<long>::iterator itTemp ;

	if (itT1 != _T1.end() || itT2 != _T2.end()) 
	{
		_hit++;
		if (itT2 != _T2.end()) {
			_T2.erase(itT2);
			_T2.insert(_T2.begin(), block_number);
		} 
		else
		{
			_T2.insert(_T2.begin(), block_number);
			if(itT1 != _T1.end())
			_T1.erase(itT1);

		}	
	} else
		CaseNum2(block_number);
}


/******************Case 2 of the Adaptive Replacement Cache*******************/
void Arc::CaseNum2(long block_number)
{

	//cout<<"case 2"<<endl;
	vector<long>::iterator itB1 = std::find(_B1.begin(), _B1.end(), block_number);
	vector<long>::iterator itTemp ;
	if (itB1 != _B1.end()) {
		_miss++;
	int delta1 = 0;
		if (_B1.size() >= _B2.size()) {
			delta1 = 1;
		} else 
		{
			if(_B1.size()!=0)
			delta1 = _B2.size() / _B1.size();
		}
		p = min(p + delta1, _size);
		Replace(block_number, p);
		 itB1 = std::find(_B1.begin(), _B1.end(), block_number);
		_B1.erase(itB1);
		itTemp = std::find(_T2.begin(), _T2.end(), block_number);
		if (itTemp != _T2.end()) {
			_T2.erase(itTemp);
			_T2.insert(_T2.begin(), block_number);
		} else {
			
			
			_T2.insert(_T2.begin(), block_number);
			
		}

	} else 
	{
		CaseNum3(block_number);
	}
}

/******************Case 3 of the Adaptive Replacement Cache*******************/
void Arc::CaseNum3(long block_number)
{

			//cout<<"3"<<endl;
	vector<long>::iterator itB2 = std::find(_B2.begin(), _B2.end(), block_number);
	vector<long>::iterator itTemp ;

	if (itB2 != _B2.end())
	{
		_miss++;
		int delta2 = 0;
		if (_B2.size() >= _B1.size()) {
			delta2 = 1;
		} else {
			if(_B2.size() != 0)
			delta2 = _B1.size() / _B2.size();
		}
		p = max(p - delta2, 0);
		Replace(block_number,p);
		itB2 = std::find(_B2.begin(), _B2.end(), block_number);
		_B2.erase(itB2);
		itTemp = std::find(_T2.begin(), _T2.end(), block_number);
		
		if (itTemp != _T2.end())
		{
			_T2.erase(itTemp);
			_T2.insert(_T2.begin(), block_number);
		}
		else
		{
			_T2.insert(_T2.begin(), block_number);
		}
	}
	else
	{
		CaseNum4(block_number);
	}
}

/******************Case 4 of the Adaptive Replacement Cache*******************/
void Arc::CaseNum4(long block_number)
{
	//cout<<"case 4"<<endl;
	vector<long>::iterator itT1 = std::find(_T1.begin(), _T1.end(), block_number);
	vector<long>::iterator itT2 = std::find(_T2.begin(), _T2.end(), block_number);
	vector<long>::iterator itB1 = std::find(_B1.begin(), _B1.end(), block_number);
	vector<long>::iterator itB2 = std::find(_B2.begin(), _B2.end(), block_number);
	vector<long>::iterator itTemp ;
	// Case A		
	if (itT1 == _T1.end() &&  itT2 == _T2.end() && itB1 == _B1.end() && itB2 == _B2.end()) 
	{
		_miss++;
		if (_T1.size() + _B1.size() == _size) {
			if (_T1.size() < _size) {

				itTemp = _B1.end();
				if(_B1.size() != 0)
					_B1.erase(itTemp - 1);
				Replace(block_number, p);
			} else {
				itTemp = _T1.end();

				if(_T1.size() != 0)
					_T1.erase(itTemp - 1);
			}
		}
		// Case B
		else if (_T1.size() + _B1.size() + _T2.size() + _B2.size() >= _size) {
					if (_T1.size() + _B1.size() + _T2.size() + _B2.size() == 2 * _size) {
						if (_B2.size() != 0) {
							itTemp = _B2.end();	
							_B2.erase(itTemp - 1);
						}
					}
					Replace(block_number, p);
				}
			
		

		itT1 = std::find(_T1.begin(), _T1.end(), block_number);
		if (itT1 != _T1.end()) {
			_T1.erase(itT1);
			itTemp = _T1.begin();
			_T1.insert(itTemp, block_number);
		} else {
			itTemp = _T1.begin();
			_T1.insert(itTemp, block_number);
		}
	}
}

/******************Function to print Hit ratio*******************/
void Arc::getHitRatio() 
{
	double d = ((double) _hit / (_hit + _miss) )* 100;
	cout<<"Hit Ratio:"<<fixed<<setprecision(2)<<d<<endl;
}

/******************REPLACE function of the Adaptive Replacement Cache*******************/
void Arc::Replace(long block_number, int p)
{

	vector<long>::iterator itB2 = std::find(_B2.begin(), _B2.end(), block_number);
	vector<long>::iterator itTemp;
	long temp;	
	if (_T1.size() != 0 && (_T1.size() > p || (itB2 != _B2.end() && _T1.size() == p))) {
			temp = _T1.back();
			_T1.pop_back();
			_B1.insert(_B1.begin(), temp);
	} else {
			temp = _T2.back();
			_T2.pop_back();
			_B2.insert(_B2.begin(), temp);
	}
}
main(int argc,char *argv[])		
{

// argv[1] is the size of cache
// argv[2] is the trace file
	long size;
	size = atoi(argv[1]);
	Arc arc(size);

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
	while(in_stream >> a>>b>>c>>d)
	{
	arc.reference(a,b);
	}
	arc.getHitRatio();	
	in_stream.close();
}

