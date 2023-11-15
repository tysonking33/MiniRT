#include "parse.h"

#define BUFFER_SIZE 1024

int parse_line(char *line, struct s_init *initial_data_struct)
{
    char **tokens = ft_split(line, ' ');
    char *endptr;

    switch (line[0])
    {
        case 'A':
            initial_data_struct->ambient_ratio = strtod(tokens[1], &endptr);
            initial_data_struct->ambient_rgb = parse_float_array(tokens[2], ',');
            break;

        case 'C':
            initial_data_struct->camera_xyz = parse_float_array(tokens[1], ',');
            initial_data_struct->camera_orientation = parse_float_array(tokens[2], ',');
            initial_data_struct->ambient_ratio = strtod(tokens[3], &endptr);
            break;

        case 'L':
            initial_data_struct->light_xyz = parse_float_array(tokens[1], ',');
            initial_data_struct->light_ratio = strtod(tokens[2], &endptr);
            break;

        case 's':
            initial_data_struct->light_xyz = parse_float_array(tokens[1], ',');
            initial_data_struct->light_ratio = strtod(tokens[2], &endptr);
            break;

        default:
            // Handle unknown type
            break;
    }

    free(tokens);  // Don't forget to free the memory allocated by ft_split

    return -1;
}

float *parse_float_array(char *token, char delimiter)
{
    char **elements = ft_split(token, delimiter);
    char *endptr;
    float *result = (float *)malloc(3 * sizeof(float));

    for (int i = 0; i < 3; ++i)
    {
        result[i] = strtod(elements[i], &endptr);
    }

    free(elements);  // Free the memory allocated by ft_split

    return result;
}


int read_and_parse_file(char *filename, struct s_init* inital_data_struct)
{
    int fileDescriptor = open(filename, O_RDONLY);

    
    if (fileDescriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and print lines from the file
    char buffer[BUFFER_SIZE];
    char lineBuffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char *newline;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        char *ptr = buffer;

        while ((newline = memchr(ptr, '\n', bytesRead - (ptr - buffer))) != NULL) {
            // Copy characters to lineBuffer until the newline character
            size_t lineLength = newline - ptr + 1;
            memcpy(lineBuffer, ptr, lineLength);

            // Null-terminate the line
            lineBuffer[lineLength] = '\0';

            // Print the current line
            //write(STDOUT_FILENO, lineBuffer, lineLength);
            printf("current line1: %s\n", lineBuffer);
            parse_line(lineBuffer, inital_data_struct);

            // Move to the next line
            ptr = newline + 1;
        }

        // Check if the last character read is a newline
        if (ptr < buffer + bytesRead) {
            // Copy the remaining part of the line to lineBuffer
            size_t remainingLength = buffer + bytesRead - ptr;
            memcpy(lineBuffer, ptr, remainingLength);

            // Null-terminate the remaining part
            lineBuffer[remainingLength] = '\0';

            // Print the remaining part of the line
            //write(STDOUT_FILENO, lineBuffer, remainingLength);
            printf("current line2: %s\n", lineBuffer);
        }
    }

    // Check for read errors
    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
    return 0;
}


int first_time_read(char *filename, struct s_init* inital_data_struct)
{
    int fileDescriptor = open(filename, O_RDONLY);

    
    if (fileDescriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and print lines from the file
    char buffer[BUFFER_SIZE];
    char lineBuffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char *newline;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        char *ptr = buffer;

        while ((newline = memchr(ptr, '\n', bytesRead - (ptr - buffer))) != NULL) {
            // Copy characters to lineBuffer until the newline character
            size_t lineLength = newline - ptr + 1;
            memcpy(lineBuffer, ptr, lineLength);

            // Null-terminate the line
            lineBuffer[lineLength] = '\0';

            // Print the current line
            //write(STDOUT_FILENO, lineBuffer, lineLength);
            printf("current line1: %s\n", lineBuffer);

            if (lineBuffer[0] == 's')
                inital_data_struct->sphere_count++;
            else if (lineBuffer[0] == 'p')
                inital_data_struct->plane_count++;
            else if (lineBuffer[0] == 'x')
                inital_data_struct->cylinder_count++;

            // Move to the next line
            ptr = newline + 1;
        }

        // Check if the last character read is a newline
        if (ptr < buffer + bytesRead) {
            // Copy the remaining part of the line to lineBuffer
            size_t remainingLength = buffer + bytesRead - ptr;
            memcpy(lineBuffer, ptr, remainingLength);

            // Null-terminate the remaining part
            lineBuffer[remainingLength] = '\0';

            // Print the remaining part of the line
            //write(STDOUT_FILENO, lineBuffer, remainingLength);
            printf("current line2: %s\n", lineBuffer);
        }
    }

    // Check for read errors
    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
    return 0;
}


int main(int argc, char **argv)
{
    printf("argc: %d\n", argc);
    if (argc == 2)
    {
        char *filename = argv[1];
        printf("file_name: %s\n", filename);

        struct s_init* inital_data_struct = (struct s_init*)malloc(sizeof(struct s_init));

        if (inital_data_struct == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        inital_data_struct->sphere_count = 0;
        inital_data_struct->plane_count = 0;
        inital_data_struct->cylinder_count = 0;

        first_time_read(filename, inital_data_struct);

        read_and_parse_file(filename, inital_data_struct);
    }
    
}