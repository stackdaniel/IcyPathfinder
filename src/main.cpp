#include "IcyPathfinderWindow.h"

int main()
{
    const int windowWidth = 832;
    const int windowHeight = 530;

    IcyPathfinderWindow icyPathfinderWindow(windowWidth, windowHeight);

    while(icyPathfinderWindow.isOpen()) {
        icyPathfinderWindow.processEvents();
        icyPathfinderWindow.draw();
    }
    return 0;
}