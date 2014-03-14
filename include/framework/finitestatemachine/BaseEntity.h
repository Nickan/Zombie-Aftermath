#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "Message.h"
#include "EntityManager.h"

class BaseEntity
{
    public:
        BaseEntity();

        const int& getId();
        virtual const bool handleMessage(Message* msgPtr) = 0;
        virtual ~BaseEntity();
    protected:
        int id;
    private:

};

#endif // BASEENTITY_H
