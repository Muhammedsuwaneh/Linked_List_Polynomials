#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "PolyNode.h"
#include "Poly.h"

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();

int main() {

	// set windows console size
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1200, 1200, false);

	printf("====================================================================================\n\n");
	Test1();
	printf("====================================================================================\n\n");
	Test2();
	printf("====================================================================================\n\n");
	Test3();
	printf("====================================================================================\n\n");
	Test4();
	printf("====================================================================================\n\n");
	Test5();
	printf("====================================================================================\n\n");
	Test6();
	printf("====================================================================================\n\n");
	Test7();
	printf("====================================================================================\n\n");
	Test8();
	printf("====================================================================================\n\n");

	return 0;
} // end-main

//-------------------------------------------------
// Prints a polynomial in a nicely formatted manner
//
void Print(PolyNode* poly) {
	if (poly == NULL) { printf("<NULL>\n"); return; }

	printf("<");
	PolyNode* p = poly;
	while (p != NULL) {
		if (p->exp == 0) {
			printf("%+-3.1f", p->coef);

		}
		else if (p->exp == 1) {
			if (p->coef == 1.0) printf("+x ");
			else if (p->coef == -1.0) printf("-x ");
			else printf("%+-3.1fx ", p->coef);

		}
		else {
			if (p->coef == 1.0) printf("+x^%-2d ", p->exp);
			else if (p->coef == -1.0) printf("-x^%-2d ", p->exp);
			else printf("%+-3.1fx^%-2d ", p->coef, p->exp);
		} //end-else

		p = p->next;
	} // end-while

	printf(">\n");
} //end-Print	

/// ---------------------------------------------------------
/// Test1
/// 
void Test1() {
	printf("%40s", "****** TEST 1 ******\n");

	PolyNode* poly = NULL;
	printf("Initial poly: "); Print(poly);

	poly = AddNode(poly, -2, 5);
	printf("Adding -2x^5: "); Print(poly);

	poly = AddNode(poly, 4.4, 7);
	printf("Adding 4.4x^7: "); Print(poly);

	poly = AddNode(poly, 2, 3);
	printf("Adding 2x^3: "); Print(poly);

	poly = AddNode(poly, 1, 4);
	printf("Adding x^4: "); Print(poly);

	poly = AddNode(poly, 4, 4);
	printf("Adding 4x^4: "); Print(poly);

	poly = AddNode(poly, 2, 5);
	printf("Adding 2x^5: "); Print(poly);

	poly = AddNode(poly, -4.4, 7);
	printf("Adding 4.4x^7: "); Print(poly);

	poly = AddNode(poly, -2, 3);
	printf("Adding -2x^3: "); Print(poly);

	poly = AddNode(poly, -5, 4);
	printf("Adding -5x^4: "); Print(poly);

	// other coefficients and exponents test
	poly = AddNode(poly, -10.5, 2);
	printf("Adding -10.5x^2: "); Print(poly);

	poly = AddNode(poly, 0.5, 3);
	printf("Adding 0.5x^3: "); Print(poly);

	poly = AddNode(poly, 1.5, 10);
	printf("Adding 1.5x^10: "); Print(poly);

	poly = AddNode(poly, -0.5, 3);
	printf("Adding -0.5x^3: "); Print(poly);

	poly = AddNode(poly, 10.5, 2);
	printf("Adding 10.5x^3: "); Print(poly);

	poly = AddNode(poly, -1.5, 10);
	printf("Adding -1.5x^10: "); Print(poly);

} // end-Test1

///----------------------------------------------------------------
/// Test2: Creates several polys from expressions
///
void Test2() {

	printf("%40s", "****** TEST 2 ******\n");

	// tested
	PolyNode *poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("[-x^3  -  6x^2 + 4x + 22]: "); Print(poly);
	DeletePoly(poly);

	// tested
	poly = CreatePoly((char*)"-x^2 +x  -  5");
	printf("[-x^2 +x  -  5]: "); Print(poly);
	DeletePoly(poly);

	// tested
	poly = CreatePoly((char*)"2.3x^4 + 5x^3 - 2.6x - 4");
	printf("[2.3x^4 + 5x^3 - 2.6x - 4]: "); Print(poly);
	DeletePoly(poly);

	poly = CreatePoly((char*)"-4.5x^10 - 45.44");
	printf("[-4.5x^10 - 45.44]: "); Print(poly);
	DeletePoly(poly);

	// tested
	poly = CreatePoly((char*)"x^6 + 24.6x^4 - x^3 - 61.3x^1 + 4.2");
	printf("[x^6 + 24.6x^4 - x^3 - 61.3x^1 + 4.2]: "); Print(poly);
	DeletePoly(poly);

	// tested
	poly = CreatePoly((char*)" -x^34+x^20 -34.3x^5  +   x -  55");
	printf("[ -x^34+x^20 -34.3x^5  +   x -  55]: "); Print(poly);
	DeletePoly(poly);

	// tested
	poly = CreatePoly((char*)"x^6 + 24.6x^4 - x^3 - 61.3x + 4.2");
	printf("[x^6 + 24.6x^4 - x^3 - 61.3x + 4.2]: "); Print(poly);
	DeletePoly(poly);
    
	// tested
	poly = CreatePoly((char*)"-33");
	printf("[-33]: "); Print(poly);
	DeletePoly(poly);

} //end-Test2

///----------------------------------------------------------------
/// Creates two polys and adds them up
///
void Test3() {
	printf("%40s", "****** TEST 3 ******\n");

	PolyNode *poly1 = CreatePoly((char*)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+4x+22]: "); Print(poly1);

	PolyNode *poly2 = CreatePoly((char*)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode *poly3 = Add(poly1, poly2);
	printf("-------------------------------------------------------(+)\n");
	printf("%25s", "Poly1+Poly2: "); Print(poly3);

	DeletePoly(poly1);
	DeletePoly(poly2);
	DeletePoly(poly3);
} //end-Test3

	//----------------------------------------------------------------
	// Creates two polys and subtracts one from the other
	//
void Test4() {
	printf("%40s", "****** TEST 4 ******\n");

	PolyNode *poly1 = CreatePoly((char*)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+4x+22]: "); Print(poly1);

	PolyNode *poly2 = CreatePoly((char *)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode *poly3 = Subtract(poly1, poly2);
	printf("-------------------------------------------------------(-)\n");
	printf("%25s", "Poly1-Poly2: "); Print(poly3);
} //end-Test4

//----------------------------------------------------------------
// Creates two polys and multiplies them
//
void Test5() {
	printf("%40s", "****** TEST 5 ******\n");

	PolyNode* poly1 = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly1[-x^3-6x^2+ 4x+22]: "); Print(poly1);

	PolyNode* poly2 = CreatePoly((char *)"-x^2 +x  -  5");
	printf("%25s", "Poly2[-x^2+x-5]: "); Print(poly2);

	PolyNode* poly3 = Multiply(poly1, poly2);
	printf("---------------------------------------------------------(*)\n");
	printf("%25s", "Poly1*Poly2: "); Print(poly3);
} //end-Test5

//----------------------------------------------------------------
// Creates a polynomial and evaluates it 
//
void Test6() {
	printf("%40s", "****** TEST 6 ******\n");

	PolyNode* poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly[-x^3-6x^2+ 4x+22]: "); Print(poly);
	printf("Evaluate(2): %4.2f\n", Evaluate(poly, 2.0));
	DeletePoly(poly);

	poly = CreatePoly((char*)"2x^3  -  4x^2 + 3x + 22");
	printf("%25s", "Poly[-x^3-6x^2+ 4x+22]: "); Print(poly);
	printf("Evaluate(-3): %4.2f\n", Evaluate(poly, -3.0));
	DeletePoly(poly);

} //end-Test6

//----------------------------------------------------------------
// Takes the derivative of a polynomial
//
void Test7() {
	printf("%40s", "****** TEST 7 ******\n");

	// poly 1
	PolyNode* poly = CreatePoly((char *)"-x^3  -  6x^2 + 4x + 22");
	printf("%25s", "Poly[-x^3-6x^2+ 4x+22]: "); Print(poly);

	PolyNode* deriv = Derivative(poly);
	printf("%25s", "Deriv[-x^3-6x^2+ 4x+22]: "); Print(deriv);

	DeletePoly(poly);
	DeletePoly(deriv);

	// other tested polynomials
	// poly 2
	poly = CreatePoly((char*)"2x^5-6x^4+ 4x^3+2x^2+3x+2");
	printf("%25s", "Poly[2x^5-6x^4+ 4x^3+2x^2+3x+2]: "); Print(poly);

	deriv = Derivative(poly);
	printf("%25s", "Deriv[2x^5-6x^4+ 4x^3+2x^2+3x+2]: "); Print(deriv);

	DeletePoly(poly);
	DeletePoly(deriv);

	// poly 3
	poly = CreatePoly((char*)"-10x^3 - 2.5x^2 + 1.3x - 0.5");
	printf("%25s", "Poly[-10x^3 - 2.5x^2 + 1.3x - 0.5]: "); Print(poly);

	deriv = Derivative(poly);
	printf("%25s", "Deriv[-10x^3 - 2.5x^2 + 1.3x - 0.5]: "); Print(deriv);

	DeletePoly(poly);
	DeletePoly(deriv);

} //end-Test7

//----------------------------------------------------------------
// Plots a polynomial on the screen
//
void Test8() {
	printf("%40s", "****** TEST 8 ******\n");
	printf("%40s\n\n", "Plot of the function 0.004x^3+0.04x^2-1.5x-4.3");

	// test 1 - Cubic graph 
    PolyNode* poly = CreatePoly((char *)"0.004x^3+0.04x^2-1.5x-4.3");
	std::cout << "\n###################################################\n";
	printf("Graph of: "); Print(poly);
	printf("Scale: x-axis- 1cm 5 units    y-axis- 1cm 5units\n");
	std::cout << "###################################################\n\n";
	Plot(poly, -30, 30);

	DeletePoly(poly);
	// test 2 - Positive Quadratic Graph

	poly = CreatePoly((char*)"0.3x^2+0.4x-5.4");
	std::cout << "\n###################################################\n";
	printf("Graph of: "); Print(poly);
	printf("Scale: x-axis- 1cm 5 units     y-axis- 1cm 5units\n");
	std::cout << "###################################################\n\n";
	Plot(poly, -30, 30);
	DeletePoly(poly);

	// test 3 - Negative Quadratic Graph

	poly = CreatePoly((char*)"-0.02x^2+0.5x-3.4");
	std::cout << "\n###################################################\n";
	printf("Graph of: "); Print(poly);
	printf("Scale: x-axis- 1cm 5 units     y-axis- 1cm 5units\n");
	std::cout << "###################################################\n\n";
	Plot(poly, -10, 10);
	DeletePoly(poly);
	//// test 4 - Positive Linear Graph

	//PolyNode* poly = CreatePoly((char*)"2.0x+4.5");
	//std::cout << "\n###################################################\n";
	//printf("Graph of: "); Print(poly);
	//printf("Scale: x-axis- 1cm 5 units     y-axis- 1cm 5units\n");
	//std::cout << "###################################################\n\n";
	//Plot(poly, -10, 10);
	//DeletePoly(poly);

	//// test 5 - Negative Linear Graph 
	//PolyNode* poly = CreatePoly((char*)"-2.0x-4.5");
	//std::cout << "\n###################################################\n";
	//printf("Graph of: "); Print(poly);
	//printf("Scale: x-axis- 1cm 5 units     y-axis- 1cm 5units\n");
	//std::cout << "###################################################\n\n";
	//Plot(poly, -10, 10);
	//DeletePoly(poly);
	
} //end-Test8



