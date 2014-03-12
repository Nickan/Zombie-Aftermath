#ifndef STATE_H
#define STATE_H

template <class Entity>
class State {
    public:
        virtual void start(Entity* entity) = 0;
        virtual void update(Entity* entity, const float& delta) = 0;
        virtual void exit(Entity* entity) = 0;
    protected:
    private:
};

#endif // STATE_H
