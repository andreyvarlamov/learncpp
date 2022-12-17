// 11.x - Q6, Q7
#include <algorithm>
#include <array>
#include <cassert>
#include <ctime>
#include <iostream>
#include <random>

enum class Rank
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,

    max_ranks
};

enum class Suit
{
    clubs,
    diamonds,
    hearts,
    spades,

    max_suits
};

struct Card
{
    Rank rank { };
    Suit suit { };
};

using Deck = std::array<Card, 52>;

void printCard(const Card& card)
{
    char rank_char { };
    char suit_char { };

    switch (card.rank)
    {
    case Rank::two:
        rank_char = '2';
        break;
    case Rank::three:
        rank_char = '3';
        break;
    case Rank::four:
        rank_char = '4';
        break;
    case Rank::five:
        rank_char = '5';
        break;
    case Rank::six:
        rank_char = '6';
        break;
    case Rank::seven:
        rank_char = '7';
        break;
    case Rank::eight:
        rank_char = '8';
        break;
    case Rank::nine:
        rank_char = '9';
        break;
    case Rank::ten:
        rank_char = '0';
        break;
    case Rank::jack:
        rank_char = 'J';
        break;
    case Rank::queen:
        rank_char = 'Q';
        break;
    case Rank::king:
        rank_char = 'K';
        break;
    case Rank::ace:
        rank_char = 'A';
        break;
    default:
        rank_char = '?';
        break;
    }

    switch (card.suit)
    {
    case Suit::clubs:
        suit_char = 'C';
        break;
    case Suit::diamonds:
        suit_char = 'D';
        break;
    case Suit::hearts:
        suit_char = 'H';
        break;
    case Suit::spades:
        suit_char = 'S';
        break;
    default:
        suit_char = '?';
        break;
    }

    std::cout << rank_char << suit_char;
}

void printDeck(const Deck& deck)
{
    for(Card card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << '\n';
}

Deck createDeck()
{
    Deck deck { };

    size_t index { 0 };
    for (int i { 0 }; i < static_cast<int>(Suit::max_suits); ++i)
    {
        for (int j { 0 }; j < static_cast<int>(Rank::max_ranks); ++j)
        {
            deck[index].suit = static_cast<Suit>(i);
            deck[index].rank = static_cast<Rank>(j);

            ++index;
        }
    }

    return deck;
}

void shuffleDeck(Deck& deck)
{
    static std::mt19937 mt { static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
    switch (card.rank)
    {
    case Rank::two:   return 2;
    case Rank::three: return 3;
    case Rank::four:  return 4;
    case Rank::five:  return 5;
    case Rank::six:   return 6;
    case Rank::seven: return 7;
    case Rank::eight: return 8;
    case Rank::nine:  return 9;
    case Rank::ten:   return 10;
    case Rank::jack:  return 10;
    case Rank::queen: return 10;
    case Rank::king:  return 10;
    case Rank::ace:   return 11;
    default:
        assert(false && "should never happen");
        return 0;
    }
}

bool playBlackjack(const Deck& deck)
{
    int playerScore { };
    int dealerScore { };

    auto currentCard { deck.begin() }; // returns iterator (I think it overloads * and ++)
    // Dealer gets one card
    dealerScore += getCardValue(*currentCard);
    ++currentCard;
    std::cout << "Dealer draws one card. Score: " << dealerScore << '\n';

    // Player gets two cards
    playerScore += getCardValue(*currentCard);
    ++currentCard;
    playerScore += getCardValue(*currentCard);
    ++currentCard;

    std::cout << "Player draws two cards. Score: " << playerScore << '\n';

    // Player's turn: hit until stand; if > 21 - bust
    while (true)
    {
        char hitChar { };
        std::cout << "Hit(y/n)? ";
        std::cin >> hitChar; // TODO: Do this safely

        if (hitChar != 'y')
        {
            break;
        }

        playerScore += getCardValue(*currentCard);
        ++currentCard;

        std::cout << "You hit. Score: " << playerScore << '\n';

        if (playerScore > 21)
        {
            std::cout << "You lose!\n";
            return false;
        }
    }

    // Dealer's turn: draw until score > 17; if > 21 - bust
    while (dealerScore <= 17)
    {
        dealerScore += getCardValue(*currentCard);
        ++currentCard;

        std::cout << "Dealer draws. Score: " << dealerScore << '\n';

        if (dealerScore > 21)
        {
            std::cout << "Dealer loses. You win!\n";
            return true;
        }
    }

    // If no bust yet: compare scores. If tie: dealer wins
    if (playerScore > dealerScore)
    {
        std::cout << "You win!\n";
        return true;
    }
    else
    {
        std::cout << "You lose!\n";
        return false;
    }

}

int main()
{
    Deck deck { createDeck() };
    if (false) // No cheating!
    {
        std::cout << "Sorted deck:\n";
        printDeck(deck);

        std::cout << '\n';

        shuffleDeck(deck);
        std::cout << "Shuffled deck:\n";
        printDeck(deck);

        std::cout << '\n';
    }
    else
    {
        shuffleDeck(deck);
        std::cout << "Prepare table... Shuffle deck...\n";
    }

    std::cout << "Begin a game of blackjack!\n";

    playBlackjack(deck);
    return 0;
}
