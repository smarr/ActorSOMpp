/*
 *  ActorMessaging.cpp
 *  SOM
 *
 *  Created by Stefan Marr on 02/06/09.
 *  Copyright 2009 Vrije Universiteit Brussel. All rights reserved.
 *
 */

#include "ActorMessaging.h"

#include <string.h>
#include <stdlib.h>

bool ActorMessaging::HasIncommingMessages() {
    return actors_msgbuffer_holds_data();
}

Message* _receiveMessage(Messages msgType) {
    Message* result;
    do {
        void* buffer;
        size_t size;
        actors_msgbuffer_read_msg(&buffer, &size);
        
        result = Message::Deserialize(buffer);
        result->Process();
        
#warning possibly lossing messages here, should be stored in a queue for later processing
        
        free(buffer);        
    } while (result->GetType() != msgType);
    
    return result;
}

SomMessage* ActorMessaging::ReceiveSomMessage() { 
    return (SomMessage*)_receiveMessage(SOM_MSG);
}

pVMObject ActorMessaging::ReceiveObjectReference() {
    ObjRefMessage* msg = (ObjRefMessage*)_receiveMessage(OBJ_REF_MSG);
    pVMObject obj = msg->GetObject();
    delete msg;
    return obj;
}

void ActorMessaging::SendObjectReference(pVMObject obj, actor_id_t actorId) {
    cout << "[A:" << dec << actors_id() << "] SendObjectReference to " << actorId << endl;
    ObjRefMessage msg(RemoteObjectManager::GetGlobalId(obj));
    SendMessage(&msg, actorId);
}

void ActorMessaging::SendMessage(Message* msg, actor_id_t actorId) {
    size_t buffer_size = msg->GetSize();
  
    // this size alignment is for the syncedqueue implementation which uses int32_t as smallest units
    void* buffer = malloc( ((buffer_size / sizeof(int32_t)) + 1) * sizeof(int32_t) );
    
    msg->Serialize(buffer);
        
    actors_msgbuffer_send_msg(actorId, buffer, buffer_size);

    free(buffer);
    
//    assert(size % sizeof(int32_t) == 0); to make sure the allocated memory is alligned
}