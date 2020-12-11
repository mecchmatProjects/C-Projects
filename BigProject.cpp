#include "ExponentialDistribution.h"
#include "NormalDistribution.h"
#include "StudentDistribution.h"
#include "FisherDistribution.h"
#include "PoissonDistribution.h"
#include <iostream>

int main()
{
    std::cout << PoisonDistribution() << std::endl;
    std::cout << FisherDistribution() << std::endl;
    std::cout << NormalDistribution() << std::endl;
    std::cout << StudentDistribution() << std::endl;
    std::cout << ExponentialDistribution() << std::endl;
}