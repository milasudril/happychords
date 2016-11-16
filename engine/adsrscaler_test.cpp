//@	{"targets":[{"name":"adsrscaler_test","type":"application"}]}

#include "adsrscaler.hpp"
#include <cstdio>

int main()
	{
	Happychords::AdsrScaler scaler;
	auto base=2.0f;
	Happychords::AdsrScaler::Params params(128,base,1,1.5,0.5,1);
	
	auto val=1.0f;
	scaler.attack();
	for(int k=0;k<328;++k)
		{
		printf("%.8g\n",val);
		val=scaler.stateUpdate(params,val);
		}
	scaler.release();
	for(int k=0;k<328;++k)
		{
		printf("%.8g\n",val);
		val=scaler.stateUpdate(params,val);
		}
	return 0;
	}
