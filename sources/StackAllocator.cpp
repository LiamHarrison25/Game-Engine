#include "StackAllocator.h"

void StackAllocator::Reset()
{
	head = stack.data();
}

char* StackAllocator::GetCurrentHead()
{
	return head;
}

void StackAllocator::ClearToFrame(char* frame)
{

	if (frame < stack.data() || frame >(stack.data() + stack.size()))
	{
		std::cerr << "Tried to clear to frame pointer " << frame << ", but it's not"
			<< " within stack " << stack.data() << "!\n";
		return;
	}

	head = frame;
}

float StackAllocator::PctUsed()
{ 
	return 100.f * ((float)BytesInUse() / stack.size()); 
}

