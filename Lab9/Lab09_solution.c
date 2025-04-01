#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Employee {
    int id;
    int salary;
    char fav_quote[50];
    int sick_leaves[6];
} emp;

emp max_salary(emp *e1, emp *e2) {
    if (e1->salary > e2->salary || (e1->salary == e2->salary && e1->id > e2->id)) {
        return *e1;
    }
    return *e2;
}

void longest_word(char *s) {
    char longest[50] = "";
    char word[50];
    int max_len = 0, len = 0, i, start_idx = 0;
    int word_start = 0;

    for (i = 0; s[i] != '.'; i++) {
        if (s[i] == '_') {
            if (len >= max_len) {
                max_len = len;
                strcpy(longest, &s[word_start]);
                longest[len] = '\0';
            }
            len = 0;
            word_start = i + 1;
        } else {
            len++;
        }
    }
    if (len >= max_len) {
        max_len = len;
        strcpy(longest, &s[word_start]);
        longest[len] = '\0';
    }
    printf("The longest word is: %s\n", longest);
}

void cal_sick_leaves(int *arr, int size, int *mode, double *avg) {
    int count[101] = {0}; // Assuming sick leaves don't exceed 100
    int max_count = 0, latest_index = -1;
    *avg = 0.0;

    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
        *avg += arr[i];
    }
    *avg /= size;

    for (int i = 0; i < size; i++) {
        if (count[arr[i]] > max_count || (count[arr[i]] == max_count && i > latest_index)) {
            max_count = count[arr[i]];
            *mode = arr[i];
            latest_index = i;
        }
    }
}

emp get_input() {
    emp e;
    printf("Enter employee id:\n");
    scanf("%d", &e.id);
    printf("Enter employee's salary:\n");
    scanf("%d", &e.salary);
    printf("Enter Favorite Quote (each word is separated by '_' and the phrase ends with a '.'):\n");
    scanf("%s", e.fav_quote);
    printf("Enter sick leaves taken by an employee for each month during the first 6 months\n");
    for (int i = 0; i < 6; i++)
        scanf("%d", &e.sick_leaves[i]);
    return e;
}

int main() {
    emp e1 = get_input();
    emp e2 = get_input();
    emp max = max_salary(&e1, &e2);

    printf("ID of the employee with the highest salary is: %d\n", max.id);

    printf("This program supports TWO operations for the employee with the highest salary:\n");
    printf("\t1. Find the longest word in the employee's favorite quote,\n");
    printf("\t2. Find the number of sick leaves that appears the most (i.e. mode) and the average number of sick leaves taken.\n\n");
    printf("Choose an operation (1 or 2): ");
    int operation = 0;
    scanf("%d", &operation);

    if (operation == 1) {
        longest_word(max.fav_quote);
    } else if (operation == 2) {
        int mode;
        double avg;
        cal_sick_leaves(max.sick_leaves, 6, &mode, &avg);
        printf("The number of sick leaves appearing the most: %d\n", mode);
        printf("The average number of sick leaves: %.1lf\n", avg);
    }

    return 0;
}
