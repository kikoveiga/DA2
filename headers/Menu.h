//
// Created by kikoveiga on 03-05-2023.
//

#ifndef DA2_MENU_H
#define DA2_MENU_H

#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <chrono>

class Menu {

private:
    Utils utils;
    std::string command;

public:

    /**
     * @brief Menu constructor that initializes the command and calls the run function
     */
    Menu();

    /**
     * @brief Function designed to run the different menus
     */
    void run();


    /**
     * @brief Function that cleans the terminal
     */
    static void cleanTerminal();

    /**
     * @brief Function designed to choose an option in the menus
     * @param n option chosen by user input
     */
    void enterOption(unsigned n);

    /**
     * @brief Function designed to ask the user to continue by pressing 0
     */
    void press0ToContinue();

    /**
     * @brief Function that runs and prints the main menu
     */
    void mainMenu();
    /**
     * @brief Function that runs and prints the graphs menu
     */
    void graphsMenu();

    /**
     * @brief Function that runs and prints a certain graph menu
     * @param graph graph chosen by user input
     */
    void graphMenu(Graph* graph);

    /**
     * @brief Function that prints a graph to a text file
     * @param graph chosen by user input
     */
    static void printGraph(Graph* graph);

    /**
     * @brief Function that runs and prints the algorithms menu
     */
    void algorithmsMenu();

    /**
     * @brief Function that runs and prints a little TSP game menu
     */
    void tSPGameMenu();

    /**
     * @brief Function that runs and prints the TSP game
     * @param graph chosen by user input
     */
    void tSPGame(Graph* graph);
};

#endif //DA2_MENU_H
