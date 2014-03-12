#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "Message.h"

class BaseEntity
{
    public:
        BaseEntity(const int& id);

        const int& getId();
        virtual bool handleMessage(Message* msgPtr) = 0;
        virtual ~BaseEntity();
    protected:
    private:
        int id;
};

#endif // BASEENTITY_H
