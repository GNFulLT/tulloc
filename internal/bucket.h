#ifndef BUCKET_H
#define BUCKET_H

#include <cstddef>
#include <cstdint>

class Bucket
{
public:
	Bucket(std::uint16_t tsize,std::uint16_t initalCount);
	~Bucket();
	void init();
	
	void* allocate();
	bool belongs(void* ptr) const noexcept;
	void deallocate(void* ptr);
private:
	void* get_node_by_id(std::uint16_t id);
private:
	//X Total Block count in Bucket
	std::uint16_t m_block_num;

	std::uint16_t m_used_block_num;
	
	//X Next allocating index
	std::uint16_t m_alloc_pointer;

	//X Begin pointer
	std::size_t m_begin_pointer;

	std::uint16_t m_block_size;

	std::uint16_t m_bucket_size;
};

#endif // BUCKET_H