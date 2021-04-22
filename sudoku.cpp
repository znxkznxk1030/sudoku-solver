#include <cstdio>
#include <vector>

using namespace std;

int origin[12][12];
int LIMIT_TRY = 11;

void read_test_case () {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			scanf("%d", &origin[j][i]);	
		}
	}
}

void print_test_case () {
		printf("\n-------------------------------------\n");
	for (int i = 1; i <= 9; i++) {
			printf("| ");
			for (int j = 1; j <= 9; j++) {
					printf("%2d ", origin[j][i]);
					if (j % 3 == 0) printf(" | ");
			}
			if (i % 3 == 0) {
 					printf("\n-------------------------------------\n");
 			} else printf("\n");
	}
}

int valid_sudoku () {

		for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) {
			int curval = origin[j][i];
			if (curval == -1) return -1;
			for (int x = 1; x <= 9; x++) {
					// printf("x : %d %d \n", curval, origin[x][i]);
					if (x == i) continue;
					if (origin [x][i] == curval) return -1;
			}

			for (int y = 1; y <= 9; y++) {
				// printf("y : %d %d\n", curval, origin[j][y]);
				if (y == j) continue;
				if (origin[j][y] == curval) return -1;
			}

			int basex = (j - 1) / 3 * 3;
			int basey = (i - 1) / 3 * 3;

			printf("valid > basex : %d, basey: %d\n", basex, basey);

			for (int x = 1; x <= 2; x++) for (int y = 1; y <= 2; y++) {
					int curx = ((j - 1)/3)*3 + x;
					int cury = ((i - 1)/3)*3 + y;
					// printf(" x y: %d %d\n, curval, origin[curx][cury]);

					if (curx == j && cury == i) continue;

					if (curval == origin[curx][cury]) return -1;
			}
		} 

		return 1; // valid
}

int find_value(int x, int y) {
	
	vector<int> poss;
	for (int num = 1; num <= 9; num++) {
		int isUsed = 0;
		for (int i = 1; i <= 9; i++) {
			if (i != y && origin[x][i] != num) {
				isUsed = 1;
				break;
			}
		}
		if (isUsed == 1) continue;

		for (int j = 1; j <= 9; j++) {
			if (j != x && origin[j][y] == num) {
					isUsed = 1;
					break;
			}
		}
		if (isUsed == 1) continue;

		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				int curx = (x/3)*3 + j;
				int cury = (y/3)*3 + i;
				
				if (curx != x && cury != y && num == origin[curx][cury]) {
						isUsed = 1;
						break;
				}

			}
		}
		

		if (isUsed == 1) continue;
		poss.push_back(num);
	}	

	if (poss.size() != 1) return -1;
	return poss[0];
}

void try_find_empty(int nfill) {
	int copy[12][12];

	for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) {
		copy[j][i] = origin[j][i];
	}

	for (int x = 1; x <= 9; x++) for (int y = 1; y <= 9; y++) {
		if (origin[x][y] == nfill) {
			for (int xx = 1; xx <= 9; xx++) copy[xx][y] = nfill;
			for (int yy = 1; yy <= 9; yy++) copy[x][yy] = nfill;
		}
	}

	for (int a = 0; a < 3; a++) for (int b = 0; b < 3; b++) {
		int nblank = 0;
		int already = 0;
		int rx, ry;

		int basex = a*3;
		int basey = b*3;

		for (int x = 1; x <= 3; x++) {
			for (int y = 1; y <= 3; y++) {
				if (origin[basex + x][basey + y] == nfill) {
					already = 1;
					break;
				}
				if (copy[basex + x][basey + y] == -1) {

						rx = basex + x; ry =basey + y;
						nblank++;
				}
			}
			if (already == 1) break;
		}

		// x-axios y-axios
		if (nblank == 1 && already == 0) {
			for (int x = 1; x <= 9; x++) {
				if (origin[x][ry] == nfill) {
						already = 1;		
						break;
				}
			}

			for (int y = 1; y <= 9; y++) {
				if (origin[rx][y] == nfill) {
						already = 1;
						break;
				}
			}
		}


		if (nblank == 1 && already == 0) {
			origin[rx][ry] = nfill;
		}
	}
	
	printf("fill : %d =====\n", nfill);
	for (int x = 1; x <= 9; x++) {
		for (int y = 1; y <= 9; y++) {
				printf("%2d", copy[y][x]);
				if ( y % 3 == 0) printf(" | ");
		}
		
		if (x % 3 == 0) {
      printf("\n-----------------------------------\n");
		} else printf("\n");	
	}
}

void fill_sudoku() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
				if (origin[j][i] != -1) continue;
			origin[j][i] = find_value(j, i);
		}
	}	

	for (int nfill = 1; nfill <= 9; nfill++) {
		try_find_empty(nfill);	
	}
}

int main () {
	read_test_case();
	print_test_case();

	if (valid_sudoku() == 1) {
			printf("valid\n");
	} else {
			printf("invalid\n");
	}

	int ntry = 0;

	while (ntry++ < LIMIT_TRY) {
			fill_sudoku();
			printf("try: %d\n", ntry);
			print_test_case();
			printf("\n\n");
			if (valid_sudoku() == 1) {
					printf("solved! in %d trys awesome right?!\n", ntry);
					break;
			}
	}

	print_test_case();

	return 1;
}
