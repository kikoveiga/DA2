//
// Created by kikoveiga on 03-05-2023.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Utils.h"
#include <iostream>
#include <algorithm>

class Menu {

private:
    Utils utils;
    std::string command;

public:
    Menu();
    void run();
    void cleanTerminal();
    void enterOption(int n);
    void press0ToContinue();
    void mainMenu();
    void graphsMenu();

};

#endif //DA2_MENU_H
