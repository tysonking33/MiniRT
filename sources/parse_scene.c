#include "../includes/parse.h"

#define BUFFER_SIZE 1024

int print_values(struct s_init *initial_data_struct)
{
    printf("Ambient Ratio: %f\n", initial_data_struct->ambient_ratio);
    printf("Ambient RGB: %f, %f, %f\n", initial_data_struct->ambient_rgb[0], initial_data_struct->ambient_rgb[1], initial_data_struct->ambient_rgb[2]);

    printf("Camera XYZ: %f, %f, %f\n", initial_data_struct->camera_xyz[0], initial_data_struct->camera_xyz[1], initial_data_struct->camera_xyz[2]);
    printf("Camera Orientation: %f, %f, %f\n", initial_data_struct->camera_orientation[0], initial_data_struct->camera_orientation[1], initial_data_struct->camera_orientation[2]);
    printf("Camera FOV: %f\n", initial_data_struct->camera_fov);

    printf("Light XYZ: %f, %f, %f\n", initial_data_struct->light_xyz[0], initial_data_struct->light_xyz[1], initial_data_struct->light_xyz[2]);
    printf("Light Ratio: %f\n", initial_data_struct->light_ratio);

    printf("Sphere Count: %d\n", initial_data_struct->sphere_count);
    for (int i = 0; i < initial_data_struct->sphere_count; ++i)
    {
        printf("Sphere %d XYZ: %f, %f, %f\n", i, initial_data_struct->sphere_array[i].sphere_xyz[0], initial_data_struct->sphere_array[i].sphere_xyz[1], initial_data_struct->sphere_array[i].sphere_xyz[2]);
        printf("Sphere %d Diameter: %f\n", i, initial_data_struct->sphere_array[i].sphere_diameter);
        printf("Sphere %d RGB: %f, %f, %f\n", i, initial_data_struct->sphere_array[i].sphere_rgb[0], initial_data_struct->sphere_array[i].sphere_rgb[1], initial_data_struct->sphere_array[i].sphere_rgb[2]);
    }

    printf("Plane Count: %d\n", initial_data_struct->plane_count);
    for (int i = 0; i < initial_data_struct->plane_count; ++i)
    {
        printf("Plane %d XYZ: %f, %f, %f\n", i, initial_data_struct->plane_array[i].plane_xyz[0], initial_data_struct->plane_array[i].plane_xyz[1], initial_data_struct->plane_array[i].plane_xyz[2]);
        printf("Plane %d Normalized Vector: %f, %f, %f\n", i, initial_data_struct->plane_array[i].plane_normalised_vector[0], initial_data_struct->plane_array[i].plane_normalised_vector[1], initial_data_struct->plane_array[i].plane_normalised_vector[2]);
        printf("Plane %d RGB: %f, %f, %f\n", i, initial_data_struct->plane_array[i].plane_rgb[0], initial_data_struct->plane_array[i].plane_rgb[1], initial_data_struct->plane_array[i].plane_rgb[2]);
    }

    printf("Cylinder Count: %d\n", initial_data_struct->cylinder_count);
    for (int i = 0; i < initial_data_struct->cylinder_count; ++i)
    {
        printf("Cylinder %d XYZ: %f, %f, %f\n", i, initial_data_struct->cylinder_array[i].cylinder_xyz[0], initial_data_struct->cylinder_array[i].cylinder_xyz[1], initial_data_struct->cylinder_array[i].cylinder_xyz[2]);
        printf("Cylinder %d Normalized Vector: %f, %f, %f\n", i, initial_data_struct->cylinder_array[i].cylinder_normalised_vector[0], initial_data_struct->cylinder_array[i].cylinder_normalised_vector[1], initial_data_struct->cylinder_array[i].cylinder_normalised_vector[2]);
        printf("Cylinder %d Diameter: %f\n", i, initial_data_struct->cylinder_array[i].cylinder_diameter);
        printf("Cylinder %d Height: %f\n", i, initial_data_struct->cylinder_array[i].cylinder_height);
        printf("Cylinder %d RGB: %f, %f, %f\n", i, initial_data_struct->cylinder_array[i].cylinder_rgb[0], initial_data_struct->cylinder_array[i].cylinder_rgb[1], initial_data_struct->cylinder_array[i].cylinder_rgb[2]);
    }
    return 1;
}

int parse_line(char *line, struct s_init *initial_data_struct)
{
    printf("char *line: %s\n", line);
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
        initial_data_struct->camera_fov = strtod(tokens[3], &endptr);
        break;

    case 'L':
        initial_data_struct->light_xyz = parse_float_array(tokens[1], ',');
        initial_data_struct->light_ratio = strtod(tokens[2], &endptr);
        break;

    case 's':
        initial_data_struct->sphere_array = (struct s_sphere_init *)malloc(10 * sizeof(struct s_sphere_init));
        initial_data_struct->sphere_array[initial_data_struct->sphere_count].sphere_xyz = parse_float_array(tokens[1], ',');
        initial_data_struct->sphere_array[initial_data_struct->sphere_count].sphere_diameter = strtod(tokens[2], &endptr);
        initial_data_struct->sphere_array[initial_data_struct->sphere_count].sphere_rgb = parse_float_array(tokens[3], ',');

        initial_data_struct->sphere_count++;
        break;
    case 'p':
        initial_data_struct->plane_array = (struct s_plane_init *)malloc(10 * sizeof(struct s_plane_init));
        initial_data_struct->plane_array[initial_data_struct->plane_count].plane_xyz = parse_float_array(tokens[1], ',');
        initial_data_struct->plane_array[initial_data_struct->plane_count].plane_normalised_vector = parse_float_array(tokens[2], ',');
        initial_data_struct->plane_array[initial_data_struct->plane_count].plane_rgb = parse_float_array(tokens[3], ',');

        initial_data_struct->plane_count++;
        break;

    case 'c':
        initial_data_struct->cylinder_array = (struct s_cylinder_init *)malloc(10 * sizeof(struct s_cylinder_init));
        initial_data_struct->cylinder_array[initial_data_struct->cylinder_count].cylinder_xyz = parse_float_array(tokens[1], ',');
        initial_data_struct->cylinder_array[initial_data_struct->cylinder_count].cylinder_normalised_vector = parse_float_array(tokens[2], ',');
        initial_data_struct->cylinder_array[initial_data_struct->cylinder_count].cylinder_diameter = strtod(tokens[3], &endptr);
        initial_data_struct->cylinder_array[initial_data_struct->cylinder_count].cylinder_height = strtod(tokens[4], &endptr);
        initial_data_struct->cylinder_array[initial_data_struct->cylinder_count].cylinder_rgb = parse_float_array(tokens[5], ',');

        initial_data_struct->cylinder_count++;
        break;

    default:
        // Handle unknown type
        printf("default: %s\n", line);
        break;
    }
    //print_values(initial_data_struct);

    free(tokens); // Don't forget to free the memory allocated by ft_split

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

    free(elements); // Free the memory allocated by ft_split

    return result;
}

int read_and_parse_file(char *filename, struct s_init *inital_data_struct)
{
    int fileDescriptor = open(filename, O_RDONLY);

    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and print lines from the file
    char buffer[BUFFER_SIZE];
    char lineBuffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char *newline;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0)
    {
        char *ptr = buffer;

        while ((newline = memchr(ptr, '\n', bytesRead - (ptr - buffer))) != NULL)
        {
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
        if (ptr < buffer + bytesRead)
        {
            // Copy the remaining part of the line to lineBuffer
            size_t remainingLength = buffer + bytesRead - ptr;
            memcpy(lineBuffer, ptr, remainingLength);

            // Null-terminate the remaining part
            lineBuffer[remainingLength] = '\0';

            // Print the remaining part of the line
            //write(STDOUT_FILENO, lineBuffer, remainingLength);
            //printf("current line2: %s\n", lineBuffer);
            parse_line(lineBuffer, inital_data_struct);

        }
    }

    // Check for read errors
    if (bytesRead == -1)
    {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fileDescriptor) == -1)
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int first_time_read(char *filename, struct s_init *inital_data_struct)
{
    int fileDescriptor = open(filename, O_RDONLY);

    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and print lines from the file
    char buffer[BUFFER_SIZE];
    char lineBuffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char *newline;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0)
    {
        char *ptr = buffer;

        while ((newline = memchr(ptr, '\n', bytesRead - (ptr - buffer))) != NULL)
        {
            // Copy characters to lineBuffer until the newline character
            size_t lineLength = newline - ptr + 1;
            memcpy(lineBuffer, ptr, lineLength);

            // Null-terminate the line
            lineBuffer[lineLength] = '\0';

            // Print the current line
            //write(STDOUT_FILENO, lineBuffer, lineLength);
            //printf("current line1: %s\n", lineBuffer);

            // Move to the next line
            if (lineBuffer[0] == 's')
                inital_data_struct->sphere_array++;
            else if (lineBuffer[0] == 'p')
                inital_data_struct->plane_count++;
            else if (lineBuffer[0] == 'c')
                inital_data_struct->cylinder_count++;
            ptr = newline + 1;
        }

        // Check if the last character read is a newline
        if (ptr < buffer + bytesRead)
        {
            // Copy the remaining part of the line to lineBuffer
            size_t remainingLength = buffer + bytesRead - ptr;
            memcpy(lineBuffer, ptr, remainingLength);

            // Null-terminate the remaining part
            lineBuffer[remainingLength] = '\0';

            if (lineBuffer[0] == 's')
                inital_data_struct->sphere_array++;
            else if (lineBuffer[0] == 'p')
                inital_data_struct->plane_count++;
            else if (lineBuffer[0] == 'c')
                inital_data_struct->cylinder_count++;

            // Print the remaining part of the line
            //write(STDOUT_FILENO, lineBuffer, remainingLength);
            //printf("current line2: %s\n", lineBuffer);
        }
    }

    // Check for read errors
    if (bytesRead == -1)
    {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    // Close the file
    if (close(fileDescriptor) == -1)
    {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
    return 0;
}

/*int main(int argc, char **argv)
{
    if (argc == 2)
    {
        char *filename = argv[1];
        printf("file_name: %s\n", filename);

        struct s_init *inital_data_struct = (struct s_init *)malloc(sizeof(struct s_init));

        if (inital_data_struct == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        inital_data_struct->sphere_count = 0;
        inital_data_struct->plane_count = 0;
        inital_data_struct->cylinder_count = 0;

        first_time_read(filename, inital_data_struct);

        read_and_parse_file(filename, inital_data_struct);
        print_values(inital_data_struct);
    }
}*/