#include <stdio.h>

// [The cheapest way]

// Function for selecting minimum of weight
int min(int a, int b, int c) {  
	if (a < b) {
		if (c < a) {
			return c;
		}
		else {
			return a;
		}
	}
	else {
		if (c < b) {
			return c;
		}
		else {
			return b;
		}
	}
}

int main(void) {

	// get matrix from user
	int m, n;
    int m_temp, n_temp;

    int total_weight[10];
    int sequence[10][100] = { 0 };
    int cnt = 0;

    while (1) {

        // Get input of m X n
        printf("Enter the number of row and column (row <= 10,  column <= 100) : ");
        scanf("%d %d", &m, &n);  

        
        if (m == -1 || n == -1) {
            break; // Shut down the program when '-1' is entered
        }
        else {
            int dimension[10][100], i, j;

            // Fill the matrix from user
            printf("Fill the dimension %d X %d\n", m, n);

            for (i = 0; i < m; i++) {
                for (j = 0; j < n; j++) {
                    scanf("%d", &dimension[i][j]);
                }
            }

            // Declare variable for cicular matrix
            int cheapest_way[10][100] = { 0 }, left = 0;

            // Compute minimum weight of each values
            for (i = 0; i < n; i++) {
                for (j = 0; j < m; j++) {
                    if (i == 0) {  
                        cheapest_way[j][i] = dimension[j][i];
                    }
                    else { 
                        if (j == 0) {  // for circular matrix
                            left = m - 1;
                        }
                        else {
                            left = j - 1;
                        }
                        // Dynamic programming for finding cheapest way, find minimum weight
                        cheapest_way[j][i] = min(dimension[j][i] + cheapest_way[left][i - 1], dimension[j][i] + cheapest_way[j][i - 1], dimension[j][i] + cheapest_way[(j + 1) % m][i - 1]);
                    }
                }
            }

            // Backtracking for finding sequence of cheapest way and computing total weight
            int index = 0, temp = 0;

            printf("\n");
            for (i = n - 1; i >= 0; i--) {
                int cheap = 100;
                if (i == n - 1) {  // Check total weight
                    for (j = 0; j < m; j++) {
                        if (cheapest_way[j][i] < cheap) {
                            cheap = cheapest_way[j][i];
                            index = j;
                        }
                    }
                    sequence[cnt][i] = dimension[index][i];
                    total_weight[cnt] += dimension[index][i];
                }
                else {  // Backtracking
                    for (j = 0; j < m; j++) {
                        if (index == 0) {
                            left = m - 1;
                        }
                        else {
                            left = index - 1;
                        }
                        if ((cheapest_way[j][i] <= cheap && j == left) || (cheapest_way[j][i] <= cheap && j == index) || (cheapest_way[j][i] <= cheap && j == (index + 1) % m)) {
                            cheap = cheapest_way[j][i];
                            temp = j;
                        }
                    }
                    index = temp;
                    sequence[cnt][i] = dimension[index][i];
                    total_weight[cnt] += dimension[index][i];
                }
                
            }
            cnt++;
            m_temp = m;
            n_temp = n;
        }        
    }

	// Print the result
    for(int i = 0;i < cnt;i++) {
        for (int j = 0; j < n_temp; j++) {
            printf("%d ", sequence[i][j]);
        }
        printf("\n");
        printf("%d \n", total_weight[i]);
    }

    return 0;

}