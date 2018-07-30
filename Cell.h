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

#ifndef Cell_H
#define Cell_H

struct Cell
{
public:
	Cell();
	~Cell();
	bool visited = false;
	bool top_wall = true;
	bool bottom_wall = true;
	bool left_wall = true;
	bool right_wall = true;
};

#endif // !Cell_H