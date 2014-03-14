#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"

template <class Owner_Entity>
class StateMachine {
    public:
        virtual ~StateMachine() {}

        // First time I will make the implementation in the header, as according to the code I saw, it is almost this way he made
        // it. But I want to write it my own way, for me to learn how template in C++ is used
        StateMachine(Owner_Entity* entityPtr) {
            this->entityPtr = entityPtr;
            this->currentStatePtr = NULL;
        }

        void changeState(State<Owner_Entity>* statePtr) {
            if (currentStatePtr != NULL) {
                currentStatePtr->exit(NULL);
            }
            currentStatePtr = statePtr;
            currentStatePtr->start(entityPtr);
        }

        void update(const float& delta) {
            if (currentStatePtr != NULL) {
                currentStatePtr->update(entityPtr, delta);
            }
        }

    protected:
    private:
        Owner_Entity* entityPtr;
        State<Owner_Entity>* currentStatePtr;
};

#endif // STATEMACHINE_H
