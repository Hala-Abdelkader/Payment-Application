#include <stdio.h>
#include <string.h>

#include"Server.h"

ST_accountsDB_t accountsDB[255] = { {2000,RUNNING,"8989374615436851"},{3000,RUNNING,"7623542289704361"},{5000,BLOCKED,"3451097634287591"},
	{19000,BLOCKED,"4578297135125824"},{13000,RUNNING,"7541682485237863"} };
ST_transaction_t transDB[255] = { 0 };

extern ST_cardData_t user_card;
extern ST_terminalData_t user_terminal;
int Account_NUM=0;
int NUM;
extern int number_of_transactions;




EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	if (isValidAccount(&user_card, accountsDB) == ACCOUNT_NOT_FOUND) {

		transData->transState = FRAUD_CARD;
		return FRAUD_CARD;
	}

	else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) {

		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;

	}

	else if (isAmountAvailable(&user_terminal, accountsDB) == SERVER_OK) {

		transData->transState = APPROVED;
		return APPROVED;
	}
	
	else if (isAmountAvailable(&user_terminal, accountsDB) == LOW_BALANCE) {

		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (saveTransaction(&user_terminal) == SAVING_FAILED) {

		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

}

EN_serverError_t isValidAccount(ST_cardData_t* CardData, ST_accountsDB_t* accountRefrence) {

	accountRefrence = accountsDB;
	for (Account_NUM = 0; Account_NUM <255; Account_NUM++) {
		if (strcmp((CardData->primaryAccountNumber), (*(accountRefrence + Account_NUM)).primaryAccountNumber)==0) {
			return SERVER_OK;
			break;
		}
	}
	return ACCOUNT_NOT_FOUND;
	}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence[Account_NUM].state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	else {
		return SERVER_OK;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (accountRefrence[Account_NUM].balance >= termData->transAmount) {
		accountsDB[Account_NUM].balance -= termData->transAmount;
		return SERVER_OK;
	}

	else if (accountRefrence[Account_NUM].balance < termData->transAmount)
	{
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
		
	for ( int NUM = 0; NUM <255; NUM++)
	{
		if ((*(transData+NUM)).transactionSequenceNumber== 0)
		{
			strcpy(transData->cardHolderData.cardHolderName, user_card.cardHolderName);
			strcpy(transData->cardHolderData.cardExpirationDate,user_card.cardExpirationDate);
			strcpy(transData->cardHolderData.primaryAccountNumber, user_card.primaryAccountNumber);
			strcpy(transData->terminalData.transactionDate, user_terminal.transactionDate);
			transData->terminalData.maxTransAmount = user_terminal.maxTransAmount;
			transData->terminalData.transAmount = user_terminal.transAmount;
			transData->transactionSequenceNumber= NUM + 1;
			
			if (transData->cardHolderData.cardHolderName ==0) {
				return SAVING_FAILED;
			}

			else if (transData->cardHolderData.cardExpirationDate == 0) {

				return SAVING_FAILED;
			}

			else if (transData->cardHolderData.primaryAccountNumber == 0) {

				return SAVING_FAILED;
			}

			else if (transData->terminalData.transactionDate == 0) {

				return SAVING_FAILED;

			}

			else if (transData->terminalData.maxTransAmount == 0) {

				return SAVING_FAILED;

			}

			else if (transData->terminalData.transAmount == 0) {

				return SAVING_FAILED;

			}

			return SERVER_OK;
		}



	}
		return SAVING_FAILED;
}


void listSavedTransactions(void) {
	
	
		printf("Transaction Sequence Number: %d\n", (*(transDB +NUM)).transactionSequenceNumber);
		printf("Transaction Date: %s\n", (*(transDB + NUM)).terminalData.transactionDate);
		printf("Transaction Amount: %.1f\n", (*(transDB + NUM)).terminalData.transAmount);

		if (recieveTransactionData(transDB) == APPROVED) {

			printf("Transaction state: APPROVED \n");
		}

		else if (recieveTransactionData(transDB) == DECLINED_INSUFFECIENT_FUND) {
			printf("Transaction state: DECLINED_INSUFFECIENT_FUND \n");
		}

		else if (recieveTransactionData(transDB) == DECLINED_STOLEN_CARD) {
			printf("Transaction state: DECLINED_STOLEN_CARD \n");
		}

		else if (recieveTransactionData(transDB) == FRAUD_CARD) {
			printf("Transaction state: FRAUD_CARD \n");
		}
		else if (recieveTransactionData(transDB) == INTERNAL_SERVER_ERROR) {
			printf("Transaction state: INTERNAL_SERVER_ERROR \n");
		}

		printf("Terminal Max Amount: %.1f\n", (*(transDB + NUM)).terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", (*(transDB + NUM)).cardHolderData.cardHolderName);
		printf("PAN: %s\n", (*(transDB + NUM)).cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", (*(transDB + NUM)).cardHolderData.cardExpirationDate);

	 }


	


void isValidAccountTest(void) {

		printf("Please enter your primary account number \n");
		scanf("\n");
		scanf("%[^\n]%*c", &(user_card.primaryAccountNumber));

		if (isValidAccount(&user_card, accountsDB) == SERVER_OK) 
		{
			printf("VALID ACCOUNT \n");
		}
		else if (isValidAccount(&user_card, accountsDB) == ACCOUNT_NOT_FOUND )
		{
			printf("INVALID ACCOUNT \n");
		}
	 }

void isBlockedAccountTest(void) {

		printf("Please enter your primary account number \n");
		scanf("%[^\n]%*c", &user_card.primaryAccountNumber);
		if (isValidAccount(&user_card, accountsDB) == SERVER_OK) {
			if (isBlockedAccount(accountsDB) == SERVER_OK) {

				printf("UNBLOCKED ACCOUNT \n");
			}

			else {
				printf(" BLOCKED ACCOUNT \n");
			}
		}
		else {
			printf("INVALID ACCOUNT \n");
		}

	} 

void isAmountAvailableTest(void) {

		printf("Please enter your primary account number \n");
		scanf("\n");
		scanf("%[^\n]%*c", &user_card.primaryAccountNumber);

		printf("Please enter transaction amount \n");
		scanf("\n");
		scanf("%f", &(user_terminal.transAmount));

		if (isValidAccount(&user_card, accountsDB) == SERVER_OK) {
			if (isBlockedAccount(&accountsDB) == SERVER_OK) {
				if (isAmountAvailable(&user_terminal, accountsDB) == SERVER_OK) {
					printf("APPROVED \n");
				}
				else {
					printf("LOW BALANCE \n");
				}
			}
		}
	}

void recieveTransactionDataTest(void) {

	printf("Please enter the card holder name \n");
	scanf("\n");
	scanf("%[^\n]%*c", &user_card.cardHolderName);


	if (getCardHolderName(&user_card.cardHolderName) == CARD_OK)
	{
		printf("Please enter the  primary account number \n");
		scanf("\n");
		scanf("%[^\n]%*c", &user_card.primaryAccountNumber);

		if (getCardPAN(&user_card.primaryAccountNumber) == CARD_OK)
		{

			printf("Please enter the card expiry date \n");
			scanf("\n");
			scanf("%[^\n]%*c", &user_card.cardExpirationDate);



			if (getCardExpiryDate(&user_card.cardExpirationDate) == CARD_OK)
			{
				printf("please enter the transaction date\n");
				scanf("\n");
				scanf("%[^\n]%*c", &(user_terminal.transactionDate));

				if (getTransactionDate(&user_terminal) == TERMINAL_OK) {

					if (isCardExpired(&user_card, &user_terminal) == TERMINAL_OK) {
						printf("Please enter the transaction amount\n");
						scanf("%f", &user_terminal.transAmount);

						if (getTransactionAmount(&user_terminal) == TERMINAL_OK) {

							if (setMaxAmount(max_amount) == TERMINAL_OK) {

								if (isBelowMaxAmount(&user_terminal) == TERMINAL_OK)
								{
									if (recieveTransactionData(transDB) == FRAUD_CARD) {
										printf("FRAUD_CARD\n");
									}
									else if (recieveTransactionData(transDB) == DECLINED_STOLEN_CARD) {
											printf("DECLINED_STOLEN_CARD\n");
									}
									else if (recieveTransactionData(transDB) == APPROVED) {
										     printf("APPROVED\n");
									}
									else if (recieveTransactionData(transDB) == DECLINED_INSUFFECIENT_FUND) {

										printf("DECLINED_INSUFFECIENT_FUND\n");
									}
									else if (recieveTransactionData(transDB) == INTERNAL_SERVER_ERROR) {
										printf("INTERNAL_SERVER_ERROR\n");
									}
								}
							}
						}
					}
				}
					
			}

		}

	}

}


void saveTransactionTest(void) {
	recieveTransactionDataTest();
	if (saveTransaction(transDB ) == SERVER_OK)
	{
		printf(" Data saved successfully\n");
	}
	else 
	{
		printf("Saving failed\n");
	}
}

void listSavedTransactionsTest(void)
{
	appStart();
}


