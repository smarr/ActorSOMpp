#pragma once
#ifndef METHODGENERATIONCONTEXT_H_
#define METHODGeNERATIONCONTEXT_H_

#include <vector>

#include "../misc/defs.h"
#include "ClassGenerationContext.h"
//#include "../misc/ExtendedVector.h"
#include "../misc/ExtendedList.h"
class VMMethod;
class VMArray;
class VMPrimitive;

class MethodGenerationContext {
public:
	MethodGenerationContext();
	~MethodGenerationContext();
    
    VMMethod*       Assemble();
    VMPrimitive*    AssemblePrimitive();

	int8_t          FindLiteralIndex(VMObject* lit);//pVMObject lit);
	bool            FindVar(const StdString& var, int* index, 
                            int* context, bool* is_argument);
	bool            FindField(const StdString& field);
	uint8_t         ComputeStackDepth();

	void            SetHolder(ClassGenerationContext* holder);
	void            SetOuter(MethodGenerationContext* outer);
	void            SetIsBlockMethod(bool is_block = true);
	void            SetSignature(VMSymbol* sig);
	void            AddArgument(const StdString& arg);
	void            SetPrimitive(bool prim = true);
	void            AddLocal(const StdString& local);
	void            AddLiteral(VMObject* lit);
	bool            AddArgumentIfAbsent(const StdString& arg);
	bool            AddLocalIfAbsent(const StdString& local);
	bool            AddLiteralIfAbsent(VMObject* lit);
	void            SetFinished(bool finished = true);

	ClassGenerationContext*     GetHolder();
	MethodGenerationContext*    get_outer();

	VMSymbol*       GetSignature();
	bool            IsPrimitive();
	bool            IsBlockMethod();
	bool            IsFinished();
	void            RemoveLastBytecode() { bytecode.pop_back(); };
	int             GetNumberOfArguments();
	void            AddBytecode(uint8_t bc);
private:
	ClassGenerationContext*    holder_genc;
    MethodGenerationContext*   outer_genc;
    bool                       block_method;
    VMSymbol*                  signature;
    ExtendedList<StdString>  arguments;
    bool                       primitive;
    ExtendedList<StdString>  locals;
    ExtendedList<VMObject*>                      literals;
    bool                       finished;
	vector<uint8_t>            bytecode;
};

#endif
