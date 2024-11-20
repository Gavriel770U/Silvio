#include <iostream>
#include <vector>
#include <cstdlib>

#define NUMBERS_AMOUNT 2017
#define LAST_NUMBER 2017
#define FIRST_NUMBER 1
#define NUMBERS_TO_ERASE 2

#define INC 1
#define DEC 1

#define ZERO 0

#define COLOR_TO_STRING(color) \
    ((color) == RED ? "RED" : \
     (color) == BLUE ? "BLUE" : \
     (color) == YELLOW ? "YELLOW" : "UNKNOWN")


typedef enum Color
{
    RED = 1,
    BLUE = 2,
    YELLOW = 3,
} Color;

typedef struct Number
{
    Color color;
    int value;

    Number() : color(RED), value(1) {}

    Number(const Color& color, const int& value) : color(color), value(value) {}

    Number(const Number& n) : color(n.color), value(n.value) {}

} Number;

int random(const int& min, const int& max)
{
    if (min == ZERO && max == ZERO)
    {
        return ZERO;
    }
    return min + (std::rand() % (max - min + INC));
}

Number algorithm_way(void)
{
    std::cout << "Algorithm Way" << std::endl;
    std::cout << "=============" << std::endl;

    int blue_amount = 0, red_amount = 0, yellow_amount = 0;

    std::vector<Number> board;
    board.reserve(NUMBERS_AMOUNT);

    do
    {
        blue_amount = random(2, NUMBERS_AMOUNT - DEC);
        red_amount = random(2, NUMBERS_AMOUNT - DEC - blue_amount);
        yellow_amount = NUMBERS_AMOUNT - blue_amount - red_amount;
    } while ((yellow_amount <= 0) || (blue_amount % 2 != 0) || (red_amount % 2 != 0) || (yellow_amount % 2 == 0));

    std::cout << "Blue Amount: " << blue_amount << std::endl;
    std::cout << "Red Amount: " << red_amount << std::endl;
    std::cout << "Yellow Amount: " << yellow_amount << std::endl;

    for (int i = FIRST_NUMBER; i <= NUMBERS_AMOUNT; i++)
    {
        Color color;
        bool flag = false;

        do
        {
            color = (Color)(random(1, 3));

            switch (color)
            {
            case RED:
                if (red_amount > 0) { red_amount--; flag = true; }
                break;
            case BLUE:
                if (blue_amount > 0) { blue_amount--; flag = true; }
                break;
            case YELLOW:
                if (yellow_amount > 0) { yellow_amount--; flag = true; }
                break;
            }
        } while (!flag);

        board.emplace_back(color, i);
    }

    while (board.size() > 1)
    {
        int colorflags = 0;
        int sum = 0;

        for (int i = 0; i < NUMBERS_TO_ERASE; i++)
        {
            bool flag = false;

            do
            {
                int index = random(0, board.size() - DEC);

                switch (board[index].color)
                {
                case RED:
                    if ((colorflags & (1 << 0)) == 0) // RED bit not set
                    {
                        colorflags |= (1 << 0); // Set RED bit
                        sum += board[index].value;
                        board.erase(board.begin() + index);
                        flag = true;
                        // std::cout << "CHOSE RED" << std::endl;
                    }
                    break;

                case BLUE:
                    if ((colorflags & (1 << 1)) == 0) // BLUE bit not set
                    {
                        colorflags |= (1 << 1); // Set BLUE bit
                        sum += board[index].value;
                        board.erase(board.begin() + index);
                        flag = true;
                        // std::cout << "CHOSE BLUE" << std::endl;
                    }
                    break;

                case YELLOW:
                    if ((colorflags & (1 << 2)) == 0) // YELLOW bit not set
                    {
                        colorflags |= (1 << 2); // Set YELLOW bit
                        sum += board[index].value;
                        board.erase(board.begin() + index);
                        flag = true;
                        // std::cout << "CHOSE YELLOW" << std::endl;
                    }
                    break;
                }
            } while (!flag);
        }

        // Determine the new color
        Color new_color = RED;
        if (((colorflags & (1 << 0)) != 0) && ((colorflags & (1 << 2)) != 0))
        {
            new_color = BLUE;
        }
        else if (((colorflags & (1 << 0)) != 0) && ((colorflags & (1 << 1)) != 0))
        {
            new_color = YELLOW;
        }

        board.emplace_back(new_color, sum);
    }

    Number last_number = board[0];
    std::cout << "Last number value: " << last_number.value << " Color: " << COLOR_TO_STRING(last_number.color) << std::endl;

    return last_number;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << "Colorful Numbers from 1-2017:\n";
    std::cout << "============================\n";

    algorithm_way();

    return 0;
}
