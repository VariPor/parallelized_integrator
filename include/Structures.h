#pragma once

#include <string>
#include <chrono>

/*
Тип решаемой задачи. На данный момент реализовано только численное интегрирование
*/
enum TaskType
{
    INTEGRATE, // численное интегрирование
    FIND_ZERO  // нахождение нуля функции
};

/*
Входные данные для задачи
*/
struct InputData
{
    double a;                    // нижняя граница отрезка
    double b;                    // верхняя граница отрезка
    std::string function_string; // строка, заадющая функцию
    TaskType task_type;          // тип решаемой задачи
    int threads_num;             // количество используемых нитей исполнения
    int steps_count;             // количество шагов для задачи интегрирования
};

/*
Выходные данные для задачи
*/
struct OutputData
{
    double calculated_result;           // результат вычислений
    std::chrono::microseconds duration; // время вычислений
};