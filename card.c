#include "card.h"
#include <stdio.h>
#include <string.h>
getCardHolderName(ST_cardData_t* cardData)
{
	printf("please enter the card holder name \n");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
	{
		printf("wrong name entered \n");
		return WRONG_NAME;
	}
	else
		return OK;
}

getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("please enter the card expiry data at the following format MM/YY  \n");
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) < 5 ||strlen(cardData->cardExpirationDate) > 5 || cardData->cardExpirationDate[2]!= '/' )
	{
		printf("Wrong format entered \n ");
			return WRONG_EXP_DATE;
	}
	else 
		return OK ;
}
getCardPAN(ST_cardData_t* cardData)
{
	printf("please enter the primary account number \n");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
	{
		printf("Wrong primary account number \n");
		return WRONG_PAN;
	}
	else
		return OK;

}