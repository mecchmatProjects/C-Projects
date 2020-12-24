//student_t_distribution
#include <iostream>
#include <random>

int main()
{
    const int nrolls = 10000;  // number of experiments
    const int nstars = 100;    // maximum number of stars to distribute

    // intervals definitions:
    const int nintervals = 12;
    const double first = -3.0;
    const double span = 0.5;

    std::default_random_engine generator;
    std::student_t_distribution<double> distribution(10.0);

    int p[nintervals] = {};

    for (int i = 0; i < nrolls; ++i) {
        double number = distribution(generator);
        if ((number >= first) && (number < first + nintervals * span))
            ++p[int((number - first) / span)];
    }

    std::cout << "student_t_distribution: " << std::endl;
    std::cout << std::fixed; std::cout.precision(1);

    for (int i = 0; i < nintervals; ++i) {
        std::cout.width(4); std::cout << (first + i * span) << "..";
        std::cout.width(4); std::cout << (first + (i + 1) * span) << ": ";
        std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
    }

    return 0;
}