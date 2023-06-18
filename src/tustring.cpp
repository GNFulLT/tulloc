#include "tustring.h"

#include <cstring>
#include <cassert>

TuString::TuString(char* beginPtr, std::size_t size) noexcept : m_begin(beginPtr),m_size(size)
{
	m_inUsageCount = strlen(beginPtr);
}

bool TuString::isFull() const noexcept
{
	return m_size ==  m_inUsageCount;
}

std::size_t TuString::size() const noexcept
{
	return m_inUsageCount;
}

std::size_t TuString::capacity() const noexcept
{
	return m_size;
}

void TuString::copy(const char* str)
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

void TuString::reset() noexcept
{
	//X TODO : NEED TEST
	for (int i = 0; i < m_size; i++)
	{
		*(m_begin + i) = '\0';
	}
}

std::size_t TuString::get_free_space() const noexcept
{
	return m_size - m_inUsageCount;
}

std::string_view TuString::as_string_view() const noexcept
{
	return std::string_view(m_begin,m_inUsageCount);
}
