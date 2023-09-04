# poker_game

## Description
This program plays draw poker. Users can play
as often they want, betting between 1 and 5. They
are dealt 5 cards and then get to chose which cards to keep,
and which cards to replace. The new hand is then reviewed and the 
user's payout is set based on the value of the hand. The user's new
bankroll is displayed as they are given the option to continue.

## Features
-Accepts input via the command line interface.
-Allows users to view the cards.
-Allows users to discard the cards.
-Allows users to bet credit. 


## Instalation
1.Clone the repo
-- "git clone git@github.com:Bele2244/poker_game_C.git"
2.Compile the program using a C compiler
-- gcc main.c -o program

## Usage
1.Open the command prompt or terminal.
2.Navigate to the program directory.
3.Run the program using the "./main" command.
4.Follow the on-screen instrucitons to play the game. 

## Examples
./main
//
How much do you want to bet?(Enter a number)1 to 5, or 0 to quit the game: 2
//
Your five cards: 
Card #1: 6s
Card #2: 5d
Card #3: Ah
Card #4: 6h
Card #5: 7c
Do you want to keep card #1: y
//
Your five final cards: 
Card #0: 6s
Card #1: 5d
Card #2: Ah
Card #3: 6h
Card #4: 7c
//
Your five final cards: 
Card #0: 6s
Card #1: 5d
Card #2: Ah
Card #3: 6h
Card #4: 7c
Pair
//
You won 2!
Your bank is now 100.
Do you want to play again?

## Contributing

Pull requests are wellcome!
