/* Solutions for Day 1
https://adventofcode.com/2025/day/1

--- Day 1: Secret Entrance ---

The Elves have good news and bad news.

The good news is that they've discovered project management! This has given them the tools they need to prevent their usual Christmas emergency. For example, they now know that the North Pole decorations need to be finished soon so that other critical tasks can start on time.

The bad news is that they've realized they have a different emergency: according to their resource planning, none of them have any time left to decorate the North Pole!

To save Christmas, the Elves need you to finish decorating the North Pole by December 12th.

Collect stars by solving puzzles. Two puzzles will be made available on each day; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

You arrive at the secret entrance to the North Pole base ready to start decorating. Unfortunately, the password seems to have been changed, so you can't get in. A document taped to the wall helpfully explains:

"Due to new security protocols, the password is locked in the safe below. Please see the attached document for the new combination."

The safe has a dial with only an arrow on it; around the dial are the numbers 0 through 99 in order. As you turn the dial, it makes a small click noise as it reaches each number.

The attached document (your puzzle input) contains a sequence of rotations, one per line, which tell you how to open the safe. A rotation starts with an L or R which indicates whether the rotation should be to the left (toward lower numbers) or to the right (toward higher numbers). Then, the rotation has a distance value which indicates how many clicks the dial should be rotated in that direction.

So, if the dial were pointing at 11, a rotation of R8 would cause the dial to point at 19. After that, a rotation of L19 would cause it to point at 0.

Because the dial is a circle, turning the dial left from 0 one click makes it point at 99. Similarly, turning the dial right from 99 one click makes it point at 0.

So, if the dial were pointing at 5, a rotation of L10 would cause it to point at 95. After that, a rotation of R5 could cause it to point at 0.

The dial starts by pointing at 50.

You could follow the instructions, but your recent required official North Pole secret entrance security training seminar taught you that the safe is actually a decoy. The actual password is the number of times the dial is left pointing at 0 after any rotation in the sequence.

For example, suppose the attached document contained the following rotations:

L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
Following these rotations would cause the dial to move as follows:

The dial starts by pointing at 50.
The dial is rotated L68 to point at 82.
The dial is rotated L30 to point at 52.
The dial is rotated R48 to point at 0.
The dial is rotated L5 to point at 95.
The dial is rotated R60 to point at 55.
The dial is rotated L55 to point at 0.
The dial is rotated L1 to point at 99.
The dial is rotated L99 to point at 0.
The dial is rotated R14 to point at 14.
The dial is rotated L82 to point at 32.
Because the dial points at 0 a total of three times during this process, the password in this example is 3.

Analyze the rotations in your attached document. What's the actual password to open the door?

*/

#include <iostream>
#include <assert.h>
#include <fstream>

enum Direction {LEFT, RIGHT};

std::pair<std::vector<Direction>, std::vector<unsigned int>> readPuzzleInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<Direction> directions;
    std::vector<unsigned int> numbers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        char dirChar = line[0];
        Direction dir;
        if (dirChar == 'L') {
            dir = LEFT;
        } else if (dirChar == 'R') {
            dir = RIGHT;
        } else {
            throw std::runtime_error("Invalid direction in " + filename + ", line: " + line);
        }

        unsigned int num = std::stoul(line.substr(1));

        directions.push_back(dir);
        numbers.push_back(num);
    }

    return {directions, numbers};
}

unsigned int rotateLock(unsigned int start,  Direction dir, unsigned int positions) {
    int final_position;
    unsigned int m = 100*(positions/100);
    if (dir == Direction::LEFT) {
        final_position = start - (positions - m);
        if (final_position < 0) {
            return 100 - abs(final_position);
        }
        else {
            return final_position;
        }
    }
    else {
        final_position = start + (positions - m);
        if (final_position >= 100){
            return final_position - 100;
        }
        else {
            return final_position;
        }
    }
}

unsigned int solvePuzzle(unsigned int start, std::string inputfile) {

    auto input = readPuzzleInput(inputfile);

    // Rotate
    unsigned int position = start;
    unsigned int num_zeros = 0;
    for (int i = 0; i < input.first.size(); i++) {
        position = rotateLock(position, input.first[i], input.second[i]);
        if (position == 0) {
            num_zeros = num_zeros + 1;
        }
    }
    return num_zeros;
}

int main() {

    // Check tests for roatateLock pass
    assert(rotateLock(11, Direction::RIGHT, 8) == 19);
    assert(rotateLock(19, Direction::LEFT, 19) == 0);
    assert(rotateLock(0, Direction::LEFT, 1) == 99);
    assert(rotateLock(99, Direction::RIGHT, 1) == 0);
    assert(rotateLock(5, Direction::LEFT, 10) == 95);
    std::cout << "All tests for rotateLock pass" << std::endl;

    // Check test for readPuzzleInput passes
    std::vector<unsigned int> expected_positions = {68, 30, 48, 5, 60, 55, 1, 99, 14, 82};
    std::vector<Direction> expected_dirs = {Direction::LEFT, Direction::LEFT, Direction::RIGHT, Direction::LEFT, Direction::RIGHT,
    Direction::LEFT, Direction::LEFT, Direction::LEFT, Direction::RIGHT, Direction::LEFT};
    auto testinput = readPuzzleInput("testinput_day1.txt");
    assert(testinput.first.size() == 10 && testinput.second.size() == 10);
    for (int i = 0; i < 10; i++) {
        assert(testinput.first[i] == expected_dirs[i]);
        assert(testinput.second[i] == expected_positions[i]);
    }
    std::cout << "Test for readPuzzleInput passes" << std::endl;

    // Check test for solvePuzzle passes
    assert(solvePuzzle(50, "testinput_day1.txt") == 3);
    std::cout << "Test for solvePuzzle passes" << std::endl;

    // Solve the puzzle
    unsigned int solution = solvePuzzle(50, "input_day1.txt");
    std::cout << "The solution for the puzzle is: " << solution << std::endl;
    
    return 0;

}

