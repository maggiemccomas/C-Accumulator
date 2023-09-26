#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"

/*
* C program that displays values in various base representations including decimal, octal, hexadecimal, and binary based on current value of program's accumulator. 
* The program also performs various bit-wise and arithmetic operations involving the accumulator.
* Maggie McComas
*/

/*
* Purpose: Convert bin str to short
* Input: char *bin
* Output: unsigned short value
*/
unsigned short get_binary_op(char *bin)
{
    short value = 0;
    int col = 1;
    int i; // variable for for loop

    for (i = strlen(bin) - 1; i >= 0; i--)
    {
        if (bin[i] == '1')
        {
            value = value + col;
        }
        col = col * 2;
    }
    return value;
}

/*
* Purpose: Convert acc to binary str for output
* Input: short acc, char *bin
* Output: void but changes acc from short to binary str
*/
void convert_to_binary(short acc, char *bin)
{
    bin_str b;
    float col = pow(2, 15);
    unsigned short uacc;
    int count = 0;
    int i; // variable for for loop
    int j; // variable for second for loop

    uacc = acc;

    for (i = 0; i < 16; i++)
    {
        if (uacc >= col)
        {
            b[i] = '1';
            uacc = uacc - col;
        }
        else
        {
            b[i] = '0';
        }
        col = col / 2;
    }

    for (j = 0; j < 16; j++)
    {
        bin[count] = b[j];
        count++;
        if (j % 4 == 3 && j != 15)
        {
            bin[count] = ' ';
            count++;
        }
    }
    bin[count] = '\0';
}

/*
* Purpose: read in numeric value in mode
* Input: char mode
* Output: short num
*/
short get_operand(char mode)
{
    short num = 0;
    bin_str b;
    bin_str b_leading;
    int i; // variable for for loop for creating string of leading zeros

    switch (mode)
    {
    case 'o':
        scanf("%6ho", &num);
        printf("%ho\n", num);
        break;
    case 'h':
        scanf("%4hx", &num);
        printf("%hX\n", num);
        break;
    case 'b':
        scanf("%s", b);
        printf("%s\n", b);
        if (strlen(b) < 16) // if entered binary string is less than 16 adds 0 to the left to make it 16 bits long
        {
            for (i = 0; i < (16 - strlen(b)); i++)
            {
                b_leading[i] = '0';
            }

            b_leading[i+1] = '\0';

            int j = 0; // index for b_leading
            int k; // index for b

            while (b_leading[j] != '\0')
            {
                j++;
            }

            for (k = 0; k < strlen(b); k++)
            {
                b_leading[j] = b[k];
                j++;
            }

            b_leading[j] = '\0';
            num = get_binary_op(b_leading);
        }
        else
        {
            num = get_binary_op(b);
        }
        break;
    default:
        scanf("%6hd", &num);
        printf("%hd\n", num);
    }
    return num;
}

/*
* Purpose: print out accumulator values
* Input: short acc, char mode
* Output: nothing
*/
void print_acc(short acc, char mode)
{
    bin_str b;

    printf("\n ****************************************\n");
    switch (mode)
    {
    case 'o':
        printf(" * Accumulator: \t"
               "Input Mode: Oct *\n");
        break;
    case 'h':
        printf(" * Accumulator: \t"
               "Input Mode: Hex *\n");
        break;
    case 'b':
        printf(" * Accumulator: \t"
               "Input Mode: Bin *\n");
        break;
    default:
        printf(" * Accumulator: \t"
               "Input Mode: Dec *\n");
    }
    convert_to_binary(acc, b);
    printf(" *   Binary  :  %s ", b);
    printf("%-4s*\n", "");
    printf(" *   Hex     :  %04hX ", acc);
    printf("%-19s*\n", "");
    printf(" *   Octal   :  %06ho ", acc);
    printf("%-17s*\n", "");
    printf(" *   Decimal :  %-6hd ", acc);
    printf("%-17s*\n", "");
    printf(" ****************************************\n");
}

/*
* Purpose: print menu, get option until valid
* Input: none
* Output: char option
*/
char print_menu(void)
{
    char input_string[10];
    char valid_option;
    int input_letter_valid = 0; // true or false int
    int input_length_valid = 1; // true or false int
    char valid_string[17] = {'b', 'o', 'h', 'd', 'c', 's', 'q', '+', '-', '&', '|', '^', '~', '<', '>', 'n', '\0'};
    int i; // variable for for loop to loop through valid string
    int j; // variable for for loop to loop through valid string (in invalid case)

    printf("\n Please select one of the following options: \n");
    printf("\n B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator \n");
    printf(" O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator \n");
    printf(" H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator \n");
    printf(" D  Decimal Mode            ~  Complement Accumulator \n");
    printf("\n C  Clear Accumulator       <  Shift Accumulator Left \n");
    printf(" S  Set Accumulator         >  Shift Accumulator Right \n");
    printf("\n Q  Quit \n");
    printf("\n Option: ");
    scanf("%s", input_string);

    char input = (char)tolower(input_string[0]);

    if (strlen(input_string) != 1)
    {
        input_length_valid = 0;
    }

    for (i = 0; i < strlen(valid_string); i++)
    {
        if (valid_string[i] == input)
        {
            input_letter_valid = 1;
        }
    }

    while (input_length_valid == 0 || input_letter_valid == 0)
    {
        printf("%s\n", input_string);
        printf("\n Invalid option: %s\n", input_string);

        printf("\n Please select one of the following options: \n");
        printf("\n B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator \n");
        printf(" O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator \n");
        printf(" H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator \n");
        printf(" D  Decimal Mode            ~  Complement Accumulator \n");
        printf("\n C  Clear Accumulator       <  Shift Accumulator Left \n");
        printf(" S  Set Accumulator         >  Shift Accumulator Right \n");
        printf("\n Q  Quit \n");
        printf("\n Option: ");
        scanf("%s", input_string);
        input = (char)tolower(input_string[0]);

        input_letter_valid = 0;

        if (strlen(input_string) != 1)
        {
            input_length_valid = 0;
        }
        else
        {
            input_length_valid = 1;
        }

        for (j = 0; j < strlen(valid_string); j++)
        {
            if (valid_string[j] == input)
            {
                input_letter_valid = 1;
            }
        }
    }

    switch (input)
    {
    case 'c':
        printf("%c\n", input_string[0]);
        valid_option = 'c';
        break;
    case 'o':
        printf("%c\n", input_string[0]);
        printf(" Mode is Octal \n");
        valid_option = 'o';
        break;
    case 'h':
        printf("%c\n", input_string[0]);
        printf(" Mode is Hexadecimal \n");
        valid_option = 'h';
        break;
    case 'q':
        printf("%c\n", input_string[0]);
        valid_option = 'q';
        break;
    case 's':
        printf("%c\n", input_string[0]);
        valid_option = 's';
        break;
    case '+':
        printf("%c\n", input_string[0]);
        valid_option = '+';
        break;
    case '-':
        printf("%c\n", input_string[0]);
        valid_option = '-';
        break;
    case '&':
        printf("%c\n", input_string[0]);
        valid_option = '&';
        break;
    case '|':
        printf("%c\n", input_string[0]);
        valid_option = '|';
        break;
    case '^':
        printf("%c\n", input_string[0]);
        valid_option = '^';
        break;
    case '~':
        printf("%c\n", input_string[0]);
        valid_option = '~';
        break;
    case 'n':
        printf("%c\n", input_string[0]);
        valid_option = 'n';
        break;
    case '<':
        printf("%c\n", input_string[0]);
        valid_option = '<';
        break;
    case '>':
        printf("%c\n", input_string[0]);
        valid_option = '>';
        break;
    case 'b':
        printf("%c\n", input_string[0]);
        printf(" Mode is Binary \n");
        valid_option = 'b';
        break;
    default:
        printf("%c\n", input_string[0]);
        printf(" Mode is Decimal \n");
        valid_option = 'd';
    }
    return valid_option;
}

/*
* Purpose: call get_operand to get val in mode to add to accum 
* also detect whether positive or negative overflow occured
* Dependent: get_operand(mode)
* Input: short *acc and char mode
* Output: none/ void
*/
void add(short *acc, char mode)
{
    short orig_acc = *acc;

    switch (mode)
    {
    case 'o':
        printf(" Enter octal value: ");
        break;
    case 'h':
        printf(" Enter hex value: ");
        break;
    case 'b':
        printf(" Enter binary value: ");
        break;
    default:
        printf(" Enter decimal value: ");
    }

    short new_acc = get_operand(mode);
    *acc = orig_acc + new_acc;

    if (orig_acc >= 0 && new_acc >= 0)
    {
        if (*acc < 0)
        {
            printf(" Positive Overflow \n");
        }
    }

    if (orig_acc < 0 && new_acc < 0)
    {
        if (*acc >= 0)
        {
            printf(" Negative Overflow \n");
        }
    }
}

/*
* Purpose: call get_operand to get val in mode to subtract from accum 
* also detect whether positive or negative overflow occured
* Dependent: get_operand(mode)
* Input: short *acc and char mode
* Output: none/ void
*/
void subtract(short *acc, char mode)
{
    short orig_acc = *acc;

    switch (mode)
    {
    case 'o':
        printf(" Enter octal value: ");
        break;
    case 'h':
        printf(" Enter hex value: ");
        break;
    case 'b':
        printf(" Enter binary value: ");
        break;
    default:
        printf(" Enter decimal value: ");
    }

    short new_acc = get_operand(mode);
    *acc = orig_acc - new_acc;

    if (orig_acc >= 0 && new_acc < 0)
    {
        if (*acc < 0)
        {
            printf(" Positive Overflow \n");
        }
    }

    if (orig_acc < 0 && new_acc >= 0)
    {
        if (*acc >= 0)
        {
            printf(" Negative Overflow \n");
        }
    }
}

/*
* Purpose: main menu loop, execute option or call appropriate function
* Dependent: print_acc(acc, mode), print_menu(), get_operand(mode), add(*acc, mode), subtract(*acc, mode), and exit(int)
* Input: none
* Output: exit(0) just exits program when function ends
*/
int main(void)
{
    char option = 'c';
    short acc = 0;
    char mode = 'd';
    short second_acc = 0; // used for methods that need additional operand
    int shift = 0;        // used for shift operands

    while (option != 'q')
    {
        print_acc(acc, mode);
        option = print_menu();
        switch (option)
        {
        case 's':
            switch (mode)
            {
            case 'o':
                printf(" Enter octal value: ");
                break;
            case 'h':
                printf(" Enter hex value: ");
                break;
            case 'b':
                printf(" Enter binary value: ");
                break;
            default:
                printf(" Enter decimal value: ");
            }
            acc = get_operand(mode);
            break;
        case 'c':
            acc = 0;
            break;
        case 'o':
            mode = 'o';
            break;
        case 'h':
            mode = 'h';
            break;
        case 'd':
            mode = 'd';
            break;
        case 'b':
            mode = 'b';
            break;
        case '+':
            add(&acc, mode);
            break;
        case '-':
            subtract(&acc, mode);
            break;
        case '&':
            switch (mode)
            {
            case 'o':
                printf(" Enter octal value: ");
                break;
            case 'h':
                printf(" Enter hex value: ");
                break;
            case 'b':
                printf(" Enter binary value: ");
                break;
            default:
                printf(" Enter decimal value: ");
            }
            second_acc = get_operand(mode);
            acc = acc & second_acc;
            break;
        case '|':
            switch (mode)
            {
            case 'o':
                printf(" Enter octal value: ");
                break;
            case 'h':
                printf(" Enter hex value: ");
                break;
            case 'b':
                printf(" Enter binary value: ");
                break;
            default:
                printf(" Enter decimal value: ");
            }
            second_acc = get_operand(mode);
            acc = acc | second_acc;
            break;
        case '^':
            switch (mode)
            {
            case 'o':
                printf(" Enter octal value: ");
                break;
            case 'h':
                printf(" Enter hex value: ");
                break;
            case 'b':
                printf(" Enter binary value: ");
                break;
            default:
                printf(" Enter decimal value: ");
            }
            second_acc = get_operand(mode);
            acc = acc ^ second_acc;
            break;
        case '~':
            acc = ~acc;
            break;
        case 'n':
            acc = acc * -1;
            break;
        case '<':
            printf(" Enter number of positions to left shift accumulator: ");
            scanf("%d", &shift);
            printf("%d\n", shift);
            acc = acc << shift;
            break;
        case '>':
            printf(" Enter number of positions to right shift accumulator: ");
            scanf("%d", &shift);
            printf("%d\n", shift);
            acc = acc >> shift;
            break;
        default:
            mode = 'q';
        }
    }
    exit(0);
}