#include <iostream>
#include "ClientManager.h"
#include "Helper.h"
#include "WindowManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    WindowManager windowManager;

    windowManager.getUserInput();

    windowManager.killWindowManager();

    return 0;
}
