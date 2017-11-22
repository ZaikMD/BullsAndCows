#pragma once
/*
	This is the console exe. that makes use of the BullCow class
	This acts as the view in a mvc pattern and is responsible for
	all user interaction. For game logic see FBullCowGame class
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
using int32 = int; //Used in unreal for cross platform. Doesn't matter in VS.
using FText = std::string; //Used for interaction with the user in UNREAL


void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
void AskToChooseWordLength();

FBullCowGame BCGame;
int main() //The main function
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}

	while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "\n \n Welcome to Bulls and Cows \n";
	AskToChooseWordLength();
	std::cout << "\n Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram? \n";
	return;
}


void PlayGame()
{

	BCGame.Reset();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		//Sumbit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SumbitValidGuess(Guess);
		//Return number of bulls/cows
		std::cout << "\n Bulls =  " << BullCowCount.Bulls << std::endl;
		std::cout << "\n Cows =  " << BullCowCount.Cows << "\n\n";

		
	}

	PrintGameSummary();
	

	
}
//loop until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
	int32 CurrentTry = BCGame.GetCurrentTry(); //Ask for guess
	std::cout << " \n Try " << CurrentTry << ". Enter your guess: \n          ";
	
	std::getline(std::cin, Guess);

		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "\n Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << " \n Please enter an word without repeating letters \n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "\n Please enter the word in lowercase \n";
			break;

		default:
			//Assuming the guess is vaild
			break;
		}
	}
	while (Status != EGuessStatus::OK); //Keep looping until no errors
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "\n Play again, with the same word?";
	std::cout << "\n y/n \n";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << response[0];

	if (response[0] == 'y' || response[0] == 'Y')
	{
		std::cout << "\n You answered Yes \n";
		return true;
	}

	else
	{
		std::cout << "\n You answered No \n";
		return false;
	}
	
}

void AskToChooseWordLength()
{
	std::cout << "\n Please choose a word length from 3 to 6 letters \n";
	FText response = "";
	

	EWordChoiceStatus status = EWordChoiceStatus::Invalid_Status;
	do 
	{
		std::getline(std::cin, response);
		status = BCGame.IsChoiceValid(response);

		switch (status)
		{
		case EWordChoiceStatus::Wrong_Length:
			std::cout << "\n Please enter a one digit number from 3 to 6. \n";
			break;

		case EWordChoiceStatus::Wrong_Number:
			std::cout << "\n Please enter a number from 3 to 6. \n";
			break;

		case EWordChoiceStatus::Not_A_Number:
			std::cout << "\n Invalid character. Please enter a number from 3 to 6. \n";
			break;

		default:
			break;
		}
	} 
		while (status != EWordChoiceStatus::OK);

	BCGame.SetWordLength(std::stoi(response));
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n You Won! \n";
	}

	else
	{
		std::cout << "\n You Lost! \n";
	}
	
}

