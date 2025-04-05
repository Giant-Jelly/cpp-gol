#ifndef EVENT_H
#define EVENT_H 

class MouseEvents {
    public:
        bool mouseDown;
        int x;
        int y;
};

class KeyboardEvents {
    public:
        bool space = false; //TODO: Ask matt why these are initialised true some times when not defined
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
};
#endif
