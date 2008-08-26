#include "GarbageCollector.h"
#include "../vm/Universe.h"
#include "../vmobjects/VMObject.h"
#include "Heap.h"
#include <vector>

GarbageCollector::GarbageCollector(Heap* h)
{
	heap = h;
}

GarbageCollector::~GarbageCollector()
{
}

void GarbageCollector::Collect()
{
	markReachableObjects();
	void* pointer = heap->object_space;
	free_list_entry* currentEntry = heap->free_list_start;
	long bytesToSkip = 0;

	do
	{
		//see whether the currentObject is part of the free list
		while( currentEntry->next != NULL &&
			pointer > (void*)currentEntry->next)
		{
			currentEntry = currentEntry->next;
		}

		//check if it is in the free list
		if (pointer == (void*)currentEntry)
		{
			bytesToSkip = currentEntry->size;
		} else if (pointer == (void*)currentEntry->next) 
		{
			bytesToSkip = currentEntry->next->size;
		} else 
		{ //we found a VMObject
			VMObject* object = (VMObject*) pointer;
			bytesToSkip = object->getObjectSize();

			if (object->getGCField() == 1) 
			{
				object->setGCField(0);
				std::cout << "Found alive object, keeping" << std::endl;
			}
			else 
			{
				std::cout << "Found trash, deleting" << std::endl;
				//delete(object, heap);//doesn't really do anything for managed objects
				//add freed space as a new entry of the free list
				memset(object, 0, bytesToSkip);
				free_list_entry* newEntry = (free_list_entry*)pointer;
				newEntry->size = bytesToSkip;
				if (newEntry < heap->free_list_start) {
					newEntry->next = heap->free_list_start;
					heap->free_list_start = newEntry;
					currentEntry = newEntry;
				} else {
					newEntry->next = currentEntry->next;
					currentEntry->next = newEntry;
				}

			}
		}

		pointer = (void*)((long)pointer + bytesToSkip);

	} while((long)pointer < ((long)(void*)heap->object_space) + heap->object_space_size);

	mergeFreeSpaces();
}

void GarbageCollector::markReachableObjects()
{
	vector<globals_entry> globals = Universe::GetUniverse()->GetGlobals();

	
	for (vector<globals_entry>::iterator it = globals.begin(); it!= globals.end(); ++it)
	{
		markObject(&(*it->value));
	}

	//get frame from interpreter, recursively mark from there...
}

void GarbageCollector::markObject(VMObject* obj)
{
	if (   ((void*) obj >= (void*)  heap->object_space) 
		&& ((void*) obj <= (void*) heap->object_space) + heap->object_space_size)
	{
		if (obj->getGCField() != 1)
		{
			obj->setGCField(1);
			obj->MarkReferences();
		}
	}
}

void GarbageCollector::mergeFreeSpaces()
{
	std::cout << "free heap before collecting: " << heap->size_of_free_heap << std::endl;
	free_list_entry* currentEntry = heap->free_list_start;
	heap->size_of_free_heap = 0;
	while (currentEntry->next != NULL) {
		if((int)currentEntry + (int)currentEntry->size == (int)currentEntry->next)
		{
			std::cout << "merging entry at address " << currentEntry << " (size: "<< currentEntry->size << ") ";
			std::cout << "with entry at address " << currentEntry->next << " (size: "<< currentEntry->next->size << ")" << std::endl;
			currentEntry->size += currentEntry->next->size;
			std::cout << "new entry size: " << currentEntry->size << std::endl;
			currentEntry->next = currentEntry->next->next;
		} else {
			heap->size_of_free_heap += currentEntry->size;
			currentEntry = currentEntry->next;
		}
	}
	heap->size_of_free_heap += currentEntry->size;
	std::cout << "free heap after collecting: " << heap->size_of_free_heap << std::endl;
}
