#include "serial.h"
#define _CRT_SECURE_NO_WARNINGS 
struct advertising{
	char adTxt[50];
	int payment;
	int sum;
};

int main()
{
	struct advertising arrayadvertising[MAX_BUSINESS];
	char b[56] = { "\\\\.\\COM5" };
	int i;
	
		SERIALPORT port = SerialInit(b);
		if (!SerialIsConnected(port))
		{
			printf("Error");
			return;
		}

	for (i = 0; i < MAX_BUSINESS; i++)
	{
		printf("\nEnter details of advertising %d\n\n", i + 1);

		printf("Enter name: ");
		fgets(arrayadvertising[i].adTxt, 50, stdin);
		arrayadvertising[i].adTxt[strlen(arrayadvertising[i].adTxt) - 1] = '\0';

		printf("Enter how much do you want to pay   : ");
		scanf("%d", &arrayadvertising[i].payment);
		
		getchar();	
		arrayadvertising[i].sum = arrayadvertising[i].payment / MAX_SECONDS;
		if(arrayadvertising[i].sum >= MAX_SECONDS ||
		   arrayadvertising[i].sum <= MIN_SECONDS)
		{
			printf("To big or to littel payment");
			return 1;
		}
	}

	for (int i = 0; i < MAX_BUSINESS; i++) {
		
		printf(" %s\nYou have got %d\n", arrayadvertising[i].adTxt, arrayadvertising[i].sum);
		
		char sendName = strlen(arrayadvertising[i].adTxt);
		SerialWritePort(port, arrayadvertising[i].adTxt, sendName);
		Sleep(arrayadvertising[i].sum * 1000);
	}
	printf("Write success");
	return 0;
}
