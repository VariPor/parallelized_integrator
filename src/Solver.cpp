#include <Solver.h>
#include "muParser.h"

double Solver::calculate(InputData input_data)
{

    double sum = 0;
    double step = (input_data.b - input_data.a) / (input_data.steps_count + 1);
#pragma omp parallel num_threads(input_data.threads_num) reduction(+ : sum)
    {
        mu::Parser parser;
        parser.DefineVar("x", &input_data.a);
        parser.SetExpr(input_data.function_string);
#pragma omp for
        for (int i = 0; i < input_data.steps_count; ++i)
        {
            double ai = input_data.a + step * i;
            parser.DefineVar("x", &ai);
            double fai = parser.Eval();
            double bi = input_data.a + step * (i + 1);
            parser.DefineVar("x", &bi);
            double fbi = parser.Eval();
            sum += (fai + fbi) / 2.0 * step;
        }
    }
    return sum;
}