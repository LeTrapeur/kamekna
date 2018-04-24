#include "CApplication.hpp"

int main()
{
    CApplication myApp;
    myApp.loadSettings();
    myApp.loadContent();
    myApp.registerStates();
    myApp.run();
}
