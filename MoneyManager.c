#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char transitioner [30];

struct item{
	char name[20];
	char category[20];
	float cost;
	int quantity;
}Expenses [100];

struct date{
	int month;
	int day;
	int year;
}Date;

void start_program ();
void title ();
void calculate_expenses ();
void access_expenses ();
void update_expenses ();
float remaining_budget (float budget, struct item *Expenses, int number_of_items);
int check_date (int month, int day, int year);												
void saving_data (struct date Date, float budget, int number_of_items, float budgetLeft, struct item Expenses[100]);
void change_budget (struct date Date);
void add_item (struct date Date);
void remove_item (struct date Date);
void print_expenses (struct date Date);
void print_by_category (struct date Date);


void main (){
	start_program ();
}

void start_program (){							
	title ();
	int choice;
	printf("\tPick an option:\n\n\t[1] Calculate Expenses for the Day\n\t[2] Access Past Expenses\n\t[3] Update Previous Expenses\n\t[4] Exit\n\nChoice: ");
	scanf("%d", &choice);
	title ();	
	if (choice == 1){																//goes to calculate_expenses function
		calculate_expenses ();
	}else if (choice == 2){															//goes to access_expenses function
		access_expenses ();
	}else if (choice == 3){																//goes to update_expenses function
		update_expenses ();														
	}else if (choice == 4){
		exit (0);
	}else{
		getc (stdin);
		start_program ();
	}
}

void title (){
	system ("cls");
	printf ("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");				//Prints the title
	printf ("$$|||||||||||||||||||||||||||||||||||||||||||||||$$\n");
	printf ("$$||                                           ||$$\n");
	printf ("$$||  ==WELCOME TO JAMVEEZEL MONEY MANAGER!==  ||$$\n");
	printf ("$$||                                           ||$$\n");
	printf ("$$|||||||||||||||||||||||||||||||||||||||||||||||$$\n");
	printf ("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
}

void calculate_expenses (){														//Asks inputs from user for date, budget, and all expenses for that day.
	title ();
	struct date Date;															//initialization of variables
	struct date Compare;
	struct item Expenses [100];
	float budget, budgetLeft;
	int number_of_items, index, index2, size_of_file, counter = 0;
	char temp_text[25];
	char delimiter;

	FILE* file_pointer;

	fflush (stdin);
	printf ("[1] January\t[7] July\n[2] February\t[8] August\n[3] March\t[9] September\n[4] April\t[10] October\n[5] May\t\t[11] November\n[6] June\t[12] December");
	printf ("\n\nEnter the Date (MM/DD/YYYY): ");			
	gets (temp_text);
	sscanf (temp_text, "%d%c%d%c%d", &Date.month, &delimiter, &Date.day, &delimiter, &Date.year);						//takes date input

	if (check_date (Date.month, Date.day, Date.year) == 1){																//calls check date function if date is valid

		file_pointer = fopen ("money.txt", "r");

		if (file_pointer == NULL){																						//creates text file if it does not exist
			printf ("\nFile Not Found... Creating file... \nEnter anything to restart program: ");
			file_pointer = fopen ("money.txt", "w");
			gets (transitioner);
			fclose (file_pointer);
			start_program ();
			return;
		}

		fseek (file_pointer, 0, SEEK_END);
    	size_of_file = ftell (file_pointer);																			//tells the size of the text file

		while (!feof (file_pointer)){																					//while not end of file...										

			fgets (temp_text, 100, file_pointer);
			sscanf (temp_text, "%d%c%d%c%d", &Compare.month, &delimiter, &Compare.day, &delimiter, &Compare.year);			
			if (Date.month == Compare.month && Date.day == Compare.day && Date.year == Compare.year){					//checks if date is in the file
				counter ++;
			}
		}

		if (counter != 0 || size_of_file == 0){																			//if date is found, or text is empty
			title ();
			printf ("Enter the budget for %d/%d/%d: ", Date.month, Date.day, Date.year);
			scanf ("%f", &budget);
			printf ("Enter number of items:");
			scanf ("%d", &number_of_items);
			if (number_of_items < 100){

				for(index = 0; index < number_of_items; index ++){													//asks for user inputs
					title ();
					printf ("Enter expenses for %d/%d/%d.\n\nExample:\n\tEnter name of item: BACON\n\tEnter the category: FOOD\n\tEnter cost: 105.67\n\tEnter the quantity: 4\n\n", Date.month, Date.day, Date.year);
					printf ("\tUse underscore '_' for multiple words\n\tExample: SMOKED_BACON\n\tDisclaimer: Item Name and Category should be strings of characters or words\n");							
					printf ("\nEnter name of item: ");
					getc (stdin);
					gets (Expenses [index].name);													
					strupr (Expenses [index].name);
					printf ("\nEnter the category (What kind of item?): ");
					gets (Expenses [index].category);
					strupr (Expenses [index].category);
					printf ("\nEnter cost (price) of the item: ");
					scanf ("%f", &Expenses [index].cost);
					if (Expenses [index].cost < 0.001){
						fflush (stdin);
						printf ("\nCost cannot be zero or words\n\nEnter anything to return to menu: ");
						gets (transitioner);
						start_program ();
						return;
					}
					printf ("\nEnter the quantity (How many did you buy?): ");
					scanf ("%d", &Expenses [index].quantity);
					if (Expenses [index].quantity > 100000 || Expenses [index].quantity == 0){
						fflush (stdin);
						printf ("\nAmount cannot be words, letters, have a large value or zero.\n\nEnter anything to return to menu: ");
						gets (transitioner);
						start_program ();
						return;

					}

				}
				budgetLeft = remaining_budget (budget, Expenses, number_of_items);							//calculates the remaining budget
				title ();
				printf ("\nInitial Budget: %.2f\n", budget);												//prints the budget
				printf ("\nRemaining Budget: %.2f\n\n", budgetLeft);

				printf ("Item                Category            Cost                Quantity\n");			//prints calculated expenses
				for (index = 0; index < number_of_items; index++){
					printf ("%-20s%-20s%-20.2f%d\n", Expenses [index].name, Expenses [index].category, Expenses [index].cost, Expenses [index].quantity);
				}
			}
			else{
				printf ("\nNumber of Items should only be numbers less than 100.\nEnter anything to return to menu: ");			//error catch for items greater than 100
				fflush (stdin);
				gets (transitioner);
				start_program ();
				return;
			}	
		}else{																											//if date already exists
    		if (size_of_file != 0){																							
				printf ("\nDate already exists.\n\nEnter anything to return to the menu\n--->");
				gets (transitioner);
				calculate_expenses ();
			}
		}

	}else{
		printf ("\nThat's not a valid date\n\nEnter anything to return to the menu\n--->");							//if date is invalid
		gets (transitioner);
		start_program ();
		return;
	}
	getc (stdin);
	fclose (file_pointer);	
	saving_data (Date, budget, number_of_items, budgetLeft, Expenses);										//calls function to save to text file
	printf ("\nFinished Calculating...\n\nEnter anything to return to the menu\n--->");
	gets (transitioner);
	start_program ();
	return;
}

float remaining_budget (float budget, struct item *Expenses, int number_of_items){			//calculates remaining budget
	//budget (cost*quantity)
	float temp = 0, budgetLeft = 0;
	int i;
	for (i = 0; i < number_of_items; i++){
		temp += (Expenses [i].cost * Expenses [i].quantity);
	}
	budgetLeft = (budget - temp);
	return budgetLeft;																		//returns the calculated budget
}

void access_expenses (){																	//chooses to print all expenses or by category
	struct date Date;																		//declaration of variables
	char temp_text [50];
	char delimiter;
	int choice;

	title ();
	fflush (stdin);
	printf ("[1] January\t[7] July\n[2] February\t[8] August\n[3] March\t[9] September\n[4] April\t[10] October\n[5] May\t\t[11] November\n[6] June\t[12] December");
	printf ("\n\nEnter the Date (MM/DD/YYYY): ");
	gets (temp_text);
	sscanf (temp_text, "%d%c%d%c%d", &Date.month, &delimiter, &Date.day, &delimiter, &Date.year);		//takes date

	printf ("\n\t[1] Print All Expenses\n\t[2] Print Expenses in Specific Category\n\nEnter your choice:");
	scanf ("%d", &choice);																		//takes user choice

	if (choice == 1){																			//chooses from two options
		print_expenses (Date);
	}else if (choice == 2){
		print_by_category (Date);
	}else{
		printf ("Invalid Choice, try again\nEnter anything to go back: ");					//otherwise, choice is invalid
		gets (transitioner);
		start_program ();
		return;
	}
}

void print_expenses (struct date Date){													//prints all expenses on the specific date
	struct date Compare;																//declaration of variables
	float budget, budgetLeft, cost;
	int number_of_items, quantity, index, counter = 0;
	char delimiter;
	char text [100], temp_text [25], name [50], category [50];

	FILE *file_pointer;

	if (check_date (Date.month, Date.day, Date.year) == 1){								//checks date

		file_pointer = fopen ("money.txt", "r");

		while (!feof (file_pointer)){											//scans line by line to print stored values in text file

			fgets (text, 100, file_pointer);																		
			sscanf (text, "%d%c%d%c%d", &Compare.month, &delimiter, &Compare.day, &delimiter, &Compare.year);
			if (Date.month == Compare.month && Date.day == Compare.day && Date.year == Compare.year){
				counter ++;
				if (counter == 1){
					title ();
					printf ("Date: %d/%d/%d", Compare.month, Compare.day, Compare.year);
				}
				else if (counter == 2){
					sscanf (text, "%s%f", temp_text, &budget);
					printf ("\nInitial Budget: %.2f", budget);
				}
				else if (counter == 3){
					sscanf (text, "%s%f", temp_text, &budgetLeft);
					printf ("\nRemaining Budget: %.2f", budgetLeft);
				}
				else if (counter == 4){
					sscanf (text, "%s%d", temp_text, &number_of_items);
					printf ("\nNumber of Items: %d", number_of_items);
				}
				else if (counter == 6){
					printf("\n\nITEM                CATEGORY            COST                QUANTITY\n");
				}
				else if (counter >= 7 && counter < number_of_items + 7){
					sscanf (text, "%s%s%f%d", name, category, &cost, &quantity);
					printf ("\n%-20s%-20s%-20.2f%d", name, category, cost, quantity);
				}	
			}
		}
		printf ("\n\nFinished analyzing");
		fclose (file_pointer);
		printf ("\nEnter anything to return to the menu\n--->");
	fflush (stdin);
		gets (transitioner);
		start_program ();
		return;

	}else{																						//else, invalid date
		printf ("\nInvalid Date\nEnter anything to return to menu\n--->");
		gets (transitioner);
		start_program ();
		return;
	}
}
	
void print_by_category (struct date Date){													//same function as print_expenses but only prints items with the same category...
	struct date Compare;																	//...entered by user
	float budget, budgetLeft, cost, totalCost = 0;
	int number_of_items, number = 0, quantity, index, counter = 0;
	char delimiter;
	char text [100], temp_text [25], name [50], category [50], findCategory [50];

	FILE *file_pointer;

	printf ("Enter category:");
	scanf ("%s", findCategory);
	strupr (findCategory);

	if (check_date (Date.month, Date.day, Date.year) == 1){

		file_pointer = fopen ("money.txt", "r");

		while (!feof (file_pointer)){

			fgets (text, 100, file_pointer);
			sscanf (text, "%d%c%d%c%d", &Compare.month, &delimiter, &Compare.day, &delimiter, &Compare.year);
			if (Date.month == Compare.month && Date.day == Compare.day && Date.year == Compare.year){
				counter ++;
				if (counter == 1){
					title ();
					printf ("Date: %d/%d/%d", Compare.month, Compare.day, Compare.year);
				}
				else if (counter == 4){
					sscanf (text, "%s%d", temp_text, &number_of_items);
				}
				else if (counter == 6){
					printf("\n\nITEM                CATEGORY            COST                QUANTITY\n");
				}
				else if (counter >= 7 && counter < number_of_items + 7){							//where evaluation of the category happens
					sscanf (text, "%s%s%f%d", name, category, &cost, &quantity);
					if (strcmp (findCategory, category) == 0){										//if true
						number ++;
						printf ("\n%-20s%-20s%-20.2f%d", name, category, cost, quantity);
						totalCost += (cost * quantity);												//solves total cost in one category
					}
				}	
			}
		}

		if (number == 0){
			fflush (stdin);
			printf ("N/A                 N/A                 N/A                 N/A\n");
			printf ("\nNo items exist in this category.\n");
			printf ("\nEnter anything to return to menu\n--->");
			gets (transitioner);
			start_program ();
			return;
		}
		printf ("\n\nTotal Cost in %s: %.2f", findCategory, totalCost);
		printf ("\nTotal number of items in %s: %d", findCategory, number);
		printf ("\n\nFinished analyzing");
		fclose (file_pointer);
		printf ("\nEnter anything to return to the menu\n--->");
		fflush (stdin);
		gets (transitioner);
		start_program ();
		return;

	}else{
		printf ("\nInvalid Date\nEnter anything to return to menu\n--->");
		gets (transitioner);
		start_program ();
		return;
	}
}


void saving_data (struct date Date, float budget, int number_of_items, float budgetLeft, struct item Expenses [100]){
	FILE *file_pointer;
	int counter;

	file_pointer = fopen ("money.txt", "a");

	fprintf (file_pointer, "%d/%d/%d\n", Date.month, Date.day, Date.year);
	fprintf (file_pointer, "Ininital_Budget: %.2f\n", budget);
	fprintf (file_pointer, "Remaining_Budget: %.2f\n", budgetLeft);
	fprintf (file_pointer, "Number_of_Items: %d\n\n", number_of_items);

	fprintf (file_pointer, "Item                Category            Cost                Quantity\n");
	for (counter = 0; counter < number_of_items; counter++){
		fprintf (file_pointer, "%-20s%-20s%-20.2f%d\n", Expenses [counter].name, Expenses [counter].category, Expenses [counter].cost, Expenses [counter].quantity);
	}
	fprintf (file_pointer, "\n");
	fclose (file_pointer);
}

void update_expenses (){
	struct date Date;
	float budget, cost;
	int month, day, year, choice;
	int number_of_items, quantity, index, counter = 0;
	char text [100], temp_text [25], name [50], category [50];
	char delimiter;

	fflush (stdin);
	title ();
	printf ("[1] January\t[7] July\n[2] February\t[8] August\n[3] March\t[9] September\n[4] April\t[10] October\n[5] May\t\t[11] November\n[6] June\t[12] December");
	printf ("\n\nEnter the Date (MM/DD/YYYY): ");
	gets (temp_text);
	sscanf (temp_text, "%d%c%d%c%d", &Date.month, &delimiter, &Date.day, &delimiter, &Date.year);

	if (check_date (Date.month, Date.day, Date.year) == 0){
		printf ("\nInvalid Date\nEnter anything to try again\n--->");
		gets (transitioner);
		update_expenses ();
		return;
	}

	printf ("\n\t[1] Change initial budget\n\t[2] Add another item\n\t[3] Remove an existing item\n\nEnter your choice:");
	scanf ("%d", &choice);

	if (choice == 1){
		change_budget(Date);
	}else if (choice == 2){
		add_item(Date);
	}else if (choice == 3){
		remove_item(Date);
	}else{
		printf ("Invalid Choice, try again\nEnter anything to go back: ");
		gets (transitioner);
		update_expenses ();
		return;
	}
}

void change_budget (struct date Date){
	struct date newDate;
	int counter = 0;
	char delimiter, text[100], temp_text[50];
	char name[50];
	float oldBudget, newBudget, oldRemainingBudget, newRemainingBudget;

	FILE* file_pointer;
	FILE* tempFile;

	title ();
	printf ("Enter new budget: ");
	scanf ("%f", &newBudget);

	file_pointer = fopen ("money.txt", "r");
	tempFile = fopen ("temporary.txt", "w");
		
	while (fgets (text, 100, file_pointer) != NULL){
		sscanf (text, "%d%c%d%c%d", &newDate.month, &delimiter, &newDate.day, &delimiter, &newDate.year);
		if (Date.month == newDate.month && Date.day == newDate.day && Date.year == newDate.year){
			counter ++;
			if (counter == 2){
				sscanf (text, "%s%f", temp_text, &oldBudget);
				fprintf (tempFile, "Initial_Budget: %.2f\n", newBudget);
				continue;
			}
			else if (counter == 3){
				sscanf (text, "%s%f", temp_text, &oldRemainingBudget);
				newRemainingBudget = oldRemainingBudget + (newBudget - oldBudget);
				fprintf (tempFile, "Remaining_Budget: %.2f\n", newRemainingBudget);
				continue;
			}
		}
	fputs (text, tempFile);
	}
	fclose (file_pointer);
	fclose (tempFile);

	remove ("money.txt");
	rename ("temporary.txt", "money.txt");

	printf ("\nSuccessfully changed budget\nEnter Anything to return the menu: ");
	fflush (stdin);
	gets (transitioner);
	start_program ();
	return;
}

void add_item (struct date Date){
	struct date newDate;
	int number_of_items, counter = 0;
	char delimiter, text[100], temp_text[50];
	char deleteItem[50], name[50];
	struct item newItem;
	float totalCost, remaining_budget;

	FILE* file_pointer;
	FILE* tempFile;

	title ();
	getc (stdin);
	printf ("Enter name of new item: ");
	gets (newItem.name);
	strupr (newItem.name);
	printf ("\nEnter the category (What kind of item?): ");
	gets (newItem.category);
	strupr (newItem.category);
	printf ("\nEnter cost (price) of the item: ");
	scanf ("%f", &newItem.cost);
	if (newItem.cost < 0.001){
		fflush (stdin);
		printf ("\nCost cannot be zero\n\nEnter anything to return to menu: ");
		gets (transitioner);
		start_program ();
		return;
	}
	printf ("\nEnter the quantity (How many did you buy?): ");
	scanf ("%d", &newItem.quantity);
	if (newItem.quantity > 100000 || newItem.quantity == 0){
		fflush (stdin);
		printf ("\nAmount cannot be words, letters, have a large value or zero\n\nEnter anything to return to menu: ");
		gets (transitioner);
		start_program ();
		return;
	}

	totalCost = newItem.cost * newItem.quantity;

	file_pointer = fopen ("money.txt", "r");
	tempFile = fopen ("temporary.txt", "w");
		
	while (fgets (text, 100, file_pointer) != NULL){
		sscanf (text, "%d%c%d%c%d", &newDate.month, &delimiter, &newDate.day, &delimiter, &newDate.year);
		if (Date.month == newDate.month && Date.day == newDate.day && Date.year == newDate.year){
			counter ++;
			if (counter == 3){
				sscanf (text, "%s%f", temp_text, &remaining_budget);
				fprintf (tempFile, "Remaining_Budget: %.2f\n", remaining_budget - totalCost);
				continue;
			}
			else if (counter == 4){
				sscanf (text, "%s%d", temp_text, &number_of_items);
				fprintf (tempFile, "Number_of_Items: %d\n", number_of_items + 1);
				continue;
			}
			else if (counter == number_of_items + 7 ){	//
				fprintf (tempFile, "%-20s%-20s%-20.2f%d\n", newItem.name, newItem.category, newItem.cost, newItem.quantity);
			}
		}
	fputs (text, tempFile);
	}
	fclose (file_pointer);
	fclose (tempFile);

	remove ("money.txt");
	rename ("temporary.txt", "money.txt");

	printf ("\nSuccessfully added Item\nEnter Anything to return the menu: ");
	fflush (stdin);
	gets (transitioner);
	start_program ();
	return;
}

void remove_item (struct date Date){
	struct date newDate;
	int number_of_items, counter = 0;
	char delimiter, text[100], temp_text[50];
	char deleteItem[50];
	struct item itemFind;
	float remaining_budget, totalCost;

	FILE* file_pointer;
	FILE* tempFile;
	//FILE* finalFile;

	title ();
	printf ("Enter item to be removed: ");
	scanf ("%s", deleteItem);
	strupr (deleteItem);

	file_pointer = fopen ("money.txt", "r");
	tempFile = fopen ("temporary.txt", "w");
		
	while (fgets (text, 100, file_pointer) != NULL){
		sscanf (text, "%d%c%d%c%d", &newDate.month, &delimiter, &newDate.day, &delimiter, &newDate.year);
		if (Date.month == newDate.month && Date.day == newDate.day && Date.year == newDate.year){
			counter ++;
			if (counter == 4){
				sscanf (text, "%s%d", temp_text, &number_of_items);
				if (number_of_items == 0){
					printf ("\nThere are no items to be removed.\nEnter Anything to return to menu: ");
					fflush (stdin);
					gets (transitioner);
					start_program ();
					return;
				}
				fprintf (tempFile, "Number_of_Items: %d\n", number_of_items - 1);
				continue;
			}else if (counter >= 7 && counter < number_of_items + 7){															//last was originally 6
				sscanf (text, "%s%s%f%d", &itemFind.name, &itemFind.category, &itemFind.cost, &itemFind.quantity);				//now with ampersnd
				if ((strcmp (itemFind.name, deleteItem)) == 0){
					totalCost = itemFind.cost * itemFind.quantity;
					//printf ("%.2f", totalCost);
					continue;
				}
			}
		}
	fputs (text, tempFile);
	}

	fclose (file_pointer);
	fclose (tempFile);

	tempFile = fopen ("temporary.txt", "r");
	file_pointer = fopen ("money.txt", "w");

	counter = 0;
	while (fgets (text, 100, tempFile) != NULL){
		sscanf (text, "%d%c%d%c%d", &newDate.month, &delimiter, &newDate.day, &delimiter, &newDate.year);
		if (Date.month == newDate.month && Date.day == newDate.day && Date.year == newDate.year){
			counter ++;
			if (counter == 3){
				sscanf (text, "%s%f", temp_text, &remaining_budget);
				//printf ("\n%.2f%.2f", totalCost, remaining_budget);
				fprintf (file_pointer, "Remaining_Budget: %.2f\n", remaining_budget + totalCost);
				continue;
			}
		}
	fputs (text, file_pointer);
	}

	fclose (file_pointer);
	fclose (tempFile);
	remove ("temporary.txt");

	printf ("\nSuccessfully Removed Item\nEnter Anything to return the menu: ");
	fflush (stdin);
	gets (transitioner);
	start_program ();
	return;
}

int check_date (int month, int day, int year){ 
	if (month >=1 && month <=12){
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
			if (day >=1 && day <=31){
				if (year>=0 && year<=9999){
					return 1;
				}else{
					return 0;
				}
			}else{
				return 0;
			}
		}else if (month == 4 || month == 6 || month == 9 || month == 11){
			if (day >=1 && day <=30){
				if (year>=0 && year<=9999){
					return 1;
				}else{
					return 0;
				}
			}else{
				return 0;
			}
		}else if (month == 2){
			if (((year % 400 == 0) || (year%4 == 0 && year%100 != 0)) && year>=0 && year<=9999){
				if (day >=1 && day <= 29){
					return 1;
				}else{
					return 0;
				}
			}else if(year>=0 && year<=9999){
				if (day >=1 && day <= 28){
					return 1;
				}else{
					return 0;
				}
			}else{
				return 0;
			}
		}
	}else{
		return 0;
	}
}


	/*file_pointer = fopen ("money.txt", "r+");
		
		while (!feof (file_pointer)){

		fgets (text, 100, file_pointer);
		sscanf (text, "%d%c%d%c%d", &month, &delimiter, &day, &delimiter, &year);
		if (Date.month == month && Date.day == day && Date.year == year){
			counter ++;
			if (counter == 2){
				sscanf (text, "%s%f", temp_text, &budget);
				printf ("\nEnter new Budget: %.2f", budget);
			}
			else if (counter == 3){
				sscanf (text, "%s%d", temp_text, &number_of_items);
				printf ("\nNumber of Items: %d", number_of_items);
			}
			else if (counter == 5){
				printf("\n\nITEM                CATEGORY            COST                QUANTITY\n");
			}
			else if (counter >= 6 && counter < number_of_items + 6){
				sscanf (text, "%s%s%f%d", name, category, &cost, &quantity);
				printf ("\n%-20s%-20s%-20.2f%d", name, category, cost, quantity);
			}	
		}
		else{
			//printf("\nDate not found");
		}
	}
	printf ("\nFinished analyzing");
	fclose (file_pointer);
	printf ("\nEnter anything to return to the menu\n--->");
	getc (stdin);
	gets (transitioner);
	start_program ();
	return;
}

	title ();
	struct date Date;
	char temp_text [25];
	char delimiter;

	FILE *file_pointer;

	printf ("\n\tEnter the Date (MM/DD/YYYY): ");
	gets (temp_text);
	sscanf (temp_text, "%d%c%d%c%d", &Date.month, &delimiter, &Date.day, &delimiter, &Date.year);
	getc (stdin);

sscanf (text, "%s%s%f%d", name, category, &cost, &quantity);
printf ("\n%s\t%s\t%.2f\t%d", name, category, cost, quantity);

}*/