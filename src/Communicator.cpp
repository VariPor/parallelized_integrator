#include <iostream>
#include <Communicator.h>
#include <stdexcept>
#include "muParser.h"

void Communicator::greet()
{
    std::cout << "Приложение предназанчено для вычисления интегралов." << std::endl;
    std::cout << "Используется метод трапеций." << std::endl;
    std::cout << "Для расчёта необходимо ввести входные данные:" << std::endl;
    std::cout << "  a: double, нижняя граница отрезка интегрирования" << std::endl;
    std::cout << "  b: double, верхняя граница отрезка интегрирования" << std::endl;
    std::cout << "  function_string: интегрируемая функция" << std::endl;
    std::cout << "  threads_num: количество используемых нитей для расчёта" << std::endl;
}

/** Функция для чтения значения double из std::cin.
 *  При неверном диапазоне или формате печатается соответствующее сообщение и предлагается повторный ввод.
 */
double read_double()
{
    std::string input_string;
    std::cin >> input_string;
    bool is_good = false;
    double a;
    while (!is_good)
    {
        try
        {
            a = stod(input_string);
            is_good = true;
        }
        catch (std::invalid_argument)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Неправильный формат. Введите число, например 2.7" << std::endl;
            std::cin >> input_string;
        }
        catch (std::out_of_range)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Число вне диапазона. Введите другое число" << std::endl;
            std::cin >> input_string;
        }
    }
    return a;
}

/**  Функция для чтения значения int из std::cin в диапазоне [min; max].
 *  При неверном диапазоне или формате печатается соответствующее сообщение и предлагается повторный ввод.
 */
int read_int(int min, int max)
{
    std::string input_string;
    std::cin >> input_string;
    bool is_good = false;
    int a;
    while (!is_good)
    {
        try
        {
            a = stoi(input_string);
            if (a > max || a < min)
                throw std::out_of_range("");
            is_good = true;
        }
        catch (std::invalid_argument)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Неправильный формат. Введите число, например, 2" << std::endl;
            std::cin >> input_string;
        }
        catch (std::out_of_range)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Число вне диапазона. Введите число в диапазоне [" << min << ", " << max << "]" << std::endl;
            std::cin >> input_string;
        }
    }
    return a;
}

/** Функция для чтения строки функции из std::cin.
 * Проводится парсинг строки и пробный вызов функции со значением a, в случае неудачи предлагается повторный ввод.
 * Реализация требует ввода функции одной переменной.
 * В качестве буквы для обозначения переменной требуется использовать x.
 */
std::string read_function(double a)
{

    while (true)
        try
        {
            std::string func_str;
            std::cin >> func_str;
            mu::Parser parser;
            parser.DefineVar("x", &a);
            parser.SetExpr(func_str);
            parser.Eval();
            return func_str;
        }
        catch (mu::Parser::exception_type &e)
        {
            std::cout << e.GetMsg() << std::endl;
            std::cout << "Введите функцию для интегрирования (используйте только переменную x): " << std::endl;
        }
}

/** Выводит подсказки для пользователя и собирает входные данные для решаемой задачи.
 * Проверяет корректность введённых данных
 * Выводит информацию о собранных данных
 */
InputData Communicator::get_input_data()
{
    double a, b;
    std::cout << "Введите отрезок интегрирования [a, b]" << std::endl;
    std::cout << "Введите a: " << std::endl;
    a = read_double();
    std::cout << "Введите b: " << std::endl;
    b = read_double();
    std::cout << "Введите функцию для интегрирования (используйте только переменную x): " << std::endl;
    std::string func_str = read_function((a + b) / 2.0);
    std::cout << "Введите количество нитей исполнения: " << std::endl;
    int n = read_int(1, 20);
    std::cout << "Введите количество шагов интегрирования: " << std::endl;
    int steps = read_int(1, INT_MAX);
    std::cout << "Данные для расчёта:" << std::endl;
    std::cout << "Отрезок интегрирования [a, b] = [" << a << ", " << b << "]" << std::endl;
    std::cout << "Функция интегрирования: " << func_str << std::endl;
    std::cout << "Нитей исполнения: " << n << std::endl;
    std::cout << "Шагов интегрирования: " << steps << std::endl;
    return InputData{a, b, func_str, TaskType::INTEGRATE, n, steps};
}

/** Выводит информацию о результате расчёта и затраченом на расчёты времени
 */
void Communicator::print_output(OutputData output_data)
{
    std::cout << "Интеграл равен " << output_data.calculated_result << std::endl;
    std::cout << "Затрачено " << output_data.duration.count() << " микросекунд" << std::endl;
}