#include <windows.h>
#include <thread>
#include "mouse.h"

bool Mouse::isDown(int opt) {
    if (opt == 1) {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
    } else if (opt == 2) {
        return (GetAsyncKeyState(VK_RBUTTON) & 0x8000);
    } else {
        return (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000);
    }
}

void Mouse::Move(short x, short y) {
    mouse_event(MOUSEEVENTF_MOVE, x, y, 0, 0);
}
