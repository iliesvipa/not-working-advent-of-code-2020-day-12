#include <stdio.h>
#include <stdlib.h>

typedef enum Direction
{
    north = 0,
    east = 90,
    south = 180,
    west = 270
} Direction;

int main(void)
{
    
    char* filepath = "day.txt";
    FILE* file = fopen(filepath, "r");
    if (!file)
    {
        fprintf(stderr, "Error: file could not be open\n");
        perror(filepath);
        return 1;
    }

    // ADVENT OF CODE 2020, DAY 12. Why is it not working ?
    // Something gets wrong with a certain combination
    char command;
    int magnitude;
    int horizontal = 0;
    const int ans = 1148;
    int direction = east; // 1, 162 // direction : 270
    long int position[2] = {0, 0}; // 0 N-S | 1 E-W
    int line = 1;
    //printf("New direction : %d | New Position(S-N) : %d | New Position(E-W) : %d\n", direction, position[0], position[1]);
    while (fscanf(file, "%c%d", &command, &magnitude) == 2)
    {
        // position[horizontal] += magnitude * (((direction & 4) == 4) * -1 * 1 + (1 * ((direction & 4) == 0)));
        switch(command)
        {
            case 'F': // Move forward in the current direction
            horizontal = (direction == east || direction == west);
            //position[horizontal] += magnitude * (((direction & 4) == 4) * -1 | ((direction & 4) == 0) * 1);
            
            position[horizontal] += (magnitude * ((direction == south || direction == west) ? -1 : 1));
            
            break;

            case 'N': // Move by magnitude in North
            position[0] += magnitude; 
            break;

            case 'E': // Move by magnitude in East
            position[1] += magnitude;
            break;

            case 'S': // Move by magnitude in South
            position[0] -= magnitude;
            break;

            case 'W': // Move by magnitude in West
            position[1] -= magnitude;
            break;

            case 'L': // move left by magnitude
            direction = (direction - magnitude) % 360;
            break;

            case 'R': // move right by magnitude
            direction = (direction + magnitude) % 360;
            break;
        }   
        fgetc(file);
    }
    fclose(file);

    long int result = abs(position[0]) + abs(position[1]);
    printf("Infos : Position on N-S [%d] | Position on E-W [%d]\n", position[0], position[1]);
    printf("Result : %lu", result);
    return 0;
}