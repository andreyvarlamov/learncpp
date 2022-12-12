// 7.x - Quiz - Questions 3 and 4

#include <iostream>
#include <limits>
#include <random>

int main()
{
    while (true)
    {
        std::random_device rd;
        std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
        std::mt19937 mt { ss };

        std::uniform_int_distribution die { 1, 100 };

        int rand_num { die(mt) };

        bool guessed_correctly { false };

        std::cout << "Try to guess a number between 1 and 100. You have 7 tries.\n";

        for (int i { }; i < 7; ++i)
        {
            int guess { };

            // ugly but ok
            bool valid_guess { true };

            do
            {
                if (!valid_guess)
                {
                    if (std::cin.fail())
                    {
                        std::cin.clear(); // put back in normal operation mode
                        // remove bad input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cout << "Invalid input. Try again...\n";
                }

                std::cout << "Guess #" << i + 1 << ": ";
                std::cin >> guess;
                // remove erroneous input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                valid_guess = !(std::cin.fail() || guess < 1 || guess > 100);
            }
            while(!valid_guess);

            if (guess > rand_num)
            {
                std::cout << "Your guess is too high.\n";
            }
            else if (guess < rand_num)
            {
                std::cout << "Your guess is too low.\n";
            }
            else
            {
                std::cout << "Correct! You win!\n";
                guessed_correctly = true;
                break;
            }
        }

        if (!guessed_correctly)
        {
            std::cout << "Sorry, you lose. The correct number was " << rand_num << '\n';
        }

        char play_again_char { };
        // still ugly but ok
        bool is_valid_input { false };

        while (!is_valid_input)
        {
            std::cout << "Would you like to play again (y/n)? ";
            std::cin >> play_again_char;
            // remove extraneous input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (play_again_char)
            {
                case 'y':
                case 'n':
                    is_valid_input = true;
                    break;
                default:
                    is_valid_input = false;
            }
        }

        if (play_again_char == 'n')
        {
            break;
        }
    }

    std::cout << "Thank you for playing!\n";

    return 0;
}
