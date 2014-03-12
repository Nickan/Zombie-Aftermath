#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

template <class Entity>
class StateMachine {
    public:
        StateMachine(Entity* entity);
        virtual ~StateMachine();

        void changeState(State<Entity>* statePtr);
        void update(const float& delta);

        // First time I will make the implementation in the header, as according to the code I saw, it is almost this way he made
        // it. But I want to write it my own way, for me to learn how template in C++ is used
        StateMachine(Entity* entityPtr) {
            this->entityPtr = entityPtr;
        }

        void changeState(State<Entity>* statePtr) {
            if (currentStatePtr != null) {
                currentStatePtr->exit(entityPtr);
            }
            currentStatePtr = statePtr;
            currentStatePtr->start(entityPtr);
        }

        void update(const float& delta) {
            currentStatePtr->update(entityPtr, delta);
        }

    protected:
    private:
        Entity* entityPtr;
        State<Entity>* currentStatePtr;
};

#endif // STATEMACHINE_H
