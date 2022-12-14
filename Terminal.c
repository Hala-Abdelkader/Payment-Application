#include <stdio.h>
#include "Terminal.h"
#include <string.h>
#include "../Card/Card.h"


ST_terminalData_t user_terminal;
extern ST_cardData_t user_card;
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	
	if (strlen(termData->transactionDate) != 10) {

		return WRONG_DATE;
	}

	if ((termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/')) {

		return WRONG_DATE;
	}

	if ((termData->transactionDate[0] !=  '0') && (termData->transactionDate[0] != '1') && (termData->transactionDate[0] != '2') && (termData->transactionDate[0] != '3')) {

		return WRONG_DATE;
	}

	if (termData->transactionDate[0] == '3') {

		if ((termData->transactionDate[1] != '0') && (termData->transactionDate[1] != '1')) {

			return WRONG_DATE;
		}

		
	}

	if ((termData->transactionDate[3] != '0') && (termData->transactionDate[3] != '1')) {

		return WRONG_DATE;
	}

	if (termData->transactionDate[3] == '1') {

	if ((termData->transactionDate[4] != '0') && (termData->transactionDate[4] != '1') && (termData->transactionDate[4] != '2')) {

		return WRONG_DATE;
	}


}
	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* CardData, ST_terminalData_t* termData) {


	if ((CardData->cardExpirationDate[3]) < (termData->transactionDate[8])) {

		return WRONG_EXP_DATE;
	}

	else if ((CardData->cardExpirationDate[3]) > (termData->transactionDate[8])) {

		return TERMINAL_OK;
	}

	if ((CardData->cardExpirationDate[4]) > (termData->transactionDate[9])) {

		return TERMINAL_OK;
	}

	else if ((CardData->cardExpirationDate[4]) < (termData->transactionDate[9])) {

		return WRONG_EXP_DATE;

	}
	if (((CardData->cardExpirationDate[3]) == (termData->transactionDate[8])) && (CardData->cardExpirationDate[4]) == (termData->transactionDate[9])) {

		if ((CardData->cardExpirationDate[0]) < (termData->transactionDate[3])) {

			return WRONG_EXP_DATE;
		}
		else if ((CardData->cardExpirationDate[1]) < (termData->transactionDate[4])) {

			return WRONG_EXP_DATE;
		}
	}
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	termData->transAmount=user_terminal.transAmount;

	if (termData->transAmount <= 0) {

		return INVALID_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	
	termData->transAmount = user_terminal.transAmount;
	 termData->maxTransAmount=max_amount;
	if (termData->transAmount > termData->maxTransAmount) {
		
		return EXCEED_MAX_AMOUNT;
	}
	else {
		
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	if (maxAmount <= 0) {
		
		return INVALID_MAX_AMOUNT;
	}

	else {
		
		return TERMINAL_OK;
	}
}

void getTransactionDateTest(void) {

	printf("Please enter the transaction date\n");

	scanf("%[^\n]%*c", &(user_terminal.transactionDate));


	if (getTransactionDate(&user_terminal) == TERMINAL_OK) {

		printf("The transaction date is correct\n");
	}
	else {
		printf("The transaction date is wrong\n");
	}
}

void isCardExpiredTest(void) {

	printf("Please enter the transaction date\n");
	scanf("\n");
	scanf("%[^\n]%*c", &(user_terminal.transactionDate));

	printf("Please enter the card expiry date \n");
	scanf("\n");
	scanf("%[^\n]%*c", &user_card.cardExpirationDate);

	if (isCardExpired(&user_card,&user_terminal) == TERMINAL_OK) {

		printf("The Card is not expired\n");
	 }
	else {
		printf("The card is expired\n");
	}
}

void getTransactionAmountTest(void) {

	printf("Please enter the transaction amount\n");
	scanf("%f", &(user_terminal.transAmount));

	if (getTransactionAmount(&user_terminal.transAmount) == TERMINAL_OK) {

		printf("The transaction amount is valid\n");
	}
	else {

		printf("The transaction amount is not valid\n");
	}
}

void isBelowMaxAmountTest(void) {

	printf("Please enter the transaction amount\n");
	scanf("%f", &(user_terminal.transAmount));

	if (isBelowMaxAmount(&user_terminal) == TERMINAL_OK) {

		printf("The amount entered is below max amount\n");
	}
	else {
		
		printf("The amount entered is exceed max amount\n");
	}
}

void setMaxAmountTest(void) {

	if (setMaxAmount(&user_terminal,max_amount) == TERMINAL_OK) {

		printf("%d\n",max_amount);
	}
	if (setMaxAmount(&user_terminal,max_amount_1)==INVALID_MAX_AMOUNT) {

		printf("%d\n",max_amount_1);
	}
}