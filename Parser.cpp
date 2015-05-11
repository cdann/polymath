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
	 //a*X^2 + b*X^1 + c*X = d*X
	std::string member;
	int i = 0;
	int c = 0;
	bool b = false;
	bool s = false;

	for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
	{

		if ((*it == '+' || *it == '-' || *it == '=' ) && (i - c > 1 || s == true))
		{
			//std::cout << "##DEBUG i - c :" << i - c << " s : " << s << std::endl;
			member = str.substr(c, i - c);
			this->extractMember(member, b);
			c = i;
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
		{
			std::cout << "&";
			s = true;
		}
			//std::cout << "%";
		//std::cout << "::" << *it;
		// if (*it != ' ' && *it != '=' && s == false)
		//{
		//	std::cout << "&";
		//	s = true;
		//}
		i++;
	}
	member = str.substr(c, i - c);
	this->extractMember(member, b);
}

int Parser::extractMember(std::string str, bool b)// si le bool est a 0 premiere partie de l'equation sinon apres le egal
{
	//std::cout << " ##DEBUG :" << str << std::endl;

	//std::cout << str;
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
  			if ((found = str.find("^")) != std::string::npos)
  			{
  				found++;
  				p = str.substr(found, str.length() - found);
  			}
  			else
			{
				Poly::setSimpleForm();
				p = "1";
			}

			//if (str[found + 2] == '^' && (found + 3) < str.length())
			//{
			//	found += 3;
			//	p = str.substr(found, str.length() - found);
			//}
			//else
			//{
			//	Poly::setSimpleForm();
			//	p = "1";
			//}
		}
  	}
  	else
  	{
  		found = str.find("X");


  		if (found != std::string::npos)
  		{
				//std::cout << "passe ici st: " << str << std::endl;
  			n = (found == 0) ? "1" : str.substr(0, found);
	  		//std::cout << " str : " << found +2 << " size : " << str.length();
  			p = ((found + 2) == str.length()) ?  "1" : str.substr(found +2, str.length());
  			if ((found = p.find("^")) != std::string::npos)
  				p = p.substr(found +1, p.length());


  		}
  		else
  		{
	  		p = "0";
  			n = str;
  		}
  		Poly::setSimpleForm();
  	}
	//std::cout << " %%%%DEBUG2 : nb :" << n << " pow :" << p << std::endl;

	return addMember(n, p, b);
}

std::string Parser::trim(std::string str)
{
	unsigned int end = 0;
	unsigned int start = 0;
	std::string ret;

	for (std::string::iterator it=str.begin(); it!=str.end(); it++)
	{
		if (*it == ' ')
			start++;
		else
			break;
	}
	for (std::string::reverse_iterator it=str.rbegin(); it!=str.rend(); it++)
	{
		if (*it == ' ')
			end++;
		else
			break;
	}
	ret = str.substr(start, str.length() - end - start);
	return (ret);
}

bool Parser::isdigit(std::string str)
{
	bool point = false;
	bool in = false;

	for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
	{
		in = true;
		if (!((*it >= '0' && *it <= '9') || (*it == '.' && !point) || (*it == '-' && it == str.begin()) || (*it == '+' && it == str.begin()) || *it == ' '))
			return false;
		point = (*it == '.') ? true : point;
	}
	if (!in)
		return false;
	return true;
}

int Parser::addMember(std::string n,std::string p, bool b)
{
	double n1;
	int		p1;
		//std::cout << "DEBUG : p :" << p << " n : " << n << std::endl;
	n = this->trim(n);

	p = this->trim(p);
	if (!this->isdigit(n) || !this->isdigit(p))
	{
		this->error = true;
		std::cout << "their is an error in the entrie" << std::endl;
		//std::cout << "DEBUG : p :" << p << " n : " << n << std::endl;
		return 0;
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



