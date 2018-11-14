#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#define MEM_ALLOC_SIZE 2
#define MBYTES 1000000
#define BYTE_IN_WORD 4

#include "defs.h"

class MemoryManager
{
public:
    MemoryManager(e_std::e_word size);
    virtual ~MemoryManager();

    virtual void* alloc(e_std::e_word size);
    
    e_std::e_byte* getMarker();
    void freeToMarker(e_std::e_byte* marker);
    void freeStack();

    static MemoryManager& get()
    {
        static MemoryManager* mem_manager = new MemoryManager(MEM_ALLOC_SIZE * MBYTES);
        return *mem_manager;
    }
protected:
    e_std::e_word m_size;
    e_std::e_byte* m_pool;
    e_std::e_byte* m_current_top;
    e_std::e_byte* m_bottom;

};

#endif // MEM_MANAGER_H
