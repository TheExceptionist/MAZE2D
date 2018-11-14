#include "mem_manager.h"
#include <stdlib.h>
#include <assert.h>

MemoryManager::MemoryManager(e_std::e_word size) :
    m_size(size)
{
    m_pool = (e_std::e_byte*) malloc(size);
    m_current_top = m_pool;
    m_bottom = (m_current_top + size);
}

MemoryManager::~MemoryManager()
{
    free(m_pool);
    m_pool = NULL;
    m_current_top = NULL;
    m_bottom = NULL;
}

void* MemoryManager::alloc(e_std::e_word size)
{
    int alignment = size % BYTE_IN_WORD;
    size += BYTE_IN_WORD - alignment;

    assert(m_current_top + size <= m_bottom);
    
    void* ptr_block = (void*) m_current_top;
    m_current_top += size;
    return ptr_block;
}

e_std::e_byte* MemoryManager::getMarker()
{
    return m_current_top;
}

void MemoryManager::freeToMarker(e_std::e_byte* marker)
{
    if(marker > m_bottom || marker < m_pool)
    {
        printf("Marker out-of-block");
        return;
    } 

    m_current_top = marker;
}


void MemoryManager::freeStack()
{
    m_current_top = m_pool;
}