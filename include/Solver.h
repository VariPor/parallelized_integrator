#pragma once
#include <Structures.h>

/*
Класс предназначен для выполнения численного интегрирования
*/
class Solver
{
public:
    double calculate(InputData input_data); // интегрирование методом трапеций
};