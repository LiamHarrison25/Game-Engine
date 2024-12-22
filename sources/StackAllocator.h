#pragma once

#include <iostream>
#include <vector>

class StackAllocator
{
public:

    StackAllocator(size_t size = 4096) :
        stack(size, 0),
        stackSize(stack.size()),
        head(stack.data())
    {}

    template <typename T, typename ...Us>
    T* Alloc(Us... args) 
    {
        const size_t size = sizeof(T);
        const size_t bytesUsed = head - stack.data();
        const size_t bytesRemaining = stackSize - bytesUsed;
        if (bytesRemaining < size)
        {
            std::cerr << "Stack failed to allocate!\n";
            return nullptr;
        }

        char* ptrToObject = head;
        new (ptrToObject) T(args...);
        head += size;
        return (T*)ptrToObject;
    }

    template <typename T>
    T* AllocArray(size_t arrayCount = 4096)
    {
        const size_t size = sizeof(T) * arrayCount;
        const size_t bytesUsed = head - stack.data();
        const size_t bytesRemaining = stackSize - bytesUsed;
        if (bytesRemaining < size)
        {
            std::cerr << "Stack failed to allocate!\n";
            return nullptr;
        }

        char* ptrToObject = head;
        head += size;
        return (T*)ptrToObject;
    }

    void Reset();

    char* GetCurrentHead();

    void ClearToFrame(char* frame);

    size_t Capacity() { return stack.size(); }

    size_t BytesInUse() 
    { 
        return head - stack.data(); 
    }

    float PctUsed();

private:

    std::vector<char> stack;

    size_t stackSize;

    char* head;
};
