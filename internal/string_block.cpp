#include "string_block.h"

#include "os.h"

StringBlock::StringBlock(std::size_t size) : m_size(size)
{
	m_begin_pointer = 0;
}

void StringBlock::init()
{
	//X Allocate page for this block
	m_begin_pointer = std::size_t(allocate_page_default(0, m_size));
	m_alloc_pointer = (char*)m_begin_pointer;
}

void StringBlock::release()
{
	free_page_default(m_begin_pointer, m_size);
}

void StringBlock::allocate_mem(std::size_t length)
{
	char* ptr = m_alloc_pointer;


}

