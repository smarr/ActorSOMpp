/*
 * $Id: String.c 116 2007-09-20 13:29:40Z tobias.pape $
 *
Copyright (c) 2007 Michael Haupt, Tobias Pape
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

#include <stdio.h>

#include "../vmobjects/VMObject.h"
#include "../vmobjects/VMFrame.h"
#include "../vmobjects/VMString.h"
#include "../vmobjects/VMInteger.h"

#include "../vm/Universe.h"

#include "../misc/defs.h"

#include "String.h"

_String* String;

void  _String::Concatenate_(VMObject* object, VMFrame* frame) {

    VMString* arg = (VMString*)frame->Pop();
    VMString* self = (VMString*)frame->Pop();
    pString a = pString(arg->GetChars());
    pString s = pString(self->GetChars());
    
    pString result = s + a;

    frame->Push((VMObject*)_UNIVERSE->new_string(result));
}


void  _String::AsSymbol(VMObject* object, VMFrame* frame) {
    VMString* self = (VMString*)frame->Pop();
    pString result = self->GetStdString();
    frame->Push((VMObject*)_UNIVERSE->symbol_for(result));
}


void  _String::Hashcode(VMObject* object, VMFrame* frame) {
    VMString* self = (VMString*)frame->Pop();
    frame->Push((VMObject*)_UNIVERSE->new_integer(self->GetHash()));
}


void  _String::Length(VMObject* object, VMFrame* frame) {
    VMString* self = (VMString*)frame->Pop();
    pString result = self->GetStdString();
    size_t len = result.length();
    frame->Push(_UNIVERSE->new_integer((int32_t)len));
}


void  _String::Equal(VMObject* object, VMFrame* frame) {
    VMObject* op1 = frame->Pop();
    VMString* op2 = (VMString*)frame->Pop();
    
    if(op1->GetClass() == string_class) {
        
        pString s1 = ((VMString*)op1)->GetStdString();
        pString s2 = op2->GetStdString();

        if(s1 == s2) {
            frame->Push(true_object);
            return;
        }
    }
    frame->Push(false_object);
}


void  _String::PrimSubstringFrom_To_(VMObject* object, VMFrame* frame) {
    VMInteger* end = (VMInteger*)frame->Pop();
    VMInteger* start = (VMInteger*)frame->Pop();
    
    VMString* self = (VMString*)frame->Pop();
    
    pString str = self->GetStdString();
    int s = start->GetEmbeddedInteger();
    int e = end->GetEmbeddedInteger();
    
    pString result = str.substr(s, e - s);

    frame->Push((VMObject*) _UNIVERSE->new_string(result));
}