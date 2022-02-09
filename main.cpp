#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include "mouse.h"

int x = 0;
int y = 3;
int z = 20;

bool recoilEnabled = false;
int mouseOpt = 3;
void recoil_thread();
void ui_thread();

int main() {
    system("cls");
    SetPriorityClass(GetCurrentProcess(), 0x00008000);
    
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recoil_thread, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ui_thread, NULL, 0, NULL);
    // std::cout << "Running!" << std::endl;

    for (;;) {
        Sleep(1);
    }
    std::cout << "Closing!" << std::endl;
    return 0;
}

std::string onoroff(bool b) { // CONVERT BOOL 'b' TO STRING "On" OR STRING "Off"
    if (b) {
        return "On"; 
    } else {
        return "Off";
    }
}

void ui_thread() {
    system("Color 0F"); // 0=Black F=BrightWhite
    int p = 0; int c = -1;
    for (;;) {
        switch (p)
        {
        case 0:
            system("title Fishi's Simple Recoil - Menu"); system("cls");
            std::cout << "[1] Toggle ["<<onoroff(recoilEnabled)<<"]" << std::endl << "[2] Change Settings" << std::endl << std::endl;
            std::cin >> c;
            if (c == 1 || c == 2) { // IF VALID OPTION
                p = c;
            } else { 
                // ELSE NOTHING
            }
            break;
        case 1:
            system("cls");
            recoilEnabled = !recoilEnabled; // SWITCH TOGGLE (T>F || F>T)
            p = 0; break;
        case 2:
            system("title Fishi's Simple Recoil - Menu - Settings"); system("cls");
            std::cout << "[1] X" << std::endl << "[2] Y" << std::endl << "[3] Sleep" << std::endl << "[4] Mouse Button" << std::endl << std::endl;
            c = -1; std::cin >> c; system("cls");
            int inp; inp = 5000;
            switch (c)
            {
            case 1:
                std::cout << "X: "; if (std::cin >> inp && (inp >= -50 && inp <= 50)) { x = inp; } std::cout << std::endl; system("cls"); p = 0; break;
            case 2:
                std::cout << "Y: ";  if (std::cin >> inp && (inp >= 0 && inp <= 50)) { y = inp; } std::cout << std::endl; system("cls"); p = 0; break;
            case 3:
                std::cout << "Sleep: "; if (std::cin >> inp && (inp > 0)) { z = inp; } std::cout << std::endl; system("cls"); p = 0; break;
            case 4:
                std::cout << "[1] Mouse 1\n[2] Mouse 2\n[3] Mouse 1+2" << std::endl << std::endl; if (std::cin >> inp && (inp == 1 || inp == 2 || inp == 3)) { mouseOpt = inp; } std::cout << std::endl; system("cls"); p = 0; break;
            default:
                p = 0; break; // GO BACK TO MAIN (IN ALL CASES)
            }
            break;
        default:
            std::cout << "UI Broke" << std::endl; // IF COMES HERE IDFK WHAT HAPPENED :kek:
            break;
        }
    }   
}

// RECOIL THREAD
void recoil_thread() {
    Mouse mouse; // INIT MOUSE CLASS
    for (;;) {
        while (mouse.isDown(mouseOpt) && recoilEnabled) { // IF MOUSE DOWN AND RECOIL IS TOGGLED ON
            mouse.Move(x, y); // MOVE MOUSE
            Sleep(z); // WAIT TIMER
        }
        Sleep(1); // PLS NO EAT MY CPU :kek:
    }
}
