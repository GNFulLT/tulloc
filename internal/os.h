#ifndef OS_H
#define OS_H

#include <cstddef>

#ifdef WIN32
#include <windows.h>
#include <memoryapi.h>
#else
#error NOT DEFINED FOR THIS PLATFORM
#endif

#ifdef WIN32
void* allocate_page(void* lpAddress,std::size_t size, DWORD flAllocationType,DWORD flProtect)
{
	return ::VirtualAlloc
    (
        nullptr,
        size,
        flAllocationType,
        flProtect
    );
}

void free_page(void* lpAddres,DWORD size,DWORD freeType)
{
    ::VirtualFree((void*)(lpAddres), size, freeType);

}

#else
#error NOT DEFINED FOR THIS PLATFORM
#endif

#endif // OS_H