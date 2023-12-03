#include<stdio.h>
#include<string.h>

int main(void) {

	// Declare variable to receive the Schedule number
	int s;

	// Receive the Schedule number
	printf("Enter the your schedule number: ");
	scanf("%d", &s);

	// Declare Start & End time
	int i, start_hour[100], start_minute[100], end_hour[100], end_minute[100];
	char name[100];

	// Receive the Start & End time of Schedules
	for (i = 0; i < s; i++) {
		printf("Enter your schedule hh:mm ~ hh:mm / Appointment: ");
		scanf("%d:%d %d:%d ", &start_hour[i], &start_minute[i], &end_hour[i], &end_minute[i]);
		fgets(name, sizeof(name), stdin);
		name[strlen(name)-1] = '\0';
		if (((start_hour[i] < 10 && end_hour[i] < 10) && (start_hour[i] > 18 && end_hour[i] > 18)) && ((start_minute[i] < 0 && end_minute[i] < 0) && (start_minute[i] > 60 && end_minute[i] > 60))) {
			printf("Enter your time again: ");
			scanf("%d:%d %d:%d %s", &start_hour[i], &start_minute[i], &end_hour[i], &end_minute[i], name);
		}
	}

	// Declare an arrangement to arrange the entered Schedules in chronological order
	int j, temp_start_hour = 0, temp_start_minute = 0, temp_end_hour = 0, temp_end_minute = 0;

	// Arrange the entered Schedules in chronological order
	for (i = 0; i < s; i++) {
		for (j = 0; j < s; j++) {
			if ((start_hour[i] > start_hour[j]) || ((start_hour[i] == start_hour[j]) && start_minute[i] > start_minute[j])) {
				temp_start_hour = start_hour[i];
				temp_start_minute = start_minute[i];
				temp_end_hour = end_hour[i];
				temp_end_minute = end_minute[i];

				start_hour[i] = start_hour[j];
				start_minute[i] = start_minute[j];
				end_hour[i] = end_hour[j];
				end_minute[i] = end_minute[j];

				start_hour[j] = temp_start_hour;
				start_minute[j] = temp_start_minute;
				end_hour[j] = temp_end_hour;
				end_minute[j] = temp_end_minute;
			}
		}

		// Declare variables to save Maximum Nap
		int nap = 0, max_nap = 0, start_time = 0;
		int first = 0, last = 0;

		// Save Maximum Nap
		for (i = 0; i < s; i++) {
			nap = (start_hour[i + 1] - end_hour[i]) * 60 + (start_minute[i + 1] - end_minute[i]);
			if (nap > max_nap) {
				max_nap = nap;
				start_time = i;
			}
		}

		// Put in the start time of the first schedule and the end time of the last schedule
		first = (start_hour[0] - 10) * 60 + start_minute[0];
		last = (18 - end_hour[s - 1]) * 60 - end_minute[s - 1];

		// If The time from the start of the entire schedule to the first schedule is the maximum value
		if (first > max_nap) {
			if (first < 60) {
				printf("\nDay #1: the longest nap starts at 10:00 and will last for [%d minutes]", first);
			}
			else {
				printf("\nDay #1: the longest nap starts at 10:00 and will last for [%d hours and %d minutes]", first / 60, first % 60);
			}
		}
		// If The time from the end schedule to the end of the entire schedule is the maximum value
		else if (last > max_nap) {
			if (last < 60) {
				printf("\nDay #1: the longest nap starts at %d:%02d and will last for [%d minutes]", end_hour[start_time], end_minute[start_time], last);
			}
			else {
				printf("\nDay #1: the longest nap starts at %d:%02d and will last for [%d hours and %d minutes]", end_hour[start_time], end_minute[start_time], last / 60, last % 60);
			}
		}
		// If the time between other schedules is the maximum value
		else {
			if (max_nap < 60) {
				printf("\nDay #1: the longest nap starts at %d:%02d and will last for [%d minutes]", end_hour[start_time], end_minute[start_time], max_nap);
			}
			else {
				printf("\nDay #1: the longest nap starts at %d:%02d and will last for [%d hours and %d minutes]", end_hour[start_time], end_minute[start_time], max_nap / 60, max_nap % 60);
			}
		}
	}

	return 0;
}