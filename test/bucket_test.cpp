#include "bucket.h"

int main()
{
	Bucket bcket(sizeof(int),500);
	bcket.init();
	auto intp = bcket.allocate();
	auto intp2 = bcket.allocate();
	auto intp3 = bcket.allocate();
	auto intp4 = bcket.allocate();
	bcket.deallocate(intp);
	bcket.deallocate(intp4);
	return 0;
}