#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "card.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("please enter the transaction date at the following format DD/MM/YYYY \n");
	gets(termData->transactionDate);
	if (strlen(termData->transactionDate) < 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || termData->transactionDate[0] == '\0')
	{
		printf("Wrong date fromat entered\n");
		return WRONG_DATE;
	}
	else { return OK1; }
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (cardData.cardExpirationDate[3] > termData.transactionDate[8])
		return OK1;
	else if ((cardData.cardExpirationDate[3] == termData.transactionDate[8]) && (cardData.cardExpirationDate[4] > termData.transactionDate[9]))
		return OK1;
	else if ((cardData.cardExpirationDate[3] == termData.transactionDate[8]) && (cardData.cardExpirationDate[4] == termData.transactionDate[9]) && (cardData.cardExpirationDate[0] > termData.transactionDate[3]))
		return OK1;
	else if ((cardData.cardExpirationDate[3] == termData.transactionDate[8]) && (cardData.cardExpirationDate[4] == termData.transactionDate[9]) && (cardData.cardExpirationDate[0] == termData.transactionDate[3]) && (cardData.cardExpirationDate[1] >= termData.transactionDate[4]))
		return OK1;
	else
		printf("Your card is expired \n");
		return EXPIRED_CARD;

	 
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please enter the transaction amount \n");
	scanf_s("%f" ,&termData->transAmount);
	if ((termData->transAmount) <= 0)
	{
		printf("You have entered an invalid amount\n");
		return INVALID_AMOUNT;
	}
	else
		return OK1;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		printf("You have exceeded the maximum amount \n");
		return EXCEED_MAX_AMOUNT;
	}
	else
		return OK1;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please enter the maximum amount \n");
	scanf_s("%f", &termData->maxTransAmount);
	if ((termData->maxTransAmount) <= 0)
	{
		printf("Wrong maximum amount entered\n");
		return INVALID_MAX_AMOUNT;

	}
	else
		return OK1;
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		return WRONG_PAN;
	}
	else

		return OK;
}
