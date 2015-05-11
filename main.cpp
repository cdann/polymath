#include "Parser.hpp"
#include "Poly.hpp"
#include <string>
#include <iostream>

bool	put_option(int argc, char const *argv[])
{
	int len;

	for (int i = 1; i < argc - 1; i++)
	{
		if (argv[i][0] != '-')
			return false;
		len = 0;
		while (argv[i][len] != '\0')
			len++;
		if (len != 2)
		{
			std::cout << "false " << len << std::endl;

			return false;
		}
		switch (argv[i][1])
		{
			case 'd':
				Parser::setDebug();
				break;

			case 'f':
				Poly::setFactor();
				break;

			case 's':
				Poly::setTableSign();
				break;

			case 'v':
				Poly::setVerbose();
				break;
		}
	}
	return true;
}

void usage(char const *name)
{
	std::cout << "usage: " << name << " monequation"<< std::endl;
	std::cout << "options: -f to factor form"<< std::endl;
	std::cout << "options: -v to see a b c and delta"<< std::endl;
	std::cout << "options: -d to see the operation in parsing"<< std::endl;
	std::cout << "options: -s to see the table of sign"<< std::endl;


}


int main(int argc, char const *argv[])
{
	if (argc >= 2)
	{
		Parser p;
		if (!put_option(argc, argv))
		{
			usage(argv[0]);
			return 0;
		}
		if (p.parse(argv[argc-1]))
			Poly calcul(p);
		//p.test();

	}
	else
	{
		usage(argv[0]);
	}
	return 0;
}
