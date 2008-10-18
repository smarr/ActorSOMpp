#include "VMPrimitive.h"
#include "VMSymbol.h"
#include "VMClass.h"
#include "../vm/Universe.h"

//needed to instanciate the Routine object for the  empty routine
#include "../primitives/Routine.h"

VMPrimitive* VMPrimitive::GetEmptyPrimitive( VMSymbol* sig )
{
    
    VMPrimitive* prim = new (_HEAP) VMPrimitive(sig);
    *(prim->empty) = true;
    prim->SetRoutine(new (_HEAP) Routine<VMPrimitive>(prim, &VMPrimitive::EmptyRoutine));
    return prim;
}

VMPrimitive::VMPrimitive(VMSymbol* signature) : VMInvokable(2)//,VMObject()
{
    _UNIVERSE->GetHeap()->StartUninterruptableAllocation();
    //the only class that explicitly does this.
    this->SetClass(primitive_class);
    this->empty = (bool*)_HEAP->Allocate(sizeof(bool));
    this->SetSignature(signature);
    this->routine = NULL;
    *(this->empty) = false;
    _UNIVERSE->GetHeap()->EndUninterruptableAllocation();
}
//TODO: this is a memory leak. The empty flag is not freed and the routine is not destroyed
//, but G++ doesn't like the destructor of VMObject classes
//VMPrimitive::~VMPrimitive(Heap* heap)
//{
//    _HEAP->Free(empty, sizeof(bool));
//    if (routine != NULL) Core::destroy(routine);
//}

bool VMPrimitive::IsEmpty()
{
    return *empty;
}

void VMPrimitive::SetRoutine(PrimitiveRoutine* rtn)
{
    routine = rtn;
}

void VMPrimitive::Invoke(VMFrame *frm)
{
    (*routine)(this, frm);
}

void VMPrimitive::MarkReferences()
{
    if (gcfield) return;
    //VMInvokable::MarkReferences();
    this->SetGCField(1);
    for( int i = 0; i < this->GetNumberOfFields(); ++i) 
    {
        //HACK to avoid calling MarkReferences() for the bool*
        if ((void*)FIELDS[i] == (void*)this->empty) 
            continue;
        FIELDS[i]->MarkReferences();
    }
}

void VMPrimitive::EmptyRoutine( VMObject* _self, VMFrame* /*frame*/ )
{
    VMInvokable* self = (VMInvokable*) _self;
    VMSymbol* sig = self->GetSignature();
    cout << "undefined primitive called: " << sig->GetChars() << endl;
}

