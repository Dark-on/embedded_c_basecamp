#include <stdio.h>

#define LEN 11

typedef struct{
	unsigned char y :4;
	unsigned char x :4;
} coordinate_t;

//unsigned int input_maze[LEN][LEN] = {{1, 1, 1, 0, 1},
//									  {1, 0, 0, 0, 1},
//									  {1, 1, 1, 0, 1},
//									  {1, 1, 0, 0, 1},
//									  {1, 1, 0, 1, 1}};
//
//unsigned int output_maze[LEN][LEN] = {{1, 1, 1, 0, 1},
//									  {1, 0, 0, 0, 1},
//									  {1, 1, 1, 0, 1},
//									  {1, 1, 0, 0, 1},
//									  {1, 1, 0, 1, 1}};


unsigned int input_maze[LEN][LEN] = {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
									 {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
									 {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
									 {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
									 {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
									 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
									 {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
									 {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
									 {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
									 {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
									 {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};

unsigned int output_maze[LEN][LEN] = {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
									 {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
									 {1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
									 {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
									 {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
									 {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
									 {1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
									 {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
									 {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
									 {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
									 {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};
coordinate_t start_pos;
coordinate_t finish_pos;

void print_maze(unsigned int const maze[LEN][LEN]);
void move(coordinate_t path[], unsigned int len_arr);
void save_path(unsigned int maze[LEN][LEN], coordinate_t path[], unsigned int len_arr);
void debug_path(coordinate_t path[], unsigned int len_arr);


int main(void){

	/* Find start position*/
	for(int i = 0; i < LEN; i++){
		if (input_maze[0][i] == 0){
			start_pos.y = 0;
			start_pos.x = i;
			input_maze[0][i] = 2;
		}
	}
//	printf("Start: [%u][%u]\n", start_pos.y, start_pos.x);

	/* Find end position*/
	for(int i = 0; i < LEN; i++){
		if (input_maze[LEN - 1][i] == 0){
			finish_pos.y = LEN - 1;
			finish_pos.x = i;
		}
	}
//	printf("Finish: [%u][%u]\n", finish_pos.y, finish_pos.x);
	coordinate_t start[1] = {start_pos};
	move(start, 1);

}


void move(coordinate_t path[], unsigned int len_arr){
//	printf("\n");
//	print_maze(input_maze);


	coordinate_t current_coord = path[0];
	coordinate_t neighbors[4] = {{current_coord.y,     current_coord.x - 1},
								 {current_coord.y + 1, current_coord.x},
								 {current_coord.y,     current_coord.x + 1},
								 {current_coord.y - 1, current_coord.x}};
	for(unsigned int i = 0; i < 4; i++){
		coordinate_t item = neighbors[i];
		if (item.y == finish_pos.y && item.x == finish_pos.x){

			coordinate_t new_path[len_arr + 1];
			new_path[0] = item;
			for (unsigned j = 0; j < len_arr; j ++){
				new_path[j + 1] = path[j];
			}

//			printf("finish\n");
//			debug_path(new_path, len_arr + 1); //todo

			save_path(output_maze, new_path, len_arr + 1);
			print_maze(output_maze);
			break;
		} else if (0 <= item.y && item.y < LEN && 0 <= item.x && item.x < LEN && input_maze[item.y][item.x] == 0){
			coordinate_t new_path[len_arr + 1];
			new_path[0] = item;
			for (unsigned j = 0; j < len_arr; j ++){
				new_path[j + 1] = path[j];
			}
//			printf("Move: [%u][%u]\n", item.y, item.x);
//			debug_path(new_path, len_arr + 1); //todo


			input_maze[item.y][item.x] = 2;
			move(new_path, len_arr + 1);
		}
	}
}


void print_maze(unsigned int const maze[LEN][LEN]){
	for (unsigned int i = 0; i < LEN; i++){
		for (unsigned int j = 0; j < LEN; j++){
			if (maze[i][j] == 1){
				printf("█");
			} else if(maze[i][j] == 2){
				printf("•");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void save_path(unsigned int maze[LEN][LEN], coordinate_t path[], unsigned int len_arr){
	for(unsigned int i = 0; i < len_arr; i++){
		coordinate_t dot = path[i];
		maze[dot.y][dot.x] = 2;
	}
}

void debug_path(coordinate_t path[], unsigned int len_arr){
	for(unsigned int i = 0; i < len_arr; i++){
		printf("[%u][%u]\n", path[i].y, path[i].x);
	}
	printf("\n");
}



