#include <string.h>

//#include "../misc/defs.h"
//#include "../vmobjects/VMObject.h"
#include "../vmobjects/PrimitiveRoutine.h"

#include "Array.h"
#include "BigInteger.h"
#include "Block.h"
#include "Class.h"
#include "Double.h"
#include "Integer.h"
#include "Object.h"
#include "String.h"
#include "Symbol.h"
#include "System.h"


#include "../primitivesCore/PrimitiveContainer.h"
#include "../primitivesCore/PrimitiveLoader.h"

#if defined (_MSC_VER)
#include "Core.h"
#endif

static PrimitiveLoader* loader = NULL;
//map<StdString, PrimitiveContainer*> primitiveObjects;
//"Constructor"
//#define __DEBUG
extern "C" void setup() {
    if (!loader) {
#ifdef __DEBUG
        cout << "Setting up the Core library" << endl;
#endif
        //Initialize loader
        loader = new PrimitiveLoader();
        loader->AddPrimitiveObject("Array", 
            static_cast<PrimitiveContainer*>(new _Array()));

        loader->AddPrimitiveObject("BigInteger", 
            static_cast<PrimitiveContainer*>(new _BigInteger()));

        loader->AddPrimitiveObject("Block", 
            static_cast<PrimitiveContainer*>(new _Block()));

        loader->AddPrimitiveObject("Class", 
            static_cast<PrimitiveContainer*>(new _Class()));

        loader->AddPrimitiveObject("Double", 
            static_cast<PrimitiveContainer*>(new _Double()));

        loader->AddPrimitiveObject("Integer", 
            static_cast<PrimitiveContainer*>(new _Integer()));

        loader->AddPrimitiveObject("Object", 
            static_cast<PrimitiveContainer*>(new _Object()));

        loader->AddPrimitiveObject("String", 
            static_cast<PrimitiveContainer*>(new _String()));

        loader->AddPrimitiveObject("Symbol", 
            static_cast<PrimitiveContainer*>(new _Symbol()));

        loader->AddPrimitiveObject("System", 
            static_cast<PrimitiveContainer*>(new _System()));
    }
}

extern "C" bool supportsClass(const char* name) {
    if (!loader) setup();
    return loader->SupportsClass(name);
}



extern "C" void tearDown() {
    //primitiveClasses.clear();
    if (loader) delete loader;
    //if (primitiveObjects) delete primitiveObjects;
}

extern "C" PrimitiveRoutine* create(const StdString& cname, const StdString& fname) {

#ifdef __DEBUG
    cout << "Loading PrimitiveContainer: " << cname << "::" << fname << endl;
#endif
    if (!loader) setup();
    return loader->GetPrimitiveRoutine(cname, fname);
}

