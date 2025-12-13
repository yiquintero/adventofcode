/* Solutions for Day 5
https://adventofcode.com/2025/day/5

As the forklifts break through the wall, the Elves are delighted to discover that there was a cafeteria on the other side after all.

You can hear a commotion coming from the kitchen. "At this rate, we won't have any time left to put the wreaths up in the dining hall!" Resolute in your quest, you investigate.

"If only we hadn't switched to the new inventory management system right before Christmas!" another Elf exclaims. You ask what's going on.

The Elves in the kitchen explain the situation: because of their complicated new inventory management system, they can't figure out which of their ingredients are fresh and which are spoiled. When you ask how it works, they give you a copy of their database (your puzzle input).

The database operates on ingredient IDs. It consists of a list of fresh ingredient ID ranges, a blank line, and a list of available ingredient IDs. For example:

3-5
10-14
16-20
12-18

1
5
8
11
17
32
The fresh ID ranges are inclusive: the range 3-5 means that ingredient IDs 3, 4, and 5 are all fresh. The ranges can also overlap; an ingredient ID is fresh if it is in any range.

The Elves are trying to determine which of the available ingredient IDs are fresh. In this example, this is done as follows:

Ingredient ID 1 is spoiled because it does not fall into any range.
Ingredient ID 5 is fresh because it falls into range 3-5.
Ingredient ID 8 is spoiled.
Ingredient ID 11 is fresh because it falls into range 10-14.
Ingredient ID 17 is fresh because it falls into range 16-20 as well as range 12-18.
Ingredient ID 32 is spoiled.
So, in this example, 3 of the available ingredient IDs are fresh.

Process the database file from the new inventory management system. How many of the available ingredient IDs are fresh?

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

std::pair<std::vector<std::pair<unsigned long int, unsigned long int>>, std::vector<unsigned long int>> readPuzzleInput(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<std::pair<unsigned long int, unsigned long int>> ranges;
    std::vector<unsigned long int> IDs;
    bool reading_ranges = true;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            reading_ranges = false;
            continue;
        }

        if(reading_ranges){
            auto dashPos = line.find('-');
            if (dashPos == std::string::npos) throw std::runtime_error("Invalid range: " + line);
            ranges.emplace_back(std::stoul(line.substr(0,dashPos)), std::stoul(line.substr(dashPos+1)));
        }
        else {
            IDs.push_back(std::stoul(line));
        }
    }
    return {ranges, IDs};
}


unsigned int countFreshProducts(const std::vector<std::pair<unsigned long int, unsigned long int>>& ranges, const std::vector<unsigned long int> IDs) {
    unsigned int freshProducts = 0;
    for (auto id : IDs) {
        for (auto range : ranges) {
            if (id >= range.first && id <= range.second){
                freshProducts++;
                std::cout << "Product "<<id<<" found!" << std::endl;
                break;
            }
        }
    }
    return freshProducts;
}

unsigned int solvePuzzle(std::string inputfile) {
    auto testinput = readPuzzleInput(inputfile);
    return countFreshProducts(testinput.first, testinput.second);
}

int main() {

    auto testinput = readPuzzleInput("testinput_day5.txt");
    auto test_ranges = std::move(testinput.first);
    auto test_IDs = std::move(testinput.second);
    std::vector<std::pair<unsigned long int, unsigned long int>> expected_ranges = {
        {3,5}, {10,14}, {16,20}, {12,18}
    };
    std::vector<unsigned long int> expected_IDs = {1, 5, 8, 11, 17, 32};
    assert(expected_ranges.size() == test_ranges.size());
    assert(expected_ranges == test_ranges);
    assert(expected_IDs.size() == test_IDs.size());
    assert(expected_IDs == test_IDs);
    std::cout << "All tests pass for readPuzzleInput" << std::endl;
    
    assert(solvePuzzle("testinput_day5.txt") == 3);
    std::cout << "Test for solvePuzzle passes" << std::endl;

    unsigned int solution = solvePuzzle("input_day5.txt");
    std::cout << "The solution is: " << solution << std::endl;

    return 0;
}