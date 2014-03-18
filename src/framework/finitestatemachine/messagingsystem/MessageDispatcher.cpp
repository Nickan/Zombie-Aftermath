#include "MessageDispatcher.h"

vector<Message*> MessageDispatcher::msgPtrList;

MessageDispatcher::MessageDispatcher() { }


void MessageDispatcher::update(const float& delta) {
    for (unsigned int index = 0; index < msgPtrList.size(); ++index) {
        Message* msgPtr = msgPtrList.at(index);
        msgPtr->dispatchTime -= delta;

        if (msgPtr->dispatchTime <= 0) {
            dischargeMessage(msgPtr, index);

            // Bring the counter back to its current index, as it will delete the current index
            --index;
        }
    }

}

void MessageDispatcher::dischargeMessage(Message* msgPtr, const int& index) {
    // Error checking...
    if (msgPtr->receiverId == -1) {
        cout << "Receiver ID is -1" << endl;
        delMsgPtr(msgPtr, index);
        return;
    } else if (msgPtr->senderId == -1) {
        cout << "Sender ID is -1" << endl;
        delMsgPtr(msgPtr, index);
        return;
    }

    BaseEntity* entity = EntityManager::getEntity(msgPtr->receiverId);

    if (entity->handleMessage(msgPtr)) {
        delMsgPtr(msgPtr, index);
    }
}

void MessageDispatcher::delMsgPtr(Message* msgPtr, const int& index) {
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

