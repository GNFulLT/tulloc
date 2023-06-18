#ifndef STRING_POOL_H
#define STRING_POOL_H

#include <vector>

class StringPool
{
public:
	StringPool() = default;
	StringPool(std::size_t blockSize) noexcept;
private:
	//std::vector<StringBlock> m_block;

	std::size_t m_defaultBlockSize = 32 << 8 ;
};

#endif // STRING_POOL_H