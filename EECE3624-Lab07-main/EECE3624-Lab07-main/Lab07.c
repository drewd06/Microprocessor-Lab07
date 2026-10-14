/***************************************************************************
 * Lab07.c 
 *
 *   Created: 10/13/2026
 *    Author: Drew Dimino
 * Processor: ATmega128A (on a ReadyAVR)
 *
 * This program implements a 1-D, 122 generation cellular automata simulation.
 * Wolfram Rule 26 rule set is used to generate each generation based on the previous generation.
 * UART communication is used to display generation results in PuTTY remote terminal.
 * Program utilizes UART subroutines from UARTLibrary, and custom subroutines to modify generations using pointers.
 *
 **************************************************************************/

/* your #include file declaration(s) go here */
#include "UARTLibrary.h"

/* your #define declarations go here */
#define BaudRate 9600
#define DataBits 8
#define StopBits 1
#define NoParity 0

// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);
unsigned char generateCell(unsigned char left, unsigned char current, unsigned char right);

int main(void)
{
	// create a 61-char array
	unsigned char cells[61];
	initializeArray(cells);

	// Initialize the UART
	// ProfNote:  Understand the UARTLibary.h before blindly running the next line!
	uart_init(BaudRate, DataBits, StopBits, NoParity);
	
	// ProfNote:  Initial Testing Only!  Comment out after UART confirmed working!
	/*
	while (1) {
		uart_tx('H');uart_tx('e');uart_tx('l');uart_tx('l');uart_tx('o');uart_tx('\r');uart_tx('\n');
		uart_tx('W');uart_tx('o');uart_tx('r');uart_tx('l');uart_tx('d');uart_tx('!');uart_tx('\r');uart_tx('\n');
	}
	*/
	
    /* your code goes here */
	
	//For 122 iterations...
	for (int i = 0; i < 122; i++) {
		
		//Display the current generation of cells
		displayArray(cells);
		
		//Create the next generation of cells
		updateArray(cells);
	}
}

/* your subroutines go here */
void initializeArray(unsigned char *cp){
	
	//Initialize the white first half of the array
	for (int i = 0; i < 30; i++) {
		*(cp+i) = ' ';
	}
	
	//Assign the middle index black
	*(cp+30) = '*';
	
	//Initialize the white second half of the array
	for (int i = 31; i < 61; i++) {
		*(cp+i) = ' ';
	}
}
void displayArray(unsigned char *cp){
	// ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
	// At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
	// output aligned properly.
	
	//Start a new line, align
	uart_tx('\r');
	uart_tx('\n');
	
	//Print each cell
	for (int i = 0; i < 61; i++) {
		uart_tx(*(cp + i));
	}
	
}
void updateArray(unsigned char *cp){
	
		//Create a placeholder char array for the next generation
		unsigned char next[61];
		//Set endpoints to white
		next[0] = ' ';
		next[60] = ' ';
		
		//Update cell states per Wolfram Rule 26
		for (int i = 1; i < 60; i++) {
			//Read current cell states (adjacent left, current index, adjacent right)
			unsigned char left = *(cp + i - 1);
			unsigned char current = *(cp + i);
			unsigned char right = *(cp + i + 1);
			
			//Apply Wolfram Rule 26
			next[i] = generateCell(left, current, right);
			
			//next[i] = ((26 >> 
		}
		
		//Copy the next generation over the current generation
		memcpy(cp, next, 61);
}
unsigned char generateCell(unsigned char left, unsigned char current, unsigned char right) {
	
	//Wolfram Rule 26 rule set for 1-D cellular automata
	//Input cases 1-8 accounted for methodically
	
	//Case 1:
	if (current == '*' && left == '*' && right == '*')
		return ' ';
		
	//Case 2:
	if (current == '*' && left == '*' && right == ' ')
		return ' ';
		
	//Case 3:
	if (current == ' ' && left == '*' && right == '*')
		return ' ';
		
	//Case 4:
	if (current == ' ' && left == '*' && right == ' ')
		return '*';
		
	//Case 5:
	if (current == '*' && left == ' ' && right == '*')
		return '*';
		
	//Case 6:
	if (current == '*' && left == ' ' && right == ' ')
		return ' ';
		
	//Case 7:
	if (current == ' ' && left == ' ' && right == '*')
		return '*';
		
	//Case 8:
	if (current == ' ' && left == ' ' && right == ' ')
		return ' ';
	/*
	//If current is black
	if(current == '*'){
		
		//If left is black
		if(left == '*'){
			
			//Rule 1: "* * *" -> ' '
			//Rule 2: "* *  " -> ' '
			return ' ';
		}
		
		//If right is black
		else if(right == '*'){
			
			//Rule 5: "  * *" -> '*'
			return '*';
		}
		
		//Rule 6: "  *  " -> ' '
		return ' ';
	}
	
	//If current is white
	else if(current == ' '){
		
		//If left is black
		if(left == '*'){
			
			//If right is black
			if(right == '*'){
				
				//Rule 3: "*   *" -> ' '
				return ' ';
			}
			
			//Rule 4: "*    " -> '*'
			return '*';
		}
		
		//If left is white
		else if(left == ' '){
			
			//If right is black
			if(right == '*'){
				
				//Rule 7: "    *" -> '*'
				return '*';
			}
		}
	}
	//Rule 8: "     " -> ' ';
	return ' ';
	*/
}
