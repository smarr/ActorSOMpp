#pragma once

#ifndef VMARRAY_H_
#define VMARRAY_H_

//#include <vector>
#include "VMObject.h"
#include "VMInteger.h"

class VMArray : public VMObject {
public:
    VMArray(int size, int nof = 0);
	//virtual ~VMArray();
	virtual void MarkReferences();

	void        SetIndexableField(int idx, VMObject* item);
	
	inline int         GetNumberOfIndexableFields() const;
	VMArray*    CopyAndExtendWith(VMObject*) const;
	void        CopyIndexableFieldsTo(VMArray*) const;

	VMObject* operator[](int idx) const;

private:

	VMInteger* size;
};

int VMArray::GetNumberOfIndexableFields() const {
    return size->GetEmbeddedInteger();
}

#endif
