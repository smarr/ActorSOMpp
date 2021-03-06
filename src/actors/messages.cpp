/*
 *  messages.cpp
 *  SOM
 *
 *  Created by Stefan Marr on 05/06/09.
 *  Copyright 2009 Vrije Universiteit Brussel. All rights reserved.
 *
 */

#include <err.h>

#include "messages.h"

#include "../vm/Universe.h"

#include "../vmobjects/VMClass.h"
#include "../vmobjects/VMSymbol.h"

#include "../misc/debug.h"

Message* Message::Deserialize(void* buffer) {
    Messages msgType = (Messages)*(int32_t*)buffer;
    buffer = (void*)((intptr_t)buffer + sizeof(int32_t));
    
    switch (msgType) {
        case EXIT_MSG:              return new ExitMsg();
        case SOM_MSG:               return new SomMessage(buffer);
        case SOM_MSG_WITH_RESULT:   return new SomMessageWithResult(buffer);
        case OBJ_REF_MSG:           return new ObjRefMessage(buffer);
        case OBJ_REF_RESULT_MSG:    return new ResultObjRefMessage(buffer);
        default:
            warnx("Message::Deserialize: unexpected msgType\n");
    }
    
    return NULL;
}

void ExitMsg::Process() {
    _UNIVERSE->GetInterpreter()->Stop();
}

void NewRefNotificationMsg::Process() {
    RemoteObjectManager::NewExternalReference(referencedObj.index, actor);
}

void UnlinkRefMsg::Process() {
    RemoteObjectManager::ObjectUnlinked(referencedObj.index, actor);
}

void ObjRefMessage::Process() {
    Interpreter::AddIncommingObjRef(GetObject());
}

void ResultObjRefMessage::Process() {
    Interpreter::HandleRemoteReturn(resultActivation, GetObject());
}

void SomMessage::Process() {
    DebugLog("Process SomMessage: %s>>%s\n", 
             GetReceiver()->GetClass()->GetName()->GetChars(), 
             GetSignature()->GetChars());
    
    Interpreter::ProcessMessage(this);
}
void SomMessageWithResult::Process() {
    DebugLog("Process SomMessageWithResult: %s>>%s\n", 
             GetReceiver()->GetClass()->GetName()->GetChars(), 
             GetSignature()->GetChars());
    
    Interpreter::ProcessMessage(this);
}