#include "string_block.h"

#include <cstring>
#include <cassert>

StringBlock::StringBlock(char* beginPtr, std::size_t size) noexcept : m_begin(beginPtr),m_size(size)
{
	m_inUsageCount = 0;
}

bool StringBlock::isFull() const noexcept
{
	return m_size ==  m_inUsageCount;
}

std::size_t StringBlock::size() const noexcept
{
	return m_inUsageCount;
}

std::size_t StringBlock::capacity() const noexcept
{
	return m_size;
}

void StringBlock::copy(const char* str)
{
	assert(strlen(str) > 0 && strlen(str) <= m_size);
	auto strSize = strlen(str);
	memcpy(m_begin, str, strSize);
	if (strSize < m_size)
	{
		//X TODO : NEED TEST
		for (int i = strSize; i < m_size; i++)
		{
			*(m_begin + i) = '\0';
		}
	}
}

void StringBlock::reset() noexcept
{
	//X TODO : NEED TEST
	for (int i = 0; i < m_size; i++)
	{
		*(m_begin + i) = '\0';
	}
}

std::size_t StringBlock::get_free_space() const noexcept
{
	return m_size - m_inUsageCount;
}

std::string_view StringBlock::as_string_view() const noexcept
{
	return std::string_view(m_begin,m_inUsageCount);
}
