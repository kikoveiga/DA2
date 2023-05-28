//
// Created by kikoveiga on 03-05-2023.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

class Menu {

private:
    Utils utils;
    std::string command;

public:
    Menu();
    void run();
    static void cleanTerminal();
    void enterOption(int n);
    void press0ToContinue();
    bool areYouSure();
    void mainMenu();
    void graphsMenu();
    void graphMenu(Graph* graph);
    static void printGraph(Graph* graph);

};

#endif //DA2_MENU_H
