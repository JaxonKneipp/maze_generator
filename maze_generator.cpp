#include <iostream>
#include <stdlib.h>

using namespace std;

const int maze_side_length = 111;
const int amount_of_grid_squares = ((maze_side_length - 1) / 2) * ((maze_side_length - 1) / 2);

int current_grid_coordinates[2] = { 1, 1 };
int visited_grid_squares[amount_of_grid_squares][2];
int last_visited_grid_squares_index = 2;
int maze_bit_map[maze_side_length][maze_side_length];

void print_bitmap() {

	for (int row = 0; row < maze_side_length; row++) {

		for (int column = 0; column < maze_side_length; column++) {

			if (maze_bit_map[row][column] == 1) {

				cout << (char)219 << (char)219;

			}
			else {

				cout << "  ";

			}

		}

		cout << "\n";

	}

}

bool all_squares_visited() {

	for (int index = 0; index < amount_of_grid_squares; index++) {

		if (visited_grid_squares[index][0] == 0 && visited_grid_squares[index][1] == 0) {

			return false;

		}

	}

	return true;

}

bool visited_grid_square(int grid_coordinates[2]) {

	for (int index = 0; index < amount_of_grid_squares; index++) {

		if (visited_grid_squares[index][0] == grid_coordinates[0] && visited_grid_squares[index][1] == grid_coordinates[1]) {

			return true;

		}

	}

	return false;

}

void set_up_bit_map() {

	for (int row = 0; row < maze_side_length; row++) {

		for (int column = 0; column < maze_side_length; column++) {

			switch (row % 2) {

			case 0:

				maze_bit_map[row][column] = 1;

				break;

			default:

				if (column % 2 == 0) {

					maze_bit_map[row][column] = 1;

				}
				else {

					maze_bit_map[row][column] = 0;

				}

			}

		}

	}

}

bool check_move(char direction, int grid_coords[2]) {

	switch (direction) {

	case 'u':

		if (grid_coords[0] - 2 > 0) {

			int proposed_new_grid_square[2] = { grid_coords[0] - 2, grid_coords[1] };

			if (visited_grid_square(proposed_new_grid_square)) {

				return false;

			}

			return true;

		}
		return false;

	case 'd':


		if (grid_coords[0] + 2 < maze_side_length-1) {

			int proposed_new_grid_square[2] = { grid_coords[0] + 2, grid_coords[1] };

			if (visited_grid_square(proposed_new_grid_square)) {

				return false;

			}


			return true;

		}

		return false;

	case 'l':

		if (grid_coords[1] - 2 > 0) {

			int proposed_new_grid_square[2] = { grid_coords[0], grid_coords[1] - 2 };

			if (visited_grid_square(proposed_new_grid_square)) {

				return false;

			}

			return true;

		}

		return false;

	case 'r':

		if (grid_coords[1] + 2 < maze_side_length - 1) {

			int proposed_new_grid_square[2] = { grid_coords[0], grid_coords[1] + 2 };

			if (visited_grid_square(proposed_new_grid_square)) {

				return false;

			}

			return true;

		}

		return false;

	default:

		break;

	}

	return false;

}

void move(char direction) {

	switch (direction) {

	case 'u':

		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0]-1][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0]-2][current_grid_coordinates[1]] = 0;

		current_grid_coordinates[0] -= 2;

		visited_grid_squares[0][0] = current_grid_coordinates[0];
		visited_grid_squares[0][1] = current_grid_coordinates[1];

		break;

	case 'd':

		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0] + 1][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0] + 2][current_grid_coordinates[1]] = 0;

		current_grid_coordinates[0] += 2;

		break;

	case 'l':

		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]-1] = 0;
		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]-2] = 0;

		current_grid_coordinates[1] -= 2;

		break;

	case 'r':

		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1]] = 0;
		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1] + 1] = 0;
		maze_bit_map[current_grid_coordinates[0]][current_grid_coordinates[1] + 2] = 0;

		current_grid_coordinates[1] += 2;

		break;

	default:

		break;

	}

	visited_grid_squares[last_visited_grid_squares_index][0] = current_grid_coordinates[0];
	visited_grid_squares[last_visited_grid_squares_index][1] = current_grid_coordinates[1];
	last_visited_grid_squares_index += 1;

}

bool direction_checked(char checked_directions[4], char direction) {

	for (int index = 0; index < 4; index++) {

		if (checked_directions[index] == direction) {

			return true;

		}

	}

	return false;

}

void draw_until_dead_end() {

	bool dead_end_reached = false;

	while (dead_end_reached != true) {

		char unchecked_directions[4] = { 'u', 'd', 'l', 'r' };
		char checked_directions[4];
		int checked_directions_index = 0;
		int random_index = rand() % 4;

		for (int i = 1; i <= 4; i++) {

			if (check_move(unchecked_directions[random_index], current_grid_coordinates)) {

				move(unchecked_directions[random_index]);

				break;

			}
			else if (checked_directions_index != 3) {

				checked_directions[checked_directions_index] = unchecked_directions[random_index];
				checked_directions_index += 1;

				random_index = rand() % 4;

				while (direction_checked(checked_directions, unchecked_directions[random_index])) {

					random_index = rand() % 4;

				}

			}


			if (i == 4) {

				dead_end_reached = true;

			}

		}

	}

	print_bitmap();

}

void hunt_for_joint() {

	for (int row = 1; row < maze_side_length; row++) {

		for (int column = 1; column < maze_side_length; column++) {

			int current_grid_square_coords[2] = { row, column };

			if (!visited_grid_square(current_grid_square_coords)) {

				int current_grid_square_coords_duplicate[2];
				current_grid_square_coords_duplicate[0] = current_grid_square_coords[0];
				current_grid_square_coords_duplicate[1] = current_grid_square_coords[1];

				current_grid_square_coords_duplicate[0] = current_grid_square_coords_duplicate[0] - 2;

				if (!check_move('u', current_grid_square_coords) && visited_grid_square(current_grid_square_coords_duplicate)) {

					maze_bit_map[current_grid_square_coords[0] - 1][current_grid_square_coords[1]] = 0;
					current_grid_coordinates[0] = current_grid_square_coords[0];
					current_grid_coordinates[1] = current_grid_square_coords[1];
					visited_grid_squares[last_visited_grid_squares_index][0] = current_grid_coordinates[0];
					visited_grid_squares[last_visited_grid_squares_index][1] = current_grid_coordinates[1];
					last_visited_grid_squares_index += 1;

					return;

				}

				current_grid_square_coords_duplicate[0] = current_grid_square_coords_duplicate[0] + 2;

				current_grid_square_coords_duplicate[0] = current_grid_square_coords_duplicate[0] + 2;

				if (!check_move('d', current_grid_square_coords) && visited_grid_square(current_grid_square_coords_duplicate)) {

					maze_bit_map[current_grid_square_coords[0] + 1][current_grid_square_coords[1]] = 0;
					current_grid_coordinates[0] = current_grid_square_coords[0];
					current_grid_coordinates[1] = current_grid_square_coords[1];
					visited_grid_squares[last_visited_grid_squares_index][0] = current_grid_coordinates[0];
					visited_grid_squares[last_visited_grid_squares_index][1] = current_grid_coordinates[1];
					last_visited_grid_squares_index += 1;

					return;

				}

				current_grid_square_coords_duplicate[0] = current_grid_square_coords_duplicate[0] - 2;

				current_grid_square_coords_duplicate[1] = current_grid_square_coords_duplicate[1] - 2;

				if (!check_move('l', current_grid_square_coords) && visited_grid_square(current_grid_square_coords_duplicate)) {

					maze_bit_map[current_grid_square_coords[0]][current_grid_square_coords[1]-1] = 0;
					current_grid_coordinates[0] = current_grid_square_coords[0];
					current_grid_coordinates[1] = current_grid_square_coords[1];
					visited_grid_squares[last_visited_grid_squares_index][0] = current_grid_coordinates[0];
					visited_grid_squares[last_visited_grid_squares_index][1] = current_grid_coordinates[1];
					last_visited_grid_squares_index += 1;

					return;

				}

				current_grid_square_coords_duplicate[1] = current_grid_square_coords_duplicate[1] + 2;

				current_grid_square_coords_duplicate[1] = current_grid_square_coords_duplicate[1] + 2;

				if (!check_move('r', current_grid_square_coords) && visited_grid_square(current_grid_square_coords_duplicate)) {

					maze_bit_map[current_grid_square_coords[0]][current_grid_square_coords[1]+1] = 0;
					current_grid_coordinates[0] = current_grid_square_coords[0];
					current_grid_coordinates[1] = current_grid_square_coords[1];
					visited_grid_squares[last_visited_grid_squares_index][0] = current_grid_coordinates[0];
					visited_grid_squares[last_visited_grid_squares_index][1] = current_grid_coordinates[1];
					last_visited_grid_squares_index += 1;

					return;

				}

				current_grid_square_coords_duplicate[1] = current_grid_square_coords_duplicate[1] - 2;

			};

		}

	}

}

void generate_maze() {

	set_up_bit_map();

	visited_grid_squares[1][0] = current_grid_coordinates[0];
	visited_grid_squares[1][1] = current_grid_coordinates[1];

	draw_until_dead_end();

	while (!all_squares_visited()) {

		hunt_for_joint();
		draw_until_dead_end();

	}

}

int main() {

	generate_maze();
	print_bitmap();

}
