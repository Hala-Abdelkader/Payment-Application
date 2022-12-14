#include <stdio.h>
#include"Card.h"
ST_cardData_t user_card;


EN_cardError_t getCardHolderName(ST_cardData_t* CardData)
{

	if (strlen(CardData->cardHolderName) > 20 || strlen(CardData->cardHolderName) < 24)
	{
		for (int i = 0; i < strlen(CardData->cardHolderName); i++) 
		{

			if (('a' > CardData->cardHolderName[i] || CardData->cardHolderName[i] > 'z') && (CardData->cardHolderName[i] != ' '))
			{
				return WRONG_NAME;
			}
					
		}
		
			return CARD_OK;
	
	
	}
	else 
	{

		return WRONG_NAME;
	}
	 

} 


EN_cardError_t getCardExpiryDate(ST_cardData_t* CardData) {
	strcpy(CardData->cardExpirationDate, user_card.cardExpirationDate);

	if ((strlen(CardData->cardExpirationDate) != 5) || (CardData->cardExpirationDate[2] != '/')) {
		
		return WRONG_EXP_DATE;
	}

	if (CardData->cardExpirationDate[0] == '1') {
		if ((CardData->cardExpirationDate[1] != '1') && (CardData->cardExpirationDate[1] != '0') && (CardData->cardExpirationDate[1] != '2')) {
			
			return WRONG_EXP_DATE;
		}
	}
	if ((CardData->cardExpirationDate[0] != '1') && (CardData->cardExpirationDate[0] != '0')) {
	
		return WRONG_EXP_DATE;
	}

	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* CardData) {
	strcpy(CardData->primaryAccountNumber, user_card.primaryAccountNumber);
	
	if (strlen(CardData->primaryAccountNumber) > 16 ||  strlen(CardData->primaryAccountNumber) < 19)
	{
		for (int i = 0; i < strlen(CardData->primaryAccountNumber); i++)
		{

			if ((CardData->primaryAccountNumber[i]) >'9' || (CardData->primaryAccountNumber[i] < '0')) {

				return WRONG_PAN;
			}
		}

		
		return CARD_OK;
	}
	else
	{
		return WRONG_PAN;
	}
}


void getCardHolderNameTest(void) {

	printf("Please enter the card holder name \n");
	scanf("\n");
	scanf("%[^\n]%*c", &user_card.cardHolderName);

	if (getCardHolderName(&user_card) == CARD_OK ) {

		printf("The card holder name is correct \n");
	}
	else {
		printf("The card holder name is wrong \n");
	}
}

void getCardExpiryDateTest(void) {

	printf("Please enter the card expiry date \n");
	scanf("\n");
	scanf("%[^\n]%*c", &user_card.cardExpirationDate);

	if (getCardExpiryDate(&user_card) == CARD_OK) {

		printf("The expiry date is in correct format\n");
	}
	else {
		printf("The expiry date is in wrong format\n");
	}
}

void getCardPANTest(void) {

	printf("Please enter the  primary account number \n");
	scanf("%[^\n]%*c", &(user_card.primaryAccountNumber));


	if (getCardPAN(&user_card) == CARD_OK) {

		printf("The Primary account number is correct\n");
	}
	else {
		printf("The primary account number is wrong\n");

	}
}
