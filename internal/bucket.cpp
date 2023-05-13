#include "bucket.h"

#include <windows.h>
#include <memoryapi.h>
#include <new>
#include <cassert>

Bucket::Bucket(std::uint16_t tsize, std::uint16_t initalCount) : m_alloc_pointer(0),m_block_size(tsize),m_block_num(initalCount),m_used_block_num(0)
{
    //X Minimum size is integer.
    assert(tsize >= sizeof(int));

    m_begin_pointer = 0;
    m_bucket_size = m_block_size * m_block_num;
}

Bucket::~Bucket()
{
    assert(m_begin_pointer != 0);
    ::VirtualFree((void*)(m_begin_pointer), 0, MEM_RELEASE);
}

void Bucket::init()
{
    void* begin = ::VirtualAlloc
    (
        nullptr,
        m_block_size * m_block_num,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    if (begin == nullptr)
    {
        throw std::bad_alloc();
    }

    m_begin_pointer = (std::size_t)begin;
    //X All nodes says next index is available
    for (std::uint16_t i = 0; i < m_block_num; i++)
    {
        void* node = get_node_by_id(i);
        (*(std::uint16_t*)node) = (std::uint16_t)i+1;
        auto t = (*(std::uint16_t*)node);
        int b = 5;
    }
}

void* Bucket::allocate()
{
    assert(m_begin_pointer != 0);
    std::uint16_t nextAlloc = m_alloc_pointer;
    void* ptrrr = get_node_by_id(nextAlloc);
    m_alloc_pointer = (*(std::uint16_t*)ptrrr);
    
    m_used_block_num++;

    return (void*)(m_begin_pointer + nextAlloc * m_block_size);
}

bool Bucket::belongs(void* ptr) const noexcept
{
    return std::uint16_t(ptr) >= m_begin_pointer && std::uint16_t(ptr) < m_begin_pointer + m_bucket_size;
}

void Bucket::deallocate(void* ptr)
{
    assert(m_begin_pointer != 0);
    assert(m_used_block_num > 0);
    
    // Alignment
    assert((std::size_t(ptr) - m_begin_pointer) % m_block_size == 0);
    std::uint16_t id = (std::size_t(ptr) - m_begin_pointer) / m_block_size;

    (*(std::uint16_t*)get_node_by_id(id)) = m_alloc_pointer;
    m_alloc_pointer = id;
    m_used_block_num--;
}

void* Bucket::get_node_by_id(std::uint16_t id)
{
    std::size_t uptr =  m_begin_pointer + id * m_block_size;
    //X Block size can be odd. Need to check
    return uptr % 2 == 0 ? (void*)uptr : (void*)(uptr + 1);
}


