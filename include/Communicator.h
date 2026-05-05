#pragma once
#include <iostream>
#include <Structures.h>

/*
Класс предназначен для общения с пользователем через командную строку
*/
class Communicator
{
public:
    void greet();                              // вывод информации про приложение
    InputData get_input_data();                // задание данных для расчёта с проверкой корректности
    void print_output(OutputData output_data); // вывод результата расчёта и времени работы
};