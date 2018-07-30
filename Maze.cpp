/*
 * Copyright 2018 Ethan P. Genser
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <list>
#include "Maze.h"
#include <ctime>
#include <Windows.h>

// Private:
void Maze::initialize_map() {
	map = {};

	// Creates a 2-D vector of default Cells.
	for (int y = 0; y < size; y++) {
		map.push_back(std::vector<Cell>{});
		for (int x = 0; x < size; x++) {
			map[y].push_back(Cell());
		}
	}
}
std::vector<std::pair<int, int>> Maze::get_neighbors(int x, int y) {
	std::vector<std::pair<int, int>> neighbors = {};

	// Gets western neighbor if it exists.
	if (x > 0) {
		neighbors.push_back(std::pair<int, int>{x - 1, y});
	}
	// Gets eastern neighbor if it exists.
	if (x < size - 1) {
		neighbors.push_back(std::pair<int, int>{x + 1, y});
	}
	// Gets northern neighbor if it exists.
	if (y > 0) {
		neighbors.push_back(std::pair<int, int>{x, y - 1});
	}
	// Gets southern neighbor if it exists.
	if (y < size - 1) {
		neighbors.push_back(std::pair<int, int>{x, y + 1});
	}

	return neighbors;
}
std::vector<std::pair<int, int>> Maze::get_unvisted(int x, int y) {
	std::vector<std::pair<int, int>> unvisted = {};
	std::vector<std::pair<int, int>> neighbors = get_neighbors(x, y);

	// Gets all neighbors that are unvisted.
	for (std::pair<int, int> neighbor : neighbors) {
		if (!map[neighbor.X][neighbor.Y].visited) {
			unvisted.push_back(neighbor);
		}
	}

	return unvisted;
}
void Maze::remove_walls(std::pair<int, int> current_cell,
	std::pair<int, int> next_cell) {
	// Finds the movement offset.
	std::pair<int, int> direction = { next_cell.X - current_cell.X,
		next_cell.Y - current_cell.Y };

	// Moving up
	if (direction == std::pair<int, int>{0, -1}) {
		map[current_cell.X][current_cell.Y].top_wall = false;
		map[next_cell.X][next_cell.Y].bottom_wall = false;
	}
	// Moving down
	if (direction == std::pair<int, int>{0, 1}) {
		map[current_cell.X][current_cell.Y].bottom_wall = false;
		map[next_cell.X][next_cell.Y].top_wall = false;
	}
	// Moving left
	if (direction == std::pair<int, int>{-1, 0}) {
		map[current_cell.X][current_cell.Y].left_wall = false;
		map[next_cell.X][next_cell.Y].right_wall = false;
	}
	// Moving right
	if (direction == std::pair<int, int>{1, 0}) {
		map[current_cell.X][current_cell.Y].right_wall = false;
		map[next_cell.X][next_cell.Y].left_wall = false;
	}
}
void Maze::move_cursor(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		COORD{ (short)x, (short)y });
}

// Public:
Maze::Maze(int size) {
	if (size > 1) {
		this->size = size;
	}
	else {
		throw std::invalid_argument("Invalid size argument.");
	}
	initialize_map();
	srand(time(NULL));
}
Maze::~Maze() {
}
void Maze::generate() {

	int unvisited = size * size;

	std::stack<std::pair<int, int>, std::list<std::pair<int, int>>> cell_stack =
		std::stack<std::pair<int, int>, std::list<std::pair<int, int>>>();

	// current_cell is set to the deafault start position.
	std::pair<int,int> current_cell =
		{START_COORDINATES.X, START_COORDINATES.Y};
	map[current_cell.X][current_cell.Y].visited = true;
	unvisited--;
	
	while (unvisited > 0) {

		// Finds the current_cell's unvisited neighbors.
		std::vector<std::pair<int, int>> unvisited_neighbors =
			get_unvisted(current_cell.X, current_cell.Y);

		if (unvisited_neighbors.size() > 0) {

			// Randomly selects one of the unvisited neighbors of current_cell.
			std::pair<int, int> next_cell =
				unvisited_neighbors[rand() % unvisited_neighbors.size()];

			// Moves current_cell to the top of the cell_stack.
			cell_stack.emplace(current_cell);

			// Removes walls between current_cell and next_cell.
			remove_walls(current_cell, next_cell);

			// Moves current_cell to next_cell.
			current_cell = next_cell;
			map[current_cell.X][current_cell.Y].visited = true;
			unvisited--;
		}
		else {
			// Backtracking
			current_cell = cell_stack.top();
			cell_stack.pop();
		}
	}
}
void Maze::print() {
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			int left = x * 4;
			int top = y * 2;

			// Prints corners.
			move_cursor(left, top);
			std::cout << "+   +";
			move_cursor(left, top + 2);
			std::cout << "+   +";

			// Prints top wall.
			if (map[x][y].top_wall) {
				move_cursor(left + 1, top);
				std::cout << "---";
			}

			// Prints bottom wall.
			if (map[x][y].bottom_wall) {
				move_cursor(left + 1, top + 2);
				std::cout << "---";
			}

			// Prints left wall.
			if (map[x][y].left_wall) {
				move_cursor(left, top + 1);
				std::cout << "|";
			}

			// Prints right wall.
			if (map[x][y].right_wall) {
				move_cursor(left + 4, top + 1);
				std::cout << "|";
			}

			// Prints start marker.
			if (std::pair<int, int>{x, y} == START_COORDINATES) {
				move_cursor(left + 2, top + 1);
				std::cout << "S";
			}

			// Prints finish marker.
			if (x == size - 1 && y == size - 1) {
				move_cursor(left + 2, top + 1);
				std::cout << "F";
				move_cursor(0, top + 4);
			}
		}
	}
}