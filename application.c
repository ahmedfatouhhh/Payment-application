
#include "application.h"
#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"

void appStart(void)
{
    uint8_t flag = 0;
    ST_cardData_t CardData;
    ST_cardData_t* CardDataPtr;
    CardDataPtr = &CardData;
    ST_terminalData_t TermData;
    ST_terminalData_t* TermDataPtr;
    TermDataPtr = &TermData;
    ST_transaction_t transData = { CardData,TermData,0,0 };
    ST_transaction_t* transDataPtr;
    transDataPtr = &transData;
    uint32_t transactionSequenceNumber = 0;
    while (1)
    {
        transData.transState = 0;
        
        flag = getCardHolderName(CardDataPtr);
        if (flag != 0)
        {
            transData.transState = 2;

            continue;
        }
        flag = 0;

        flag = getCardPAN(CardDataPtr);
        if (flag != 0)
        {
            transData.transState = 2;
            continue;
        }       
        
    
        flag = 0;
        flag = isValidAccount(CardDataPtr);
        if (flag != 0)
        {
            transData.transState = 2;
            continue;


        }
        flag = 0;
        flag =getTransactionDate(TermDataPtr);
        if (flag != 0)
        {
            continue;
        }
        flag = getCardExpiryDate(CardDataPtr);
        if (flag != 0)
        {
            transData.transState = 2;
            continue;


        }
        flag = 0;


        flag = isCardExpired(CardData, TermData);
        if (flag != 0)
        {
            continue;

        }
        else
        {
            flag = 0;
        }
        flag = block(transDataPtr);
        if (flag != 0) {
            transData.transState = 2;
        }

       flag = getTransactionAmount(TermDataPtr);
        if (flag != 0)
        {
            continue;

        }
        transDataPtr->terminalData.transAmount = TermDataPtr->transAmount;
        flag = 0;
        flag = setMaxAmount(TermDataPtr);
        if (flag != 0)
        {
            continue;
        }
        transDataPtr->terminalData.maxTransAmount = TermDataPtr->maxTransAmount;
        flag = isBelowMaxAmount(TermDataPtr);
        if (flag != 0)
        {

            continue;
        }
        flag = 0;
        
        flag = isAmountAvailable(TermDataPtr);
        if (flag != 0)
        {
            transData.transState = 1;
            continue;

        }
        flag = 0;
        flag = recieveTransactionData(transDataPtr);
        if (flag != 0)
        {
            continue;
        }
        flag = 0;
        flag = saveTransaction(transDataPtr);
        transData.transactionSequenceNumber++; 
  
    };
}

void main()
{

    appStart();
}
