#include <iostream>
#include <vector>

#define NUMBERS_AMOUNT 1000
#define LAST_NUMBER 1000
#define FIRST_NUMBER 1
#define NUMBERS_TO_ERASE 2

#define INC 1
#define DEC 1

#define ZERO 0

int random(const int& min, const int& max)
{
    if (ZERO == max && max == min)
    {
        return ZERO;
    }

    return min + (std::rand() % (max - min + INC));
}

int algorithm_way(void)
{
    std::cout << "Algorithm Way" << std::endl;
    std::cout << "=============" << std::endl;

    int i = 0, index = 0, sum = 0;

    std::vector<int> board;
    board.reserve(NUMBERS_AMOUNT);

    for (i = FIRST_NUMBER; i <= NUMBERS_AMOUNT; i++)
    {
        board.emplace_back(i);
    }

    do
    {
        sum = 0;

        for (i = 0; i < NUMBERS_TO_ERASE; i++)
        {
            index = random(0, board.size() - DEC);
            sum += board[index];
            board.erase(board.begin() + index);
        }

        board.emplace_back(sum);
    } while (board.size() != 1);

    int last_number = board[0];
    std::cout << "Last number: " << last_number << std::endl;

    board.clear();

    return last_number;
}

int math_way(void)
{
    std::cout << "Mathematical Way" << std::endl;
    std::cout << "================" << std::endl;

    int a1 = FIRST_NUMBER;
    int an = LAST_NUMBER;
    int n = NUMBERS_AMOUNT;

    int sum = ((n * (a1 + an)) / 2);

    std::cout << "Last number: " << sum << std::endl;
    return sum;
}

int main()
{
    std::cout << "Regular Numbers from 1-1000:\n";
    std::cout << "============================\n";

    std::cout << ((algorithm_way() == math_way()) ? "Both ways are equal" : "Both ways are not equal") << std::endl;

    return 0;
}