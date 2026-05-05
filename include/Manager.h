#pragma once
#include <Communicator.h>
#include <Solver.h>

/*
Класс предназначен для координирования действий расчётного ядра
и интерфейса взаимодействия с пользователем.
Также замеряет время работы расчётного ядра
*/
class Manager
{
private:
    Solver solver;             // класс расчётного ядра
    Communicator communicator; // класс для взаимодействия с пользователем

public:
    void run(); // реализация работы приложения
};