#include <stdio.h>
#include <string.h>

int main(void) {

    // Declare the variables of the sequence and subsequence to be tested
	char sequence[10000], subsequence[100];
    // Declare variables for the number of sequences to be inputted
	int i, num;

    // Enter the number of sequences
    printf("Enter the number of test cases(Sequence): ");
	scanf("%d", &num);
	fflush(stdin);

    printf("\n");

    // Declare variables to output results
    int cnt[100] = { 0 };

    // Repeat as many times as you receive
    for(int a = 0;a < num;a++) {
        // Enter the sequence to test
        printf("Enter a sequence of alphabet: ");
        fgets(sequence, sizeof(sequence), stdin);

        // Enter the subsequence to test
        printf("Enter the subsequence of first sequence entered: ");
        fgets(subsequence, sizeof(subsequence), stdin);

        printf("\n");

        int length1 = strlen(sequence), length2 = strlen(subsequence);

        // Repeat to add zero at the beginning of the dynamic program array
        for (i = strlen(sequence); i > 0; i--) {
            sequence[i] = sequence[i - 1];
        }
        for (i = strlen(subsequence); i > 0; i--) {
            subsequence[i] = subsequence[i - 1];
        }

        int j = 0;
        int distinct[100][100] = { 0 };

        for (i = 0; i < 100; i++) {
            distinct[0][i] = 1;
        }

        // The process of finding a sub-sequence of that sequence
        for (i = 1; i <= length2; i++) {
            for (j = 1; j <= length1; j++) {
                if (subsequence[i] == sequence[j]) {
                    distinct[i][j] = distinct[i][j - 1] + distinct[i - 1][j - 1];
                }
                else {
                    distinct[i][j] = distinct[i][j - 1];
                }
            }
        }

        // Save output
        cnt[a] = distinct[i - 1][j - 1];

        // Initialize before repeating
	    sequence[0] = '\0', subsequence[0] = '\0';
    }

    // Print output
    printf("=====Output=====\n");
    for (int a = 0;a < num;a++) {
        printf("%d\n", cnt[a]);
    }
    

    return 0;

}