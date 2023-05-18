#ifndef STRING_BLOCK_H
#define STRING_BLOCK_H

#include <cstddef>
#include <string_view>
class StringBlock
{
public:
	StringBlock(char* beginPtr,std::size_t size) noexcept;

	bool isFull() const noexcept;

	std::size_t size() const noexcept;

	std::size_t capacity() const noexcept;

	void copy(const char* str);

	void reset() noexcept;

	std::size_t get_free_space() const noexcept;

	std::string_view as_string_view() const noexcept;
private:

	char* m_begin;
	std::size_t m_size;
	std::size_t m_inUsageCount;

};

#endif // STRING_BLOCK_H