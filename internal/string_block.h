#ifndef STRING_BLOCK_H
#define STRING_BLOCK_H

#include <cstddef>

class StringBlock
{
public:
	StringBlock(std::size_t size);

	void init();

	void release();
private:
	void allocate_mem(std::size_t length);
private:
	//X Begin pointer
	std::size_t m_begin_pointer;

	char* m_alloc_pointer;
	
	std::size_t m_size;
};

#endif // STRING_BLOCK_H