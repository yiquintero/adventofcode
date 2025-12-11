/* Solutions for Day 3
https://adventofcode.com/2025/day/3

--- Day 3: Lobby ---

You descend a short staircase, enter the surprisingly vast lobby, and are quickly cleared by the security checkpoint. When you get to the main elevators, however, you discover that each one has a red light above it: they're all offline.

"Sorry about that," an Elf apologizes as she tinkers with a nearby control panel. "Some kind of electrical surge seems to have fried them. I'll try to get them online soon."

You explain your need to get further underground. "Well, you could at least take the escalator down to the printing department, not that you'd get much further than that without the elevators working. That is, you could if the escalator weren't also offline."

"But, don't worry! It's not fried; it just needs power. Maybe you can get it running while I keep working on the elevators."

There are batteries nearby that can supply emergency power to the escalator for just such an occasion. The batteries are each labeled with their joltage rating, a value from 1 to 9. You make a note of their joltage ratings (your puzzle input). For example:

987654321111111
811111111111119
234234234234278
818181911112111
The batteries are arranged into banks; each line of digits in your input corresponds to a single bank of batteries. Within each bank, you need to turn on exactly two batteries; the joltage that the bank produces is equal to the number formed by the digits on the batteries you've turned on. For example, if you have a bank like 12345 and you turn on batteries 2 and 4, the bank would produce 24 jolts. (You cannot rearrange batteries.)

You'll need to find the largest possible joltage each bank can produce. In the above example:

In 987654321111111, you can make the largest joltage possible, 98, by turning on the first two batteries.
In 811111111111119, you can make the largest joltage possible by turning on the batteries labeled 8 and 9, producing 89 jolts.
In 234234234234278, you can make 78 by turning on the last two batteries (marked 7 and 8).
In 818181911112111, the largest joltage you can produce is 92.
The total output joltage is the sum of the maximum joltage from each bank, so in this example, the total output joltage is 98 + 89 + 78 + 92 = 357.

There are many batteries in front of you. Find the maximum joltage possible from each bank; what is the total output joltage?
*/

#include <iostream>
#include <fstream>
#include <assert.h>
#include <algorithm>

std::vector<std::vector<unsigned int>> readPuzzleInput(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<std::vector<unsigned int>> result;
    std::vector<unsigned int> bank;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        // Read bank
        for (int i = 0; i < line.size(); i++) {
            bank.push_back(std::stoi(line.substr(i,1)));
        }
        // Save bank
        result.push_back(bank);
        bank.clear();
    }
    return result;
}

unsigned int getLargestJoltageInBank(std::vector<unsigned int> bank) {
    auto maxiter = std::max_element(bank.begin(), bank.end());
    auto maxindex = std::distance(bank.begin(), maxiter);

    if (maxindex == bank.size() - 1) {
        auto otherindex = std::distance(bank.begin(), std::max_element(bank.begin(), maxiter));
        return (10*bank[otherindex] + bank[maxindex]);
    }
    else {
        auto otheriter = std::max_element(std::next(maxiter), bank.end());
        auto otherindex = std::distance(maxiter, otheriter) + maxindex;
        return (10*bank[maxindex] + bank[otherindex]);
    }
}

unsigned int solvePuzzle(std::string inputfile) {
    auto banks = readPuzzleInput(inputfile);
    unsigned long int solution = 0;
    for (auto b : banks) {
        solution = solution + getLargestJoltageInBank(b);
    }
    return solution;
}

int main(){

    // Test readPuzzleInput
    auto actual = readPuzzleInput("testinput_day3.txt");
    assert(actual.size() == 4);
    assert((actual[0] == std::vector<unsigned int>{9,8,7,6,5,4,3,2,1,1,1,1,1,1,1}));
    assert((actual[1] == std::vector<unsigned int>{8,1,1,1,1,1,1,1,1,1,1,1,1,1,9}));
    assert((actual[2] == std::vector<unsigned int>{2,3,4,2,3,4,2,3,4,2,3,4,2,7,8}));
    assert((actual[3] == std::vector<unsigned int>{8,1,8,1,8,1,9,1,1,1,1,2,1,1,1}));
    std::cout << "All tests for readPuzzleInput pass!" << std::endl;

    // Test getLargestJoltageInBank
    assert(getLargestJoltageInBank({9,8,7,6,5,4,3,2,1,1,1,1,1,1,1}) == 98);
    assert(getLargestJoltageInBank({8,1,1,1,1,1,1,1,1,1,1,1,1,1,9}) == 89);
    assert(getLargestJoltageInBank({2,3,4,2,3,4,2,3,4,2,3,4,2,7,8}) == 78);
    assert(getLargestJoltageInBank({8,1,8,1,8,1,9,1,1,1,1,2,1,1,1}) == 92);
    std::cout << "All tests for getLargestJoltageInBank pass!" << std::endl;

    // Test for Solve Puzzle
    assert(solvePuzzle("testinput_day3.txt") == 357);
    std::cout << "The tests for solvePuzzle passes!" << std::endl;

    unsigned long int solution = solvePuzzle("input_day3.txt");
    std::cout << "The solution is: " << solution << std::endl;

    return 0;
}