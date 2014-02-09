#ifndef INPUT_H
#define INPUT_H

class Input {
    public:
        Input();
        virtual void leftMousePressed(const int& x, const int& y) = 0;
        virtual void leftMouseReleased(const int& x, const int& y) = 0;
        virtual void rightMousePressed(const int& x, const int& y) = 0;
        virtual void rightMouseReleased(const int& x, const int& y) = 0;

        virtual void mouseMoved(const int& x, const int& y) = 0;
        virtual void mouseMotion(const int& x, const int& y) = 0;

        virtual void keyPressed(const int& keycode) = 0;
        virtual void keyReleased(const int& keycode) = 0;
        virtual ~Input();
    protected:
    private:
};

#endif // INPUT_H
