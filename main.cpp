#include "Parser.hpp"
#include "Poly.hpp"
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		Parser p;
		p.parse(argv[1]);
		p.test();
		Poly calcul(p);
	}
	else
	{
		std::cout << "usage: " << argv[0] << "monequation"<< std::endl;
	}
	return 0;
}
