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
#include "Maze.h"
#include <iostream>
#include <vector>
#include <Windows.h>

int main() {

	int size = 0;

	// Asks user for the maze size.
	std::cout << "Enter maze size: ";
	std::cin >> size;
	getchar();
	
	// Ensures the user does not enter a size value less that 2.
	if (size > 1) {
		Maze maze = Maze(size);
		maze.generate();
		maze.print();

		std::cout << "Press [enter] to exit...";
	}
	else {
		std::cout << "Error: Size must be larger than 1."
			<< std::endl
			<< std::endl;
	}

	// Pauses before ending execution.
	getchar();
	return 0;
}