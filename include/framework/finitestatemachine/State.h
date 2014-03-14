#ifndef STATE_H
#define STATE_H

template <class Owner_Entity>
class State {
    public:
        virtual void start(Owner_Entity* entity) = 0;
        virtual void update(Owner_Entity* entity, const float& delta) = 0;
        virtual void exit(Owner_Entity* entity) = 0;
    protected:
    private:
};

#endif // STATE_H
