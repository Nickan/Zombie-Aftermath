#include "Message.h"

Message::Message(const int& senderId, const int& receiverId, const float& dispatchTime, MessageType msgType, void* extraInfo) {
    this->senderId = senderId;
    this->receiverId = receiverId;
    this->dispatchTime = dispatchTime;
    this->msgType = msgType;
    this->extraInfo = extraInfo;
}

Message::~Message()
{
    //dtor
}
