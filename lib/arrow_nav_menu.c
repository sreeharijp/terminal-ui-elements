#include "arrow_nav_menu.h"

int arrow_key_navigate(char prompt[][30], int num_of_ops, int x_cor, int y_cor)
{
    char tx_buffer;
    int run_flag = 1;
    int *pointer = malloc(num_of_ops * sizeof(int));
    int ret = 0;

    struct termios orig_termios;
    struct termios new_termios;

    // Disable canonical mode and echoing so that we can read key presses immediately

    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    memset(pointer, 0, num_of_ops * sizeof(int));
    pointer[0] = 1;
    while (run_flag)
    {
        printf("\033[%d;%dHPress Enter to Select\r\nArrow Keys to move cursor\r\n", x_cor, y_cor);
        for (int i = 0; i < num_of_ops; i++)
        {
            if (pointer[i] == 1)
            {
                printf("\x1b[44m");
            }
            else
            {
                printf("\x1b[0m");
            }
            printf("%-30s", prompt[i]);
            printf("\x1b[0m");
            if (pointer[i] == 1)
            {
                printf("\t<==\r\n");
            }
            else
            {
                printf("                     \r\n");
            }
        }
        tx_buffer = getchar();
        // Check for arrow keys
        if (tx_buffer == 27)
        {                          // Escape key, indicating an escape sequence
            tx_buffer = getchar(); // Read the next character
            if (tx_buffer == 91)
            {                          // '[' character, indicating an arrow key
                tx_buffer = getchar(); // Read the arrow key direction
                int temp;
                switch (tx_buffer)
                {
                case 'A':
                    // printf("Up Arrow\r\n");
                    temp = pointer[0];
                    for (int j = 0; j != num_of_ops - 1; j++)
                    {
                        pointer[j] = pointer[j + 1];
                    }
                    pointer[num_of_ops - 1] = temp;
                    break;
                case 'B':
                    // printf("Down Arrow\r\n");
                    temp = pointer[num_of_ops - 1];
                    for (int j = num_of_ops - 1; j != 0; j--)
                    {
                        pointer[j] = pointer[j - 1];
                    }
                    pointer[0] = temp;
                    break;
                case 'C':
                    printf("Right Arrow Pressed\n");
                    break;
                case 'D':
                    printf("Left Arrow Pressed\n");
                    break;
                default:
                    // Handle other arrow keys or unknown sequences
                    break;
                }
            }
        }
        else if (tx_buffer == '\n')
        {
            // printf("Enter\r\n");
            for (int j = 0; j < num_of_ops; j++)
            {
                if (pointer[j] == 1)
                {
                    ret = j;
                    run_flag = 0;
                    break;
                }
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    printf("\x1b[2J");
    return ret + 1;
}
