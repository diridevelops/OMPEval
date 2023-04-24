#include "OMPEvalWrapper.h"

EquityCalculator::Results
OMPEval::calculateOdds(const std::vector<std::string> &handRanges, std::string boardCards, std::string deadCards,
                       bool enumerateAll, double stdevTarget, double updateInterval, unsigned threadCount)
{
    std::vector<CardRange> ranges = {};
    for (std::string r : handRanges)
        ranges.push_back(CardRange(r));

    uint64_t board = CardRange::getCardMask(boardCards);
    uint64_t dead = CardRange::getCardMask(deadCards);

    eq.start(ranges, board, dead, enumerateAll, stdevTarget, nullptr,
             updateInterval, threadCount);
    eq.wait();
    return eq.getResults();
}

std::string
OMPEval::combToString(std::array<uint8_t, 2> combination)
{
    std::string hand = "";
    uint8_t suits[] = {0, 1, 2, 3};
    for (uint8_t c : combination)
    {
        for (uint8_t s : suits)
        {
            if ((c - s) % 4 == 0)
            {
                hand += std::string(1, std::toupper(rankToChar((c - s) / 4))) + std::string(1, suitToChar(s));
            }
        }
    }
    return hand;
}

std::vector<std::vector<std::string>>
OMPEval::originalHandRanges()
{
    std::vector<std::vector<std::string>> rangesString;
    std::vector<std::string> rString = {};
    auto ranges = eq.originalHandRanges();
    for (auto r : ranges)
    {
        for (auto c : r.combinations())
        {
            rString.push_back(combToString(c));
        }
        rangesString.push_back(rString);
        rString.clear();
    }
    return rangesString;
}

std::vector<std::vector<std::string>>
OMPEval::handRanges()
{
    std::vector<std::vector<std::string>> rangesString;
    std::vector<std::string> rString = {};
    auto ranges = eq.handRanges();
    for (auto r : ranges)
    {
        for (auto c : r)
        {
            rString.push_back(combToString(c));
        }
        rangesString.push_back(rString);
        rString.clear();
    }
    return rangesString;
}

char OMPEval::rankToChar(unsigned c)
{
    switch (c)
    {
    case 12:
        return 'a';
    case 11:
        return 'k';
    case 10:
        return 'q';
    case 9:
        return 'j';
    case 8:
        return 't';
    case 7:
        return '9';
    case 6:
        return '8';
    case 5:
        return '7';
    case 4:
        return '6';
    case 3:
        return '5';
    case 2:
        return '4';
    case 1:
        return '3';
    case 0:
        return '2';
    default:
        return ' ';
    }
}

char OMPEval::suitToChar(unsigned c)
{
    switch (c)
    {
    case 0:
        return 's';
    case 1:
        return 'h';
    case 2:
        return 'c';
    case 3:
        return 'd';
    default:
        return ' ';
    }
}
