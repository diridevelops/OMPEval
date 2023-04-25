#ifndef OMP_WRAPPER_H
#define OMP_WRAPPER_H

#include "HandEvaluator.h"
#include "EquityCalculator.h"

using namespace omp;

class OMPEval
{
private:
    HandEvaluator eval;
    EquityCalculator eq;

    char rankToChar(unsigned c);
    char suitToChar(unsigned c);

public:
    static Hand getHandFromBitmask(uint64_t cards);

    uint16_t evaluateHand(std::string hand);

    // Calculate range vs range odds.
    EquityCalculator::Results calculateOdds(
        const std::vector<std::string> &handRanges, std::string boardCards = "", std::string deadCards = "",
        bool enumerateAll = false, double stdevTarget = 5e-5,
        double updateInterval = 0.2, unsigned threadCount = 0);

    // Returns the hand string corresponding to the input combination.
    std::string combToString(std::array<uint8_t, 2> combination);

    // Combinations before card removal.
    std::vector<std::vector<std::string>> originalCombinations();

    // Combinations after card removal.
    std::vector<std::vector<std::string>> combinations();
};

#endif // OMP_WRAPPER_H
