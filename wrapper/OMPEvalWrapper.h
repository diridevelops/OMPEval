#ifndef OMP_EVALWRAPPER_H
#define OMP_EVALWRAPPER_H

#include <HandEvaluator.h>
#include <EquityCalculator.h>

using namespace omp;

class OMPEvalWrapper
{
private:
    EquityCalculator eq;

    char rankToChar(unsigned c);
    char suitToChar(unsigned c);
    // Returns the hand string corresponding to the input combination.
    std::string combToString(std::array<uint8_t, 2> combination);
public:
    // Calculate range vs range odds.
    EquityCalculator::Results calculateOdds(const std::vector<std::string> &handRanges, std::string boardCards = "", std::string deadCards = "",
                          bool enumerateAll = false, double stdevTarget = 5e-5,
                          double updateInterval = 0.2, unsigned threadCount = 0);

    // Hand ranges before card removal.
    std::vector<std::vector<std::string>> originalHandRanges();

    // Hand ranges after card removal.
    std::vector<std::vector<std::string>> handRanges();
};

#endif // OMP_EVALWRAPPER_H
