#ifndef MESSAGE_H
#define MESSAGE_H

enum MessageType {
    TARGET_ZOMBIE, HIT_ZOMBIE,      // Cannon's Message
    TARGET_RESPONSE, HIT_RESPONSE, // Zombie's Message
};

class Message
{
    public:
        Message(const int& senderId, const int& receiverId, const float& dispatchTime, MessageType msgType, void* extraInfo);

        int senderId;
        int receiverId;
        float dispatchTime;
        MessageType msgType;
        void* extraInfo;

        virtual ~Message();
    protected:
    private:
};

#endif // MESSAGE_H
