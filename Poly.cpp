#include <stdio.h>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Poly.h"
#define _MAX_CHAR_ 255
#define _MAX_VAL_ 50

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
	std::vector<double>coefficients;
	std::vector<int>exponents;
	double c;
	int e;
	char* temp, * endptr;

	temp = new char[_MAX_CHAR_];

	for (int i = 0; i < sizeof(iss_temp); i++) temp[i] = ' ';

	for (int i = 0; i < sizeof(iss_temp); i++)
		iss_temp >> std::skipws >> temp[i];

	std::istringstream iss(temp);

	std::getline(iss, buffer);

	if (buffer[0] >= '0' && buffer[0] <= '9')
		buffer = "+" + buffer;

	// start obtaining the coefficients and exponents of terms
	for (int i = 0; i < buffer.length(); i++) {

		// declare stringstream format for storing and swift conversion of strings
		std::stringstream coeff_iss;
		std::stringstream exp_iss;

		// declare new coeff and exp
		double new_coeff;
		int new_exp;

		coeff = "";
		exp = "";

		// get sign of buffer[i]
		bool sign = (buffer[i] == '-') ? 1 : 0;

		// position of coefficient
		i += 1;

		// append coefficient as 1 
		if (buffer[i] == 'x') {

			coeff = '1';
		}

		// append numbers before x - coefficients
		while (buffer[i] != 'x' && buffer[i] != ' ') {

			coeff += buffer[i];
			i++;
		}

		// series of test to specify the correct exponent and coefficient
		if (buffer[i] == 'x' && buffer[i + 1] != '^') {

			exp = '1';
			i += 1;
		}

		else if (buffer[i] != 'x' && buffer[i + 1] != '^') {

			exp = '0';

			coeff_iss << coeff;
			coeff_iss >> new_coeff;

			exp_iss << exp;
			exp_iss >> new_exp;

			if (sign) {

				new_coeff = new_coeff * -1;
			}

			// save coefficients and exponents
			coefficients.push_back(new_coeff);
			exponents.push_back(new_exp);

			break;
		}

		else {

			// shift to the exponent position
			i += 2;
		}

		// now append the exponents before the end of the term
		while (buffer[i] != '+' && buffer[i] != '-' && buffer[i] != ' ') {

			exp += buffer[i];
			i++;
		}

		// convert coeff and exp in their whole numbers
		coeff_iss << coeff;
		coeff_iss >> new_coeff;

		exp_iss << exp;
		exp_iss >> new_exp;

		// check for coefficient sign and update if necessary
		if (sign) {

			new_coeff = new_coeff * -1;
		}

		coefficients.push_back(new_coeff);
		exponents.push_back(new_exp);

		i--;

	}

	//// output results

	//for (int i = 0; i < coefficients.size(); i++)
	//	std::cout << coefficients[i] << " ";

	//std::cout << std::endl;

	//for (int i = 0; i < exponents.size(); i++)
	//	std::cout << exponents[i] << " ";

	std::cout << std::endl;

	// create a Polynomial node based on exponents and coefficients

	for (int i = 0; i < coefficients.size(); i++) {

		c = coefficients[i];
		e = exponents[i];

		poly = AddNode(poly, c, e);
	}

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

	// allocated space for temp node from heap

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
	}

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
	}

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
	}

	return node;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){

	PolyNode* node = new PolyNode();
	PolyNode* temp = NULL;
	double c;
	int e;



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
	}

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
	}

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

	char** graph;
	int y;

	graph = new char*[_MAX_VAL_];

	for (int i = -_MAX_VAL_; i < _MAX_VAL_; i++) {

		graph[i] = new char[_MAX_VAL_];
	}

	for (int i = -_MAX_VAL_; i < _MAX_VAL_; i++) {

		for (int j = -_MAX_VAL_; j < _MAX_VAL_; j++) {

			graph[i][j] = ' ';
		}
	}
	
	for (int i = -_MAX_VAL_; i < _MAX_VAL_; i++) {

		for (int j = -_MAX_VAL_; j < _MAX_VAL_; j++) {

			if (j == -1*(x1 + x2) / 2)
				graph[j][i] = '|';
			if (i == -1*(x1 + x2) / 2)
				graph[j][i] = '-';
		}
	}

	for (int i = x1; i < x2; i++) {

		y = Evaluate(poly, i);
		graph[i][y] = '*';
	}

	for (int i = x1; i < x2; i++) {

		for (int j = x1; j < x2; j++) {

			std::cout << graph[j][i];
		}

		std::cout << "\n";
	}

} //end-Plot
