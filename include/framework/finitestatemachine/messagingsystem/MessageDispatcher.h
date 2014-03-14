#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include "EntityManager.h"
#include "Message.h"
#include <vector>

using namespace std;

class MessageDispatcher {
    public:
        static void update(const float& delta);
        static void sendMessage(const int& senderId, const int& receiverId, const float& dispatchTime, MessageType msg, void* extraInfo);
    protected:
    private:
        MessageDispatcher();
        virtual ~MessageDispatcher();

        static void dischargeMessage(Message* msgPtr, const int& msgIndex);

        static vector<Message*> msgPtrList;
};

#endif // MESSAGEDISPATCHER_H
