#ifndef BUCKET_H
#define BUCKET_H

#include <cstddef>
#include <cstdint>

class MHPool;

class Bucket
{
public:
	~Bucket();
	void init();
	
	void* allocate();
	bool belongs(void* ptr) const noexcept;
	void deallocate(void* ptr);
	void release();
	bool is_full() const noexcept;
private:
	Bucket(std::uint16_t tsize, std::uint16_t initalCount);
	void* get_node_by_id(std::uint16_t id);
private:
	bool m_is_released;
	//X Total Block count in Bucket
	std::uint16_t m_block_num;

	std::uint16_t m_used_block_num;
	
	//X Next allocating index
	std::uint16_t m_alloc_pointer;

	//X Begin pointer
	std::size_t m_begin_pointer;

	std::uint16_t m_block_size;

	std::uint16_t m_bucket_size;
	friend class MHPool;
};

#endif // BUCKET_H