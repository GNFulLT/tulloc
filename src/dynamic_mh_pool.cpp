#include "dynamic_mh_pool.h"

#include <cassert>

MHPool::MHPool(std::uint16_t tsize, std::uint16_t growCount) : m_tsize(tsize),m_growCount(growCount)
{
	p_shouldDealloc = nullptr;
	p_usingBucket = nullptr;
}

MHPool::~MHPool()
{
	auto iter = m_buckets.begin();
	while (iter != m_buckets.end())
	{
		iter->release();
		iter++;
	}
}

void* MHPool::allocate()
{
	if (p_usingBucket == nullptr || p_usingBucket->is_full())
	{
		//X Check there is any empty bucket
		auto iter = m_buckets.begin();
		while (iter != m_buckets.end())
		{
			if (!iter->is_full())
			{
				break;
			}
			iter++;
		}
		//X If there is, use it
		if (iter != m_buckets.end())
		{
			p_usingBucket = iter._Ptr;
		}
		else
		{
			{
				//X TODO : COPY CTOR CAUSES BUG
				//X There is no empty bucket, create one
				m_buckets.emplace_back(m_tsize,m_growCount);
			}
			m_buckets.back().init();
			
			p_usingBucket = &m_buckets.back();
		}
	}
	return p_usingBucket->allocate();
}

void MHPool::deallocate(void* ptr)
{
	if (p_shouldDealloc == nullptr || !p_shouldDealloc->belongs(ptr))
	{
		//X Find belongs bucket
		auto iter = m_buckets.begin();
		while (iter != m_buckets.end())
		{
			if (iter->belongs(ptr))
			{
				break;
			}
			iter++;
		}
		
		//X Should be never reached
		assert(iter != m_buckets.end());
		
		p_shouldDealloc = iter._Ptr;
	}

	p_shouldDealloc->deallocate(ptr);

	//X TODO : Releasing bucket
}


