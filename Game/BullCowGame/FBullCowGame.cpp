#pragma once

#include "FBullCowGame.h"
#include <map>
#include <ctype.h>
#define TMap std::map

using int32 = int;
int32 isdigit(int32 ch);

FBullCowGame::FBullCowGame() //Default Constructor, called when object is created
{
	Reset();
}
void FBullCowGame::Reset()
{
	m_CurrentTry = 1;
	m_GameWon = false;
	return;
}
int32 FBullCowGame::GetMaxTries()
{
	TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16} };
	return WordLengthToMaxTries[GetHiddenWordLength()] ;
}

int32 FBullCowGame::GetCurrentTry()
{
	return m_CurrentTry;
}
bool FBullCowGame::IsGameWon()
{
	return m_GameWon;
}
int32 FBullCowGame::GetHiddenWordLength() const
{
	return m_HiddenWord.length();
}

 void FBullCowGame::SetHiddenWord(int32 wordLength)
{
	switch (wordLength)
	{
	case 3:
		m_HiddenWord = "sad";
		break;

	case 4:
		m_HiddenWord =  "plan";

		break;

	case 5:
		m_HiddenWord = "maybe";
		break;

	case 6:
		m_HiddenWord = "almost";
		break;

	default:
		break;
	}
}

EWordChoiceStatus FBullCowGame::IsChoiceValid(FString choice) const
{
	int32 length; //int for the length of the word
	
	if (choice.length() > 1) //If the user inputs too many characters
	{
		return EWordChoiceStatus::Wrong_Length;
	}
	else if (!IsNumber(choice)) //If the input is NaN
	{
		return EWordChoiceStatus::Not_A_Number;
	}
	length = std::stoi(choice); //If we got this far then the choice is a one digit number

	if (length <= 2 || length >= 7) //If the number isn't within range
	{
		return EWordChoiceStatus::Wrong_Number;
	}

	return EWordChoiceStatus::OK; //Ok input
}

void FBullCowGame::SetWordLength(int32 length)
{
	m_WordLength = length;
	SetHiddenWord(m_WordLength);
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{

	if (!IsIsogram(Guess))// if the guess isn't an isogram, return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))//if the guess isn't lowercase, return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//If the guess length is wrong, return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

//Recieves a valid guess, increments turn and returns count.
FBullCowCount FBullCowGame::SumbitValidGuess(FString Guess)
{

	//Increments return number
	m_CurrentTry++;
	//Setup return variable
	FBullCowCount bullCowCount;
	
	//Loop through all letters in the guess
		//Compare letters against the hidden word
		//if they match, increment bulls
	int32 HiddenWordLength = m_HiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (m_HiddenWord[i] == Guess[j])
			{
				if (i == j)
				{
					bullCowCount.Bulls++;
					
				}

				else
				{
					bullCowCount.Cows++;
				}
			}
		}
	}

	if (bullCowCount.Bulls == m_HiddenWord.length())
	{
		m_GameWon = true;
	}
	else
	{
		m_GameWon = false;
	}

	

	return bullCowCount;
}

void FBullCowGame::SetMaxTry(int32 maxTries)
{

}

bool FBullCowGame::IsLowerCase(FString word) const
{
	for (auto letter : word)
	{
		if (!islower(letter))//if the letter isn't lowercase
		{
			return false;
		}
		
		else
		{
			return true;
		}
	}

	return false;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	//treat 0 and 1 letter words as isograms
	if (word.length() < 2)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;
	//loop through the letters in the hidden word
	for (auto letter : word) // For all letters of the word
	{
		letter = tolower(letter);

		if (LetterSeen[letter])// check to see if they are true in the map
		{
			return false;// if they are, then return false, not an isogram
		}

		else
		{
			LetterSeen[letter] = true;//if they aren't, set the letter to true and carry on
		}


	}

	return true; //For example, where cases /0 is entered

}

bool FBullCowGame::IsNumber(FString length) const
{
	
	FString::const_iterator it = length.begin();
	while (it != length.end() && isdigit(*it)) ++it;
	return !length.empty() && it == length.end();

}
