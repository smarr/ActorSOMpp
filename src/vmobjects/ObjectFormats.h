#pragma once
#ifndef OBJECTFORMATS_H_
#define OBJECTFORMATS_H_

/*
 *
 *
Copyright (c) 2007 Michael Haupt, Tobias Pape, Arne Bergmann
Software Architecture Group, Hasso Plattner Institute, Potsdam, Germany
http://www.hpi.uni-potsdam.de/swa/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
  */

#define pVMArray VMPointer<VMArray>
#define pVMBigInteger VMPointer<VMBigInteger>
#define pVMBlock VMPointer<VMBlock>
#define pVMClass VMPointer<VMClass>
#define pVMDouble VMPointer<VMDouble>
#define pVMEvaluationPrimitive VMPointer<VMEvaluationPrimitive>
#define pVMFrame VMPointer<VMFrame>
#define pVMInteger VMPointer<VMInteger> 
#define pVMInvokable VMPointer<VMInvokable>
#define pVMMethod VMPointer<VMMethod> 
#define pVMObject VMPointer<VMObject> 
#define pVMPrimitive VMPointer<VMPrimitive> 
#define pVMString VMPointer<VMString> 
#define pVMSymbol VMPointer<VMSymbol> 
#define pVMRemoteObject VMPointer<VMRemoteObject>

typedef enum ImmutableTypes {
    NotImmutable,
    
    BigIntegerTag,
    DoubleTag,
    IntegerTag,
    StringTag,
    SymbolTag,
    GlobalObjectIdTag
} ImmutableTypes;


#endif OBJECTFORMATS_H_
