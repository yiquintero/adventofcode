/*
--- Day 2: Gift Shop ---

You get inside and take the elevator to its only other stop: the gift shop. "Thank you for visiting the North Pole!" gleefully exclaims a nearby sign. You aren't sure who is even allowed to visit the North Pole, but you know you can access the lobby through here, and from there you can access the rest of the North Pole base.

As you make your way through the surprisingly extensive selection, one of the clerks recognizes you and asks for your help.

As it turns out, one of the younger Elves was playing on a gift shop computer and managed to add a whole bunch of invalid product IDs to their gift shop database! Surely, it would be no trouble for you to identify the invalid product IDs for them, right?

They've even checked most of the product ID ranges already; they only have a few product ID ranges (your puzzle input) that you'll need to check. For example:

11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
1698522-1698528,446443-446449,38593856-38593862,565653-565659,
824824821-824824827,2121212118-2121212124
(The ID ranges are wrapped here for legibility; in your input, they appear on a single long line.)

The ranges are separated by commas (,); each range gives its first ID and last ID separated by a dash (-).

Since the young Elf was just doing silly patterns, you can find the invalid IDs by looking for any ID which is made only of some sequence of digits repeated twice. So, 55 (5 twice), 6464 (64 twice), and 123123 (123 twice) would all be invalid IDs.

None of the numbers have leading zeroes; 0101 isn't an ID at all. (101 is a valid ID that you would ignore.)

Your job is to find all of the invalid IDs that appear in the given ranges. In the above example:

11-22 has two invalid IDs, 11 and 22.
95-115 has one invalid ID, 99.
998-1012 has one invalid ID, 1010.
1188511880-1188511890 has one invalid ID, 1188511885.
222220-222224 has one invalid ID, 222222.
1698522-1698528 contains no invalid IDs.
446443-446449 has one invalid ID, 446446.
38593856-38593862 has one invalid ID, 38593859.
The rest of the ranges contain no invalid IDs.
Adding up all the invalid IDs in this example produces 1227775554.

What do you get if you add up all of the invalid IDs?

*/

#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <numeric>

std::vector<std::pair<unsigned long int, unsigned long int>> readPuzzleInput(std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Read file
    std::string line;
    std::getline(file, line);     // read the single, long line

    std::vector<std::pair<unsigned long int, unsigned long int>> ranges;

    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, ',')) {   // split by commas
        // item looks like "1517536-173648713"
        auto dashPos = item.find('-');
        if (dashPos == std::string::npos) {
            throw std::runtime_error("Invalid item: " + item);
        }
        unsigned long int first  = std::stoul(item.substr(0, dashPos));
        unsigned long int second = std::stoul(item.substr(dashPos + 1));

        ranges.emplace_back(first, second);
    }

    return ranges;
}

std::vector<unsigned long int> findInvalidIDs(unsigned long int start, unsigned long int end) {
    assert(end > start);

    std::vector<unsigned long int> invalidIDs;
    for (long int i = start; i <= end; i++) {
        std::string istr = std::to_string(i);
        if(istr.size() % 2 != 0){
             continue;
        }
        auto mid = istr.size()/2;
        if(istr.substr(0,mid) == istr.substr(mid)) {
            invalidIDs.push_back(i);
        }
    }
    return invalidIDs;
}

unsigned long int solvePuzzle(std::string inputfile) {
    auto ranges = readPuzzleInput(inputfile);
    unsigned long int result = 0;
    std::vector<unsigned long int> wrongIDs;
    for (auto r : ranges) {
        wrongIDs = findInvalidIDs(r.first, r.second);
        for (auto i : wrongIDs) {
            result = result + i; 
        }
        wrongIDs.clear();
    }
    return result;
}

int main() {

    // Tests for readPuzzleInput
    auto ranges = readPuzzleInput("testinput_day2.txt");
    assert(ranges.size() == 11);
    assert(ranges[0].first == 11 && ranges[0].second == 22);
    assert(ranges[1].first == 95 && ranges[1].second == 115);
    assert(ranges[9].first == 824824821 && ranges[9].second == 824824827);
    assert(ranges[10].first == 2121212118 && ranges[10].second == 2121212124);
    std::cout << "All tests for readPuzzleInput pass" << std::endl;

    // Tests for findInvalidIDs
    assert((findInvalidIDs(11, 22) == std::vector<unsigned long int>{11,22}));
    assert((findInvalidIDs(95, 115) == std::vector<unsigned long int>{99}));
    assert((findInvalidIDs(998, 1012) == std::vector<unsigned long int>{1010}));
    assert((findInvalidIDs(1188511880, 1188511890) == std::vector<unsigned long int>{1188511885}));
    assert((findInvalidIDs(222220, 222224) == std::vector<unsigned long int>{222222}));
    assert((findInvalidIDs(1698522, 1698528).size() == 0));
    assert((findInvalidIDs(446443, 446449) == std::vector<unsigned long int>{446446}));
    assert((findInvalidIDs(38593856, 38593862) == std::vector<unsigned long int>{38593859}));
    std::cout << "All tests for findInvalidIDs pass" << std::endl;

    assert(solvePuzzle("testinput_day2.txt") == 1227775554);
    std::cout << "Test for solvePuzzle passes" << std::endl;

    unsigned long int solution = solvePuzzle("input_day2.txt");
    std::cout << "The solution is: " << solution << std::endl;

    return 0;    

}