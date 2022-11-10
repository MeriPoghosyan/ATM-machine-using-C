#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

int main()
{
	do {
		FILE * fptr;
		int option;
		const int maxInputLength = 8;
		char username[50], end[50] = ".txt";
		char password[100];
		int characterPosition = 0, i = 0, ans, amount, remaining;
		char TruePassword[100];
		char ch;
		char line[256];
		printf(":::::::::::::::::::: LOGIN FORM ::::::::::::::::::::");
		printf("\nENTER USERNAME: ");
		scanf("%s", &username);
		strcat(username, end);
		if ((fptr = fopen(username, "r")) == NULL)
		{
			printf("Invalid username! ");
		}
		else
		{
			printf("\nENTER PASSWORD: ");
			fscanf(fptr, "%[^\n]", TruePassword);
			while (1)
			{
				ch = _getch();
				if (ch == 13)
				{
					//13y enteri ascii-n a
					break;
				}
				else if (ch == 8)
				{
					//8y backspacei asciin a
					if (characterPosition > 0)
					{
						characterPosition--;
						password[characterPosition] = '\0';
						printf("\b \b");
					}
				}
				else if (ch == 32 || ch == 9)
				{
					//32-space, 9- tab
					continue;
				}
				else
				{
					if (characterPosition < maxInputLength)
					{
						password[characterPosition] = ch;
						characterPosition++;
						printf("*");
					}
					else
					{
						printf("\nYour password should contain less characters. ");
						break;
					}
				}
			}

			password[characterPosition] = '\0';
			if (strlen(password) == 0)
			{
				printf("\nNo password input");
			}
			else if (strcmp(password, TruePassword) == 0)
			{
				printf("\nsuccessfull login");
				printf("\nEnter any option to be served\n\n1... To withdraw\n2... To deposit\n3... Check balance\n - ");
				scanf("%d", &option);
				switch (option)
				{
					case 1:
						while (fgets(line, sizeof(line), fptr))
						{
							if (i == 1)
							{
								printf("Your balance is: %s", line);
								printf("\nEnter the amount you want to withdraw:");
								scanf("%d", &amount);
								if (atoi(line) < amount) printf("insufficient resources");
								else
								{
									remaining = atoi(line) - amount;

									fclose(fptr);
									fptr = fopen(username, "w");
									fputs(TruePassword, fptr);
									//fclose(fptr);
									//fptr = fopen(username, "a");
									fprintf(fptr, "\n%d", remaining);
									fclose(fptr);
								}
							}

							i++;

						}

						break;

					case 2:
						printf("\n1... To another account\n2... To personal account\n");
						scanf("%d", &ans);

						if (ans == 1)
						{
							printf("\nEnter the username of the account you want to transfer...\n");
							scanf("%s", &username);
							strcat(username, end);

							if ((fptr = fopen(username, "r")) == NULL)
							{
								printf("Invalid username! ");
								break;
							}
						}

						while (fgets(line, sizeof(line), fptr))
						{
							if (i == 1)
							{
								if (ans == 2) printf("The balance is: %s", line);

								printf("\nEnter the amount you want to deposit:");
								scanf("%d", &amount);
								remaining = atoi(line) + amount;
							}

							i++;

						}

						fclose(fptr);

						fptr = fopen(username, "w");

						fputs(TruePassword, fptr);
						fclose(fptr);
						fptr = fopen(username, "a");
						fprintf(fptr, "\n%d", remaining);
						fclose(fptr);

						break;

					case 3:

						while (fgets(line, sizeof(line), fptr))
						{
							if (i == 1) printf("Your balance is: %s", line);
							i++;
						}

						break;

					default:
						printf("There is no such option");
				}
			}
			else
			{
				printf("\ninvalid password");
			}
		}

		printf("\nTap any key to continue...\n");
	} while (getch());
	return 0;
}
