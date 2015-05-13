#include "Parser.hpp"
#include "Poly.hpp"
#include <iostream>
#include <stdlib.h>
#include <locale>

bool Parser::debug = false;

void Parser::setDebug()
{
	Parser::debug = true;
}

bool Parser::getDebug()
{
	return Parser::debug;
}

Parser::Parser(): degree(0), error(false)
{}

Parser::~Parser()
{}



Parser::Parser(std::string equa): degree(0), error(false)
{
	this->parse(equa);
}

bool  Parser::parse(std::string str)
{
	this->splitByPart(str);
	return !this->error;
}


void Parser::splitByPart(std::string str)
{
	std::string member;
	int i = 0;
	int c = 0;
	bool b = false;
	bool s = false;
	bool sign = false;

	for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
	{

		if ((*it == '+' || *it == '-' || *it == '=' ) && (i - c > 1 || s == true))
		{
			member = str.substr(c, i - c);

			if ((s == true || !Tester.isonlyspace(member)) && !Tester.isonlyspace(str.substr(c + 1, i - c - 1)))
				this->extractMember(member, b);
			if (Tester.isonlyspace(str.substr(c + 1, i - c - 1)) && (*it == '+' || *it == '-'))
			{
				if (sign == false)
					sign = true;
				else
				{
					std::cout << "too many operators (+++ or ---)" << std::endl;
					this-> error = true;
				}
			}
			else
			{
				if (sign == true)
					sign = false;
				c = i;
			}
			if (*it == '=')
			{
				s = false;
				if (b == true)
				{
					std::cout << "their is an error in the entrie, too many equal" << std::endl;
					this-> error = true;
				}
				c ++;
				b = true;
			}
		}
		else if (*it != ' ' && s == false)
			s = true;

		i++;
	}
	member = str.substr(c, i - c);
	this->extractMember(member, b);
	if  (b == false)
	{
		std::cout << "their is an error in the entrie, without equal this is not an equation" << std::endl;
					this-> error = true;
	}
}

int Parser::extractMember(std::string str, bool b)// si le bool est a 0 premiere partie de l'equation sinon apres le egal
{
	std::string n;
	std::string p;

	std::size_t found = str.find("*");
	if (found!=std::string::npos)
	{
		n = str.substr(0, found);
		if (((found + 1) < str.length() && str[found + 1] == ' '))
			str = str.erase(found + 1, 1);
		if (((found + 1) < str.length() && str[found + 1] == 'X'))
		{
			found += 2;
			while (str[found]  == ' ' && found != str.length())
				found ++;
  			if (str[found]  == '^')
  			{
  				found++;
  				p = str.substr(found, str.length() - found);
  			}
  			else if (found == str.length())
			{
				Poly::setSimpleForm();
				p = "1";
			}

		}
  	}
  	else
  	{
  		found = str.find("X");


  		if (found != std::string::npos)
  		{
  			n = (found == 0) ? "1" : str.substr(0, found);
  			p = str.substr(found +2, str.length());
  			if ((found = p.find("^")) != std::string::npos)
  				p = p.substr(found +1, p.length());
  			if (Tester.isonlyspace(p))
  				p = "1";
  		}
  		else
  		{
	  		p = "0";
  			n = str;
  		}
  		Poly::setSimpleForm();
  	}
	int ret = addMember(n, p, b);
	if (ret == -1)
		std::cout << str;

	return (ret);
}

int Parser::addMember(std::string n,std::string p, bool b)
{
	double n1;
	int		p1;
	Tester.trim(n);

	Tester.trim(p);
	Tester.getsign(n);

	if (!Tester.isdigit(n) || !Tester.isdigit(p))
	{
		this->error = true;
		std::cout << "their is an error in the entrie near : " << std::endl;
		return -1;
	}


	p1 = atoi(p.c_str());
	if (n[1] == ' ')
		n = n.erase (1, 1);
	n1 = std::strtod(n.c_str(), NULL);
	(b) ? n1 *= -1 : n1 ;
	if (Parser::debug)
		std::cout << "=> X^" << p1 << " * (" << this->p[p1] << " + " << n1 << ")" << std::endl;
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



