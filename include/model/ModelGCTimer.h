#ifndef MODELGCTIMER_H
#define MODELGCTIMER_H

//-----------------------------------------------------------------------------------------------------------
//
// A very simple class that has the ID of the entity that needs to be erased and the time duration it has
// before deleting it
//-----------------------------------------------------------------------------------------------------------

class ModelGCTimer
{
    public:
        ModelGCTimer(const int& entityId, const float& duration);
        virtual ~ModelGCTimer();

        const int& getEntityId();

        float duration;
    protected:
    private:
        int entityId;
};

#endif // MODELGCTIMER_H
