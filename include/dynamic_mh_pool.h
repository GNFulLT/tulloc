#ifndef DYNAMIC_MH_POOL_H
#define DYNAMIC_MH_POOL_H


#include <vector>

class Bucket;

class MHPool
{
public:
	MHPool(std::uint16_t tsize,std::uint16_t growCount);
	~MHPool();
	void* allocate();
	void deallocate(void* ptr);
private:
	std::uint16_t m_tsize;
	std::uint16_t m_growCount;
	std::vector<Bucket> m_buckets;
	Bucket* p_usingBucket;
	Bucket* p_shouldDealloc;
};


#endif  //DYNAMIC_MH_POOL_H
