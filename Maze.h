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

#pragma once

#include <vector>
#include "Cell.h"

#ifndef Maze_H
#define Maze_H

#define X first
#define Y second

class Maze {
private:
	const std::pair<int, int> START_COORDINATES = {0, 0};
	int size;
	std::vector<std::vector<Cell>> map;
	void initialize_map();
	std::vector<std::pair<int, int>> get_neighbors(int x, int y);
	std::vector<std::pair<int, int>> get_unvisted(int x, int y);
	void remove_walls(std::pair<int, int> current_cell,
		std::pair<int, int> next_cell);
	void move_cursor(int x, int y);

public:
	// Constructor
	Maze(int size);

	// Destructor
	~Maze();

	// Generates the maze.
	void generate();

	// Prints a visual representation of the maze to the console.
	void print();
};

#endif // !Maze_H