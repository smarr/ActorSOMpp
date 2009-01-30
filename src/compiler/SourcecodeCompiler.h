#pragma once

#ifndef SOURCECODECOMPILER_H_
#define SOURCECODECOMPILER_H_

#include "../misc/defs.h"
#include "../vmobjects/ObjectFormats.h"

class VMClass;
class Parser;

class SourcecodeCompiler
{
public:
    SourcecodeCompiler();
    ~SourcecodeCompiler();

    pVMClass CompileClass(const StdString& path, const StdString& file,
                                  pVMClass system_class);
    pVMClass CompileClassString(const StdString& stream, pVMClass system_class);
private:
    void showCompilationError(const StdString& filename, const char* message);
    pVMClass compile(pVMClass system_class);
    Parser* parser;
};

#endif
