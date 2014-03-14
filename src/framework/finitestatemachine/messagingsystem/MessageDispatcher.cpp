#include "MessageDispatcher.h"

vector<Message*> MessageDispatcher::msgPtrList;

MessageDispatcher::MessageDispatcher() { }


void MessageDispatcher::update(const float& delta) {
    for (unsigned int index = 0; index < msgPtrList.size(); ++index) {
        Message* msgPtr = msgPtrList.at(index);
        msgPtr->dispatchTime -= delta;

        // Later, optimize and dispatch other messages that should be, make it run for now
        if (msgPtr->dispatchTime <= 0) {
            dischargeMessage(msgPtr, index);
            break;
        }
    }

}

void MessageDispatcher::dischargeMessage(Message* msgPtr, const int& index) {
    // Error checking...
    if (msgPtr->receiverId == -1) {
        cout << "Receiver ID is -1" << endl;
        delMsgPtr();
        return;
    } else if (msgPtr->senderId == -1) {
        cout << "Sender ID is -1" << endl;
        delMsgPtr();
        return;
    }

    BaseEntity* entity = EntityManager::getEntity(msgPtr->receiverId);

    if (entity->handleMessage(msgPtr)) {
        delMsgPtr();
    }
}

void MessageDispatcher::delMsgPtr(Message* msgPtr) {
    msgPtrList.erase(msgPtrList.begin() + index);
        delete msgPtr;
}

void MessageDispatcher::sendMessage(const int& senderId, const int& receiverId,
    const float& dispatchTime, MessageType msgType, void* extraInfo) {
    msgPtrList.push_back(new Message(senderId, receiverId, dispatchTime, msgType, extraInfo));
}

MessageDispatcher::~MessageDispatcher() {
    //dtor
}

