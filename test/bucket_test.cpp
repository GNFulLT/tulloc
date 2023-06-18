#include "bucket.h"
#include "dynamic_mh_pool.h"
#include "string_pool.h"

#include <sstream>
#include <chrono>

void string_test()
{
	StringPool allocator;
	auto str = allocator.allocate("Selamm");
	auto str2 = allocator.allocate("Asss");
}

void bucket_test()
{
	Bucket bcket(sizeof(int), 5000);
	bcket.init();
	
	auto beginTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 5000; i++)
	{
		auto intp = bcket.allocate();
		bcket.deallocate(intp);

	}
	auto endTime = std::chrono::high_resolution_clock::now();
	auto diff = (endTime - beginTime).count();

	beginTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 5000; i++)
	{
		auto intp = new int;
		delete intp;
	}

	endTime = std::chrono::high_resolution_clock::now();
	auto diff2 = (endTime - beginTime).count();
	int a = 5;
	

}

void mh_pool_alloc_dealloc()
{
	MHPool pool(sizeof(int),50);
	auto t1 = pool.allocate();
	auto t2 = pool.allocate();
	auto t3 = pool.allocate();
	auto t4 = pool.allocate();
	auto t5 = pool.allocate();
	auto t6 = pool.allocate();

	pool.deallocate(t1);
	pool.deallocate(t2);
	pool.deallocate(t3);
	pool.deallocate(t4);
	pool.deallocate(t5);
	pool.deallocate(t6);

}


void mh_pool_alloc_bucket()
{
	MHPool pool(sizeof(int), 10);
	std::vector<int*> ptrs;
	for (int i = 0; i < 10; i++)
	{
		ptrs.push_back((int*)pool.allocate());
	}
	auto elevenPtr = pool.allocate();
	for (int i = 0; i < 10; i++)
	{
		pool.deallocate(ptrs[i]);
	}
	pool.deallocate(elevenPtr);
}

int main()
{

	// PASSED
	// bucket_test();
	// PASSED
	// mh_pool_alloc_dealloc();
	//mh_pool_alloc_bucket();
	// PASSED
	//bucket_test();
	string_test();
	return 0;
}