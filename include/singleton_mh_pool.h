#ifndef SINGLETON_MH_POOL
#define SINGLETON_MH_POOL


#include <vector>
#include <mutex>

class Bucket;

class SingletonMHPool
{
public:
	SingletonMHPool(std::uint16_t tsize, std::uint16_t growCount);
	~SingletonMHPool();
private:
	void* allocate();
	void deallocate(void* ptr);
private:
	std::uint16_t m_tsize;
	std::uint16_t m_growCount;
	std::vector<Bucket> m_buckets;
	Bucket* p_usingBucket;
	Bucket* p_shouldDealloc;
	
	std::mutex m_mutex;
};

#endif // SINGLETON_MH_POOL