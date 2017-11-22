#pragma once
#include <string>
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Invalid_Character,
	Wrong_Length,
	Not_Lowercase

};

enum class EWordChoiceStatus
{
	Invalid_Status,
	OK,
	Not_A_Number,
	Wrong_Length,
	Wrong_Number
};



class FBullCowGame
{
	
public:
	FBullCowGame(); // Constructor

	void Reset();
	int32 GetMaxTries();
	int32 GetCurrentTry();
	bool IsGameWon();
	EGuessStatus IsGuessValid(FString) const;
	int32 GetHiddenWordLength() const;
	void SetHiddenWord(int32);
	EWordChoiceStatus IsChoiceValid(FString) const;
	void SetWordLength(int32);
	

	FBullCowCount SumbitValidGuess(FString);
	void SetMaxTry(int32 maxTries);
	
	

private:
	//See constructor for initialization
	int32 m_CurrentTry;
	FString m_HiddenWord;
	bool m_GameWon;
	int32 m_WordLength;

	//Helpers
	bool IsLowerCase(FString) const;
	bool IsIsogram(FString) const;
	bool IsNumber(FString) const;

};