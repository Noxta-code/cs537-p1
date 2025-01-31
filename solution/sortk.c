#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to compare strings, skipping leading whitespace
int compare_trimmed_lines(const char *a, const char *b) {
    // Skip leading whitespace in both strings
    while (isspace((unsigned char)*a)) a++;
    while (isspace((unsigned char)*b)) b++;
    return strcmp(a, b);
}

int compare_kword(const void *one, const void *two) {
    char ***line_one = (char ***)one;
    char ***line_two = (char ***)two;

    // Check for lines that have fewer than k words (key word is NULL)
    if ((*line_one)[1] == NULL && (*line_two)[1] == NULL) {
        return compare_trimmed_lines((*line_one)[0], (*line_two)[0]);
    } else if ((*line_one)[1] == NULL) {
        return 1;
    } else if ((*line_two)[1] == NULL) {
        return -1;
    }

    // Remove newline from kth word if present
    (*line_one)[1][strcspn((*line_one)[1], "\n")] = '\0';
    (*line_two)[1][strcspn((*line_two)[1], "\n")] = '\0';

    // Compare the kth words
    int result = strcmp((*line_one)[1], (*line_two)[1]);

    // If kth words were different, return the result
    if (result != 0) return result;

    // If kth words were the same, compare the whole line
    return compare_trimmed_lines((*line_one)[0], (*line_two)[0]);
}

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        return 1;
    }

    // Check that the second argument is an integer
    char *invalidPtr;
    int order = strtol(argv[2], &invalidPtr, 10);
    if (*invalidPtr != '\0') { // Meaning there are non-int chars
        return 1;
    }

    // Check if k <= 0
    if (order <= 0) {
        return 1;
    }

    // Open the file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        return 1;
    }

    // Create variables for reading input
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int lineNum = 0;
    int capacity = 16; // Initial capacity

    // Dynamically allocate memory for lines array
    char ***lines = malloc(capacity * sizeof(char **));
    if (lines == NULL) {
        fclose(input);
        return 1;
    }

    // Initialize each entry
    for (int i = 0; i < capacity; i++) {
        lines[i] = malloc(2 * sizeof(char *));
        if (lines[i] == NULL) {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            fclose(input);
            return 1;
        }
        lines[i][0] = NULL;
        lines[i][1] = NULL;
    }

    // Read and store lines
    while ((read = getline(&line, &length, input)) != -1) {
        // Resize array if needed
        if (lineNum >= capacity) {
            int new_capacity = capacity * 2;
            char ***new_lines = realloc(lines, new_capacity * sizeof(char **));
            if (new_lines == NULL) {
                // Clean up on allocation failure
                for (int i = 0; i < lineNum; i++) {
                    if (lines[i][1] != NULL) free(lines[i][1]);
                    if (lines[i][0] != NULL) free(lines[i][0]);
                    free(lines[i]);
                }
                free(lines);
                free(line);
                fclose(input);
                return 1;
            }
            lines = new_lines;

            // Initialize new entries
            for (int i = capacity; i < new_capacity; i++) {
                lines[i] = malloc(2 * sizeof(char *));
                if (lines[i] == NULL) {
                    // Clean up on allocation failure
                    for (int j = 0; j < i; j++) {
                        if (lines[j][1] != NULL) free(lines[j][1]);
                        if (lines[j][0] != NULL) free(lines[j][0]);
                        free(lines[j]);
                    }
                    free(lines);
                    free(line);
                    fclose(input);
                    return 1;
                }
                lines[i][0] = NULL;
                lines[i][1] = NULL;
            }
            capacity = new_capacity;
        }

        lines[lineNum][0] = strdup(line);
        if (lines[lineNum][0] == NULL) {
            // Clean up on allocation failure
            for (int i = 0; i < lineNum; i++) {
                if (lines[i][1] != NULL) free(lines[i][1]);
                if (lines[i][0] != NULL) free(lines[i][0]);
                free(lines[i]);
            }
            free(lines);
            free(line);
            fclose(input);
            return 1;
        }

        // Split the line into words
        char *temp_line = strdup(line);
        if (temp_line == NULL) {
            // Clean up on allocation failure
            for (int i = 0; i < lineNum + 1; i++) {
                if (lines[i][1] != NULL) free(lines[i][1]);
                if (lines[i][0] != NULL) free(lines[i][0]);
                free(lines[i]);
            }
            free(lines);
            free(line);
            fclose(input);
            return 1;
        }

        char *word = strtok(temp_line, " ");
        int word_count = 0;

        // Find the kth word
        while (word != NULL) {
            word_count++;
            if (word_count == order) {
                lines[lineNum][1] = strdup(word);
                if (lines[lineNum][1] == NULL) {
                    // Clean up on allocation failure
                    free(temp_line);
                    for (int i = 0; i < lineNum + 1; i++) {
                        if (lines[i][1] != NULL) free(lines[i][1]);
                        if (lines[i][0] != NULL) free(lines[i][0]);
                        free(lines[i]);
                    }
                    free(lines);
                    free(line);
                    fclose(input);
                    return 1;
                }
                break;
            }
            word = strtok(NULL, " ");
        }

        free(temp_line);
        lineNum++;
    }

    // Sort the lines
    qsort(lines, lineNum, sizeof(char **), compare_kword);

    // Print sorted lines
    for (int i = 0; i < lineNum; i++) {
        printf("%s", lines[i][0]);
        if (lines[i][0][strlen(lines[i][0]) - 1] != '\n') {
            printf("\n");
        }
    }

    // Clean up
    for (int i = 0; i < capacity; i++) {
        if (lines[i][1] != NULL) free(lines[i][1]);
        if (lines[i][0] != NULL) free(lines[i][0]);
        free(lines[i]);
    }
    free(lines);
    free(line);
    fclose(input);

    return 0;
}
