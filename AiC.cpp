#include <iostream>
#include"Calc.h"

int main()
{

	ComplexMatrix square_m1(6, 6);
	ComplexMatrix square_m2(6, 6);

	square_m1.auto_gen(1, 5, 1, 5);
	square_m2.auto_gen(1, 5, 1, 5);

	square_m1.print();
	std::cout << "----------------------" << std::endl;
	square_m2.print();
	std::cout << "----------------------" << std::endl;
	Strassen(&square_m1, &square_m2)->print();


}

