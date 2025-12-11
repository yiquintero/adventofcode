/* Solution for Day 4
https://adventofcode.com/2025/day/4

You ride the escalator down to the printing department. They're clearly getting ready for Christmas; they have lots of large rolls of paper everywhere, and there's even a massive printer in the corner (to handle the really big print jobs).

Decorating here will be easy: they can make their own decorations. What you really need is a way to get further into the North Pole base while the elevators are offline.

"Actually, maybe we can help with that," one of the Elves replies when you ask for help. "We're pretty sure there's a cafeteria on the other side of the back wall. If we could break through the wall, you'd be able to keep moving. It's too bad all of our forklifts are so busy moving those big rolls of paper around."

If you can optimize the work the forklifts are doing, maybe they would have time to spare to break through the wall.

The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input) indicating where everything is located.

For example:

..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent positions. If you can figure out which rolls of paper the forklifts can access, they'll spend less time looking and more time breaking down the wall to the cafeteria.

In this example, there are 13 rolls of paper that can be accessed by a forklift (marked with x):

..xx.xx@x.
x@@.@.@.@@
@@@@@.x.@@
@.@@@@..@.
x@.@@@@.@x
.@@@@@@@.@
.@.@.@.@@@
x.@@@.@@@@
.@@@@@@@@.
x.x.@@@.x.
Consider your complete diagram of the paper roll locations. How many rolls of paper can be accessed by a forklift?

*/

#include <fstream>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <numeric>

std::vector<std::vector<unsigned int>> readPuzzleInput(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::vector<std::vector<unsigned int>> result;
    std::vector<unsigned int> l;
    std::string line;
    while (std::getline(file, line)) {
        l.push_back(0); // padding for easy processing
        for (auto c : line) {
            unsigned int x = (c == '.') ? 0 : 1;
            l.push_back(x);
        }
        l.push_back(0); // padding
        result.push_back(l);
        l.clear();
    }
    // Add row of zeroes top and bottom - assumes all lines are the same size
    std::vector<unsigned int> padding(result[0].size(), 0);
    auto i = result.begin();
    i = result.insert(i, padding);
    result.push_back(padding);

    return result;
}

unsigned int countAccessibleRolls(std::vector<unsigned int>& top,
     std::vector<unsigned int>& row, std::vector<unsigned int>& bottom) {
    assert(row.size() == top.size() && row.size() == bottom.size());
    
    unsigned long int result = 0;
    for (int i = 1; i < row.size() - 1; i++) {
        if (row[i]){
            int nr = row[i-1] + row[i+1] + top[i-1] + top[i] + top[i+1] + bottom[i-1] + bottom[i] + bottom[i+1];
            if (nr < 4) result++;
        }
    }
    return result;
}

unsigned int solvePuzzle(std::string inputfile) {
    auto grid = readPuzzleInput(inputfile);

    unsigned int solution = 0;
    for (int i = 1; i < grid.size() - 1; i++) {
        solution = solution + countAccessibleRolls(grid[i-1], grid[i], grid[i+1]);
    }
    return solution;
}


int main() {

    // Test readPuzzleInput
    auto actual = readPuzzleInput("testinput_day4.txt");
    assert(actual.size() == 12);
    assert((actual[1] == std::vector<unsigned int>{0,0,0,1,1,0,1,1,1,1,0,0}));
    assert((actual[2] == std::vector<unsigned int>{0,1,1,1,0,1,0,1,0,1,1,0}));
    assert((actual[3] == std::vector<unsigned int>{0,1,1,1,1,1,0,1,0,1,1,0}));
    assert((actual[4] == std::vector<unsigned int>{0,1,0,1,1,1,1,0,0,1,0,0}));
    assert((actual[5] == std::vector<unsigned int>{0,1,1,0,1,1,1,1,0,1,1,0}));
    assert((actual[6] == std::vector<unsigned int>{0,0,1,1,1,1,1,1,1,0,1,0}));
    assert((actual[7] == std::vector<unsigned int>{0,0,1,0,1,0,1,0,1,1,1,0}));
    assert((actual[8] == std::vector<unsigned int>{0,1,0,1,1,1,0,1,1,1,1,0}));
    assert((actual[9] == std::vector<unsigned int>{0,0,1,1,1,1,1,1,1,1,0,0}));
    assert((actual[10] == std::vector<unsigned int>{0,1,0,1,0,1,1,1,0,1,0,0}));
    std::cout << "All tests for readPuzzleInput pass!" << std::endl;
    
    // Tests countAccessibleRolls
    assert(countAccessibleRolls(actual[0], actual[1], actual[2]) == 5);
    assert(countAccessibleRolls(actual[1], actual[2], actual[3]) == 1);
    assert(countAccessibleRolls(actual[2], actual[3], actual[4]) == 1);
    assert(countAccessibleRolls(actual[3], actual[4], actual[5]) == 0);
    assert(countAccessibleRolls(actual[4], actual[5], actual[6]) == 2);
    assert(countAccessibleRolls(actual[5], actual[6], actual[7]) == 0);
    assert(countAccessibleRolls(actual[6], actual[7], actual[8]) == 0);
    assert(countAccessibleRolls(actual[7], actual[8], actual[9]) == 1);
    assert(countAccessibleRolls(actual[8], actual[9], actual[10]) == 0);
    assert(countAccessibleRolls(actual[9], actual[10], actual[11]) == 3);
    std::cout << "All tests for countAccessibleRolls pass!" << std::endl;

    unsigned long int solution = solvePuzzle("input_day4.txt");
    std::cout << "The solution is: " << solution << std::endl;

    return 0;
}