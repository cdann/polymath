#include "Parser.hpp"
#include "Poly.hpp"
#include <iostream>
#include <stdlib.h>

//bool Parser::debug = false;

Parser::Parser(): degree(0)
{}

Parser::~Parser()
{}

//void Parser::setDebug()
//{
//	Parser::debug = true;
//}
//
//bool Parser::getDebug()
//{
//	return Parser::debug;
//}


Parser::Parser(std::string equa): degree(0)
{
	this->parse(equa);
}

void Parser::parse(std::string str)
{
	this->splitByPart(str);
}

void Parser::splitByPart(std::string str)
{
	 //a*X^2 + b*X^1 + c*X = d*X
	std::string member;
	int i = 0;
	int c = 0;
	bool b = false;

	for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
	{
		if (*it == '+' || *it == '-' || *it == '=')
		{
			member = str.substr(c, i - c);
			this->extractMember(member, b);
			c = i;
			if (*it == '=')
			{
				c ++;
				b = true;
			}
		}
		i++;
	}
	member = str.substr(c, i - c);
	this->extractMember(member, b);
}
int Parser::extractMember(std::string str, bool b)// si le bool est a 0 premiere partie de l'equation sinon 2eme partie
{
	//n*X^p
	std::string n;
	std::string p;

	std::size_t found = str.find("*");
	if (found!=std::string::npos)
	{
		n = str.substr(0, found);
		if (((found + 1) < str.length() &&str[found + 1] == ' '))
			str = str.erase(found + 1, 1);
		if (((found + 1) < str.length() &&str[found + 1] == 'X'))
		{
			if (str[found + 2] == '^' && (found + 3) < str.length())
			{
				found += 3;
				p = str.substr(found, str.length() - found);
			}
			else
			{
				Poly::setSimpleForm();
				p = "1";
			}
		}
  	}
  	else
  	{
  		p = "0";
  		Poly::setSimpleForm();
  		n = str.substr(0, str.length());
  	}
	return addMember(n, p, b);
}

int Parser::addMember(std::string n,std::string p, bool b)
{
	//n*X^p
	double n1;
	int		p1;

	p1 = atoi(p.c_str());
	if (n[1] == ' ')
		n = n.erase (1, 1);
	n1 = std::strtod(n.c_str(), NULL);
	(b) ? n1 *= -1 : n1 ;
	this->p[p1] += n1;
	(p1 > this->degree) ? this->degree = p1 : this->degree;
	return p1;
}

void Parser::test(void)
{
	std::cout << " size: " << this->p.size() << " degree: " << this->degree << std::endl;
	for (std::map<int,double>::iterator it=this->p.begin(); it!=this->p.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}



double Parser::operator[](int n)
{
	std::map<int,double>::iterator it;
	if ((this->p).find(n) != this->p.end())
		return this->p[n];
	return 0;
}

int						 Parser::getDegree()
{
	return this->degree;
}

std::map<int,double>	 Parser::getPoly()
{
	return this->p;
}



