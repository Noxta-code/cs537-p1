#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Comparison function to use for qsort()
// Each parameter is a pointer to one of the elements being compared
int compare_kword(const void *one, const void *two){
    // Parameter types are void pointers for qsort and const so they aren't changed
    // Casting one and two to char** interprets them as pointers to arrays of char*
    // Dereferences lines[i][1] to compare the strings at the kth word pointer

    char **line_one = (char**)one; // Pointer to the first spot of 1st line
    char **line_two = (char**)two; // Pointer to the first spot of 2nd line
    // Each line is an array of two char* pointers ([0] points to the line start, [1] points to kth word)

    // Check for lines that have fewer than k words (key word is NULL)
    // Both lines have <k words, so they're comparable using the whole line
    if(line_one[1] == NULL && line_two[1] == NULL){
        return strcmp(line_one[0], line_two[0]);
    }
    // Only the first line has <k words, not comparable, ignore
    else if(line_one[1] == NULL){
        return 1; // place one after two
    }
    else if(line_two[1] == NULL){
        return -1; // place two after one
    }

    // Else, compare the keywords
    return strcmp(line_one[1], line_two[1]);
}

int main(int argc, char *argv[]) {

    // Check for correct number of arguments
    if(argc != 3){
        printf("Incorrect number of inputs. \n");
        return 1;
    }

    // Check that the second argument is an integer
    char *invalidPtr;
    int order = strtol(argv[2], &invalidPtr, 10);
    if(*invalidPtr != '\0'){ // Meaning there are non-int chars
        printf("k must be an integer.\n");
        return 1;
    }

    // Check if k <= 0
    if(order <= 0){
        printf("k less than or equal to 0. \n");
        return 1;
    }

    // Open the file
    FILE *input = fopen(argv[1], "r"); // Open in read mode
    if (input == NULL){
        printf("Error opening file");
        return 1;
    }

    // Create variables for reading input
    char *line = NULL; // Pointer to the line
    size_t length = 0; // Size of the buffer for curr line
    ssize_t read; // If -1 then end' of the file has been reached
    int lineNum = 0; // How many lines input.txt has

    // Count how many lines the input file has
    while ((read = getline(&line, &length, input)) != -1){
        lineNum++;
    }

    // Reset the file pointer to the beginning
    fseek(input, 0, SEEK_SET);

    // Memory to store lines and the kth word
    char *lines[lineNum][2]; // 2 because storing both line and keyword

    // Get the kth word of each line
    int i = 0;
    while((read = getline(&line, &length, input)) != -1){
        lines[i][0] = strdup(line); // Allocate memory for the line

        // Split the line into words (tokens)
        char *word = strtok(line, " "); // Delimiters are spaces
        int word_count = 0;

        // Find the kth word for this line
        while(word != NULL){
            word_count++;
            if(word_count == order){
                lines[i][1] = strdup(word); // Add a copy of the kth word to the array
                break;
            }
            word = strtok(NULL, " "); // Go to the next word
        }

        // If the line is too short, set the kth word to NULL
        if(word_count < order){
            lines[i][1] = NULL;
        }

        i++;
    }

    // Sort the lines by kth word. Can use sizeof because it's the pointer, not the actual line
    qsort(lines, lineNum, sizeof(lines[0]), compare_kword);

    // Print the sorted lines
    for(int i=0; i<lineNum; i++){
        printf("%s", lines[i][0]); // %s to print a string from a pointer to the first char
    }


    // Free memory
    for(int i=lineNum-1; i>=0; i--){
        if(lines[i][1] != NULL){
            free(lines[i][1]); // Free the full line copy
        }
        if(lines[i][0] != NULL){
            free(lines[i][0]); // Free the kth word copy
        }
        //free(lines[i]); // Free the whole row
    }

    fclose(input);
    free(line);

	return 0;
}
