/* Header files */

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

/* Two constants defined for determining weather hands
 are flushes or straights */

 #define FALSE 0
 #define TRUE 1

/* Function Prototypes */

void print_greeting();
int get_bet();
char get_suit(int suit);
char get_rank(int rank);
void get_first_hand(int card_rank[], int card_suit[]);
void get_final_hand(int card_rank[], int card_suit[],int final_rank[],
                    int final_suit[], int ranks_in_hand[], int suits_in_hand[]);
int analyze_hand(int ranks_in_hand[], int suits_in_hand[]);

main()
{
    int bet; 
    int bank = 100;
    int i;
    int card_rank[5]; // Will one of 13 values(Ace-King)
    int card_suit[5]; // Will be one of 4(Clubs, Diamonds, Hearts, Spades)
    int final_rank[5];
    int final_suit[5];
    int ranks_in_hand[13]; // Used for evaluating the final hand 
    int suits_in_hand[4]; // Used for evaluating the final hand
    int winnings;
    char suit, rank, still_play;
    time_t t;

// Calling the function once
    print_greeting();
//  loop runs each time the user plays a hand or draw poker
    do{
        bet = get_bet();

        srand(time(&t));
        get_first_hand(card_rank, card_suit);
        printf("Your five cards: \n");
        for(i = 0; i < 5; i++)
        {
            suit = get_suit(card_suit[i]);
            rank = get_rank(card_rank[i]);
            printf("Card #%d: %c%c\n", i + 1, rank, suit);
        }
// These two arrays are used to figure out the value of 
// the player's hand. However, they must be zeroed out
// in case the user plays multiple hands.
        for(i = 0; i < 4; i++)
        {
            suits_in_hand[i] = 0;
        }
        for(i = 0; i < 13; i++)
        {
            ranks_in_hand[i] = 0;
        }
        get_final_hand(card_rank, card_suit, final_rank, 
                       final_suit, ranks_in_hand,suits_in_hand);
        printf("Your five final cards: \n");
        for(i = 0; i < 5; i++)
        {
            suit = get_suit(final_suit[i]);
            rank = get_rank(final_rank[i]);
            printf("Card #%d: %c%c\n", i, rank, suit);
        }
        winnings = analyze_hand(ranks_in_hand, suits_in_hand);
            printf("You won %d!\n", bet*winnings);
        bank = bank - bet + (bet * winnings);
            printf("\nYour bank is now %d.\n",bank);
            printf("\nDo you want to play again?");
        scanf(" %c", &still_play);
    }while(toupper(still_play)== 'Y');
    return;       
}
/****************************************************************/

// Print a quick greeting as well as tell the users the value
// of different winning hands

void print_greeting()
{
    printf("****************************");
    printf("\n\n\tWelcome to the Cassino\n\n");
    printf("\tHome of Video Draw Poker\n\n");
    printf("****************************");
    printf("Here are the rules:\n");
    printf("You start with 100 credits, and you make a bet from");
    printf("1 to 5 credits.\n");
    printf("cards to keep ");
    printf("or discard.\n");
    printf("You want to make the best possible hand.\n");
    printf("\nHere is the table for winnings (assuming a ");
    printf("bet of 1 credit):");
    printf("\nPair\t\t\t\t1 credit");
    printf("\nTwo pairs\t\t\t2 credits");
    printf("\nThree of a kind\t\t\t3 credits");
    printf("\nStraight\t\t\t4 credits");
    printf("\nFlush\t\t\t\t5 credits");
    printf("\nFull House\t\t\t8 credits");
    printf("\nFour of a Kind\t\t\t10 credits");
    printf("\nStraight Flush\t\t\t20 credits");
    printf("\n\nHave fun!!\n\n");
}
// Function to deal the first five cards
void get_first_hand(int card_rank[], int card_suit[])
{
    int i, j;
    int card_dup;

    for(i = 0; i < 5; i++)
    {
        card_dup = 0;
        do{
// Card is one of 13 (2-10, J, Q, K, A)
        card_rank[i] = (rand() % 13);
        card_suit[i] = (rand() % 4);
            for(j = 0; j < i; j++)
            {
                if(( card_rank[i] == card_rank[j]) && (card_suit[i] == card_suit[j]))
                {
                    card_dup = 1;
                }
            }
        }while(card_dup == 1);
    }
}
// Function that changes the suit integer value
// to a charcacter representing the suit
char get_suit(int suit)
{
    switch(suit)
    {
        case 0:
            return('c');
        case 1:
            return('d');
        case 2:
            return('h');
        case 3:
            return('s');
    }
}
// Changes the rank integer value to a character representing the rank
char get_rank(int rank)
{
    switch(rank)
    {
        case 0:
            return('A');
        case 1:
            return('2');
        case 2:
            return('3');
        case 3:
            return('4');
        case 4:
            return('5');
        case 5:
            return('6');
        case 6:
            return('7');
        case 7:
            return('8');
        case 8:
            return('9');
        case 9:
            return('T');
        case 10:
            return('J');
        case 11:
            return('Q');
        case 12:
            return('K');    
    }
}
// Get the user's bet between 1 and 5

int get_bet()
{
    int bet;
    do{
        printf("How much do you want to bet?(Enter a number)");
        printf("1 to 5, or 0 to quit the game: ");scanf(" %d", &bet);

        if(bet >= 1 && bet <= 5)
        {
            return(bet);
        }
        else if(bet == 0)
        {
            exit(1);
        }
        else
        {
            printf("\n\nPlease enter a bet from 1-5 or ");
            printf("0 to quit the game.\n");
        }
    }while((bet < 0) || (bet > 5) );
}
// Reviews the final hand and determines the value of the hand
int analyze_hand(int ranks_in_hand[], int suits_in_hand[])
{
    int num_consec = 0;
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;

    for(suit = 0; suit < 4; suit++)
        if(suits_in_hand[suit] == 5)
            flush = TRUE;
    rank = 0;
    while(ranks_in_hand[rank] == 0)
        rank++;
    for(; rank < 13 && ranks_in_hand[rank]; rank++)
        num_consec++;
    if (num_consec == 5)
    {
        straight = TRUE;
    }
    for(rank = 0; rank < 13; rank++)
    {
        if (ranks_in_hand[rank] == 4)
            four = TRUE;
        if(ranks_in_hand[rank] == 3)
            three = TRUE;
        if(ranks_in_hand[rank] == 2)
                pairs++;
    }
    if(straight && flush)
    {
        printf("Straight flush\n\n");
        return(20);
    }
    else if(four)
    {
        printf("Four of a kind\n\n");
        return(10);
    }
    else if(three && pairs ==1)
    {
        printf("Full house\n\n");
        return(8);
    }
    else if(flush)
    {
        printf("Flush\n\n");
        return(5);
    }
    else if(straight)
    {
        printf("Straight\n\n");
        return (4);
    }
    else if(three)
    {
        printf("Three of a kind\n\n");
        return(3);
    }
    else if(pairs == 2)
    {
        printf("Two pairs\n\n");
        return(2);
    }
    else if(pairs == 1)
    {
        printf("Pair\n\n");
        return(1);
    }
    else
    {
        printf("High Card\n\n");
        return (0);
    }
}
// Looks through each of the five cards in the first hand 
// and asks the user if they want to keep the card. If they
// say no, they get a replacement card.
void get_final_hand(int card_rank[], int card_suit[],int final_rank[],
                    int final_suit[], int ranks_in_hand[], int suits_in_hand[])
{
    int i, j, card_dup;
    char suit, rank, ans;

    for(i = 0; i < 5; i++)
    {
        suit = get_suit(card_suit[i]);
        rank = get_rank(card_rank[i]);
        printf("Do you want to keep card #%d: %c%c?",i + 1, rank, suit);
        printf("\nPlease answer(Y/N): ");
        scanf(" %c", &ans);
        if(toupper(ans) == 'Y')
        {
            final_rank[i] = card_rank[i];
            final_suit[i] = card_suit[i];
            ranks_in_hand[final_rank[i]]++;
            suits_in_hand[final_suit[i]]++;
            continue;
        }
        else if(toupper(ans) == 'N')
        {
            card_dup = 0;
            do{
                card_dup = 0;
                final_rank[i] = (rand() % 13);
                final_suit[i] = (rand() % 4);
                for(j = 0; j < 5; j++)
                {
                    if((final_rank[i]) == card_rank[j] && (final_suit[i] == card_suit[j]))
                    {
                        card_dup = 1;
                    }
                }
                for(j = 0; j < i; j++)
                {
                    if((final_rank[i]) == final_rank[j] && (final_suit[i] == final_suit[j]))
                    {
                        card_dup = 1;
                    }
                }
            }while(card_dup == 1);
            ranks_in_hand[final_rank[i]]++;
            suits_in_hand[final_suit[i]]++;
        }
    }

}

