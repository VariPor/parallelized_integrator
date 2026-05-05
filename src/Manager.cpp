#include <Manager.h>
#include <chrono>

void Manager::run()
{
    communicator.greet();
    InputData input_data = communicator.get_input_data();
    auto start = std::chrono::high_resolution_clock::now();
    double result = solver.calculate(input_data);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    OutputData output_data{result, duration};
    communicator.print_output(output_data);
}