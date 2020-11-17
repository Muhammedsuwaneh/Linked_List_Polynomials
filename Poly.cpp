#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "Poly.h"
#define _MAX_CHAR 255

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode *CreatePoly(char *expr){	

	// initialize PolyNode
	PolyNode* poly = NULL;

	/*
	  obtain Polynomial string, coefficients and exponents
	*/
	std::istringstream iss_temp(expr);
	std::string buffer, coeff, exp;
	char* temp;

	temp = new char[_MAX_CHAR];

	for (int i = 0; i < sizeof(iss_temp); i++) temp[i] = ' ';

	// remove white spaces from string
	for (int i = 0; i < sizeof(iss_temp); i++)
		iss_temp >> std::skipws >> temp[i];

	std::istringstream iss(temp);

	// ax^n + bx^n-1....c
	std::getline(iss, buffer);

	if (buffer[0] >= '0' && buffer[0] <= '9')
		buffer = "+" + buffer;

	// initialize seekers
	int i = 0, j = 0;

	// first term coeff's sign 
	if (buffer[0] == '-' || buffer[0] == '+') i++;

	// start obtaining the coefficients and exponents of terms
	while (i < buffer.length()) {

		// std::stringstream declaration
		std::stringstream coeff_iss;
		std::stringstream exp_iss;

		// declare temp coeff and exp
		double c = 0;
		int e = 0;

		// empty strings
		coeff = "";
		exp = "";

		// check for coeff sign
		bool sign = (buffer[j] == '-') ? true : false;

		// seek coefficients
		while (1) {

			// 1x^n -> x
			if (buffer[i] == 'x') {

				coeff = '1';
				break;
			}

			// ax^n -> ax^n
			while (buffer[i] != 'x' && buffer[i] != ' ') {

				coeff += buffer[i];
				i++;

			}// end-while-loop

			break;
		}// end-while-loop

		// seek exponents 
		while (1) {
            
			// ax^0 -> a
			if (buffer[i] != 'x' && buffer[i + 1] != '^' && coeff != "1") {
				exp = '0';
				break;
			}

			// ax^1 -> ax
			else if (buffer[i] == 'x' && buffer[i + 1] != '^') {
				exp = '1';
				break;
			}

			else {

				// shift to exponent
				i += 2;
				while (buffer[i] != '+' && buffer[i] != '-') {
					exp += buffer[i];
					i++;
				}
				// end-while-loop

				break;
			}

		}// end-while-loop

		// convert coefficients and exponents to int and double

		coeff_iss << coeff;
		coeff_iss >> c;

		exp_iss << exp;
		exp_iss >> e;

		// append sign if true
		if (sign == true) c = c * -1;

		// add coefficients and exponents to node
		poly = AddNode(poly, c, e);

		i++;
		j = i - 1;

		// stop seeking
		if (buffer[i] == ' ') break;

	}
	// end-while-loop

	std::cout << std::endl;

	// return new Polynode created
	return poly;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	delete poly;
} // end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp){

	PolyNode* temp, *curr, *prev;

	// allocate space for temp node from heap
	temp = new PolyNode();

	curr = prev = head;

	while (curr != NULL) {

		// compare new exponent and current node exponent
		if (exp > curr->exp) break;

		// check for duplicates
		if (exp == curr->exp) {

			curr->coef = curr->coef + coef;

			if (curr->coef == 0) {	

				PolyNode* new_temp;

				if (curr == head) {

					new_temp = head;
					head = new_temp->next;
					delete new_temp;
				}

				else {

					new_temp = prev->next;
					prev->next = new_temp->next;
					delete new_temp;
				}
			}
			
			return head;
			break;
		}

		// change position of current pointer 
		prev = curr;
		curr = curr->next;

	}// end-while-loop

	// assign coeff and exp to temp node
	temp->exp = exp;
	temp->coef = coef;
	temp->next = curr;

	if (head == curr) { head = temp; }

	else { prev->next = temp; }

	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode *Add(PolyNode *poly1, PolyNode *poly2){
	
	PolyNode* node = new PolyNode();
	double c;
	int e;

	while (poly1 != NULL && poly2 != NULL) {

		if (poly1->exp > poly2->exp) {

			c = poly1->coef;
			e = poly1->exp;
			node = AddNode(node, c, e);
			poly1 = poly1->next;
		}

		else if (poly2->exp > poly1->exp) {

			c = poly2->coef;
			e = poly2->exp;
			node = AddNode(node, c, e);
			poly2 = poly2->next;
		}

		else {

			c = poly1->coef + poly2->coef;
			e = poly1->exp;
			node = AddNode(node, c, e);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

	}// end-while-loop

	return node;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode *Subtract(PolyNode *poly1, PolyNode *poly2){

	PolyNode* node = new PolyNode();
	double c;
	int e;

	while (poly1 != NULL && poly2 != NULL) {

		if (poly1->exp > poly2->exp) {

			c = poly1->coef;
			e = poly1->exp;
			node = AddNode(node, c, e);
			poly1 = poly1->next;
		}

		else if (poly2->exp > poly1->exp) {

			c = poly2->coef;
			e = poly2->exp;
			node = AddNode(node, c, e);
			poly2 = poly2->next;
		}

		else {

			c = poly1->coef - poly2->coef;
			e = poly1->exp;
			node = AddNode(node, c, e);
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

	}// end-while-loop

	return node;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){

	PolyNode* node = new PolyNode();
	PolyNode* A = NULL, *B = NULL;
	double c;
	int e;

	A = poly1;

	while (A != NULL) {

		B = poly2;

		while (B != NULL) {

			c = A->coef * B->coef;
			e = A->exp + B->exp;
			node = AddNode(node, c, e);
			B = B->next;
		}

		A = A->next;

	}// end-while-loop

	return node;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x){
	double result = 0;

	while (poly != NULL) {

		result += poly->coef * pow(x, poly->exp);
		poly = poly->next;

	}// end-while-loop

	return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode *Derivative(PolyNode *poly){
	PolyNode* node = new PolyNode();
	double c;
	int e;

	while (poly != NULL) {

		if (poly->exp != 0) {

		   c = poly->coef * poly->exp;
		   e = poly->exp - 1;
		   node = AddNode(node, c, e);
		}

		poly = poly->next;

	}// end-while-loop

	return node;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){

	const int a = 39;
	const int b = 12;

    char** _graph = new char*[a];
	double fx = NULL;

	for(int i = -a; i <= a; i++) 
		_graph[i] = new char[a];

	// initialize graph with spaces
	for (int x = -a; x <= a; x++) {

		for (int y = -a; y <= a; y++) {

			_graph[x][y] = ' ';
		}
	}

	// scale x-cordinate and draw lines
	for (int x = -a; x <= a; x++) {

		  _graph[x][0] = '-';
	}

	for (int x = 0; x <= a; x+=5) {

		_graph[x][0] = '+';
	}

	for (int x = 0; x >= -a; x -= 5) {

		_graph[x][0] = '+';
	}

	// scale y-cordinate and draw lines
	for (int y = b; y >= -b; y--) {

		_graph[0][y] = '|';
	}

	for (int y = 0; y >= -b; y-=5) {

		_graph[0][y] = '+';
	}

	for (int y = 0; y <= b; y += 5) {

		_graph[0][y] = '+';
	}

	// fix points on graph
	for (int y = b; y >= -b; y--) {

		for (int x = -a; x <= a; x++) {

			if (x >= x1 && x <= x2) {

				fx = Evaluate(poly, x);

				if ((int)fx == y && fx != NULL)
					_graph[x][y] = '*';
			}
		}
	}

	// print graph
	for (int y = b; y >= -b; y--) {

		for (int x = -a; x <= a; x++) {

			 std::cout << _graph[x][y];
		}
		std::cout << "\n";
	}

} //end-Plot
