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
		}
	}
	return true;
}

void usage(char const *name)
{
	std::cout << "usage: " << name << "monequation"<< std::endl;
	std::cout << "options: -f to factor form"<< std::endl;


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
		p.parse(argv[argc-1]);
		//p.test();
		Poly calcul(p);
	}
	else
	{
		usage(argv[0]);
	}
	return 0;
}
