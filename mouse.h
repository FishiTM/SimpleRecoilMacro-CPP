#include <windows.h>
#include <thread>

class Mouse {
    public:
        bool isDown(int opt);
        void Move(short x, short y);
};
