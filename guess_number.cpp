#include <iostream>

int main()
{
    std::srand(std::time(0));                  // 使用当前时间作为随机数种子
    int random_number = std::rand() % 100 + 1; // 生成1到100之间的随机数
    int guess;
    int attempts = 0;

    std::cout << "Welcome to the Guess Number Game!" << std::endl;
    std::cout << "I have selected a number between 1 and 100. Try to guess it!" << std::endl;

    do
    {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess > random_number)
        {
            std::cout << "Too high! Try again." << std::endl;
        }
        else if (guess < random_number)
        {
            std::cout << "Too low! Try again." << std::endl;
        }
        else
        {
            std::cout << "Congratulations! You've guessed the number in " << attempts << " attempts." << std::endl;
        }
    } while (guess != random_number);

    return 0;
}
