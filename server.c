#include<stdio.h>
#include <string.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
int flag = 0;
sint32_t  PAN = -1;
uint32_t TransactionSequenceNumber = 0;
struct ST_accountsDB_t accounts[255] = { 
	{1000,"1234567890123456789"}
	,{2000,"1234567890123456788"}
	,{3000,"1234567890123456787"}
	,{4000,"1234567890123456786"}
	,{5000,"1234567890123456785"}
	,{6000,"1234567890123456784"}
	,{7000,"1234567890123456783"}
	,{8000,"1234567890123456782"}
	,{9000,"1234567890123456781"}
	,{1000,"1234567890123456780"}

};
struct ST_transaction_t transactions[255] = { 0 };
EN_transState_t block(ST_transaction_t* transData)
{
	int x;
	printf(" Do you want to block your card? if yes please enter 1, if no please enter 0 \n");
	scanf_s("%d", &x);
	if (x == 1)
	{
		printf("Declined stolen card\n");
		return DECLINED_STOLEN_CARD;
		
	}
	else
		return OK2;
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if ((transData->transState) == 1)
	{
		printf("Insuffecient fund\n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	else if ((transData->transState) == 2)
	{
		printf("Declined Stolen Card \n");
		return DECLINED_STOLEN_CARD;
	}
	
	
	else if ((transData->transState) == 3)
	{
		printf("Internal server error\n");
		return INTERNAL_SERVER_ERROR;
	}
	else
	return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (int i = 0; i < 10; i++)
	{
		
		if (strcmp((cardData->primaryAccountNumber), (accounts[i].primaryAccountNumber ))==0)
		{
			printf("The primary account number was found\n");
			return OK2;

		}
		else
			flag++;
			

	}
	for (int i = 0; i < 10; i++)
	{
		if (strcmp((cardData->primaryAccountNumber), (accounts[i].primaryAccountNumber )) != 0)
		{
			printf("The primary account number wasn't found\n");
			return DECLINED_STOLEN_CARD;
		}
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > accounts[flag].balance)
	{
		printf("Sorry, the transaction amount exceeds your balance\n");
		return LOW_BALANCE;
	}
	else
		printf("amount available\n");
		return OK2;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	uint8_t flag1 = 0;
	//flag[0] = recieveTransactionData(transData);
	if ((transData->transState) == 1)
	{
		printf("DECLINED INSUFFECIENT FUND\n");
		return SAVING_FAILED;
	}
	else if ((transData->transState) == 2)
	{
		printf("DECLINED CARD\n");
		return SAVING_FAILED;
	}
	flag1 = getTransaction(TransactionSequenceNumber, transData);
	if (flag1 == 1)
	{
		printf("Reached max transactions\n");
		return SAVING_FAILED;
	}
	else
		// update transaction array
		transactions[TransactionSequenceNumber] = *transData;
	return OK2;
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	if ((transactionSequenceNumber >= 10) || (transactionSequenceNumber < 0))
	{
		return SAVING_FAILED;
	}
	if (transData->transactionSequenceNumber == transactionSequenceNumber)
	{
		transData->terminalData.maxTransAmount = accounts[flag].balance;
		// update Max Amount
		transData->terminalData.maxTransAmount = ((transData->terminalData.maxTransAmount) - (transData->terminalData.transAmount));
		//Update balance
		accounts[flag].balance = transData->terminalData.maxTransAmount;
		printf("Transaction done and your balance is updated\n");
		printf("The new balance is %f\n", transData->terminalData.maxTransAmount);
		TransactionSequenceNumber++;
		return OK2;
	}
	// if it is not saved 
	return SAVING_FAILED;
}

	
	