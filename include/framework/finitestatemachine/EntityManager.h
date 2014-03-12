#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "BaseEntity.h"
#include <vector>

using namespace std;

class EntityManager
{
    public:
        static BaseEntity* getEntity(const int& id);
        static const int getAvailableId(BaseEntity* entity);
        static void deleteEntity(const int& id);
    protected:
    private:
        EntityManager();
        virtual ~EntityManager();

        static vector<BaseEntity*> entityList;

        static int idCounter;
};

#endif // ENTITYMANAGER_H
