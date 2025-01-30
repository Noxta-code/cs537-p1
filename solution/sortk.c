#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_kword(const void *one, const void *two) {
    char **line_one = (char **)one;
    char **line_two = (char **)two;

    // Check for lines that have fewer than k words (key word is NULL)
    if (line_one[1] == NULL && line_two[1] == NULL) {
        return strcmp(line_one[0], line_two[0]);
    } else if (line_one[1] == NULL) {
        return 1; // place one after two
    } else if (line_two[1] == NULL) {
        return -1; // place two after one
    }

    // Remove newline from kth word if present
    line_one[1][strcspn(line_one[1], "\n")] = '\0';
    line_two[1][strcspn(line_two[1], "\n")] = '\0';

    // Compare the kth words
    int result = strcmp(line_one[1], line_two[1]);

    // If kth words were different, return the result
    if (result != 0) {
        return result;
    }

    // If kth words were the same, compare the whole line
    return strcmp(line_one[0], line_two[0]);
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
    FILE *input = fopen(argv[1], "r"); // Open in read mode
    if (input == NULL) {
        return 1;
    }

    // Create variables for reading input
    char *line = NULL; // Pointer to the line
    size_t length = 0; // Size of the buffer for curr line
    ssize_t read; // If -1 then end of the file has been reached
    int lineNum = 0; // How many lines input.txt has

    // Count how many lines the input file has
    while ((read = getline(&line, &length, input)) != -1) {
        lineNum++;
    }

    // Reset the file pointer to the beginning
    fseek(input, 0, SEEK_SET);

    // Memory to store lines and the kth word
    char *lines[lineNum][2]; // 2 because storing both line and keyword

    // Get the kth word of each line
    int i = 0;
    while ((read = getline(&line, &length, input)) != -1) {
        lines[i][0] = strdup(line); // Allocate memory for the line

        // Split the line into words (tokens)
        char *word = strtok(line, " "); // Delimiters are spaces
        int word_count = 0;

        // Find the kth word for this line
        while (word != NULL) {
            word_count++;
            if (word_count == order) {
                lines[i][1] = strdup(word); // Add a copy of the kth word to the array
                break;
            }
            word = strtok(NULL, " "); // Go to the next word
        }

        // If the line is too short, set the kth word to NULL
        if (word_count < order) {
            lines[i][1] = NULL;
        }

        i++;
    }

    // Sort the lines by kth word
    qsort(lines, lineNum, sizeof(lines[0]), compare_kword);

    // Print the sorted lines
    for (int i = 0; i < lineNum; i++) {
        printf("%s", lines[i][0]); // Print the line
        if (lines[i][0][strlen(lines[i][0]) - 1] != '\n') {
            printf("\n"); // Add a newline if it doesn't exist
        }
    }

    // Free memory
    for (int i = lineNum - 1; i >= 0; i--) {
        if (lines[i][1] != NULL) {
            free(lines[i][1]); // Free the kth word copy
        }
        if (lines[i][0] != NULL) {
            free(lines[i][0]); // Free the full line copy
        }
    }

    fclose(input);
    free(line);

    return 0;
}
