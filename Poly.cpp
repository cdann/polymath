#include "Poly.hpp"
# include "Parser.hpp"
#include <iostream>

Poly::Poly(){
}

Poly::~Poly(){}

Poly::Poly(Parser parse){
	if (print_first_part(parse) == true)
	{
		calculate(parse);
		print_result();
	}
}


bool Poly::print_first_part(Parser parse)
{
	std::map<int, double>	po;
	int						deg;

	po = parse.getPoly();
	std::cout << "Reduced form: ";
	for (std::map<int,double>::iterator it=po.begin(); it!=po.end(); ++it)
	{
		if (it != po.begin())
			std::cout << " + ";
		std::cout << it->second << "*X^" << it->first;
	}
	std::cout << std::endl;
	deg = parse.getDegree();
	std::cout << "Polynomial degree: " << deg << std::endl;
	if (deg <= 2)
		return true;
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
	return false;
}

void Poly::calculate(Parser parse)
{
	std::map<int, double>	po = parse.getPoly();

	if (po.find(0) != po.end())
		_c = parse[0];
	if (po.find(1) != po.end())
		_b = parse[1];
	if (po.find(2) != po.end())
		_a = parse[2];

	this->_delta = (_b * _b) - (4 * _a * _c);
	if (this->_delta > 0)
	{
		_X1 = (-_b - this->Sqrt(_delta))/ (2 * _a);
		_X2 = (-_b + this->Sqrt(_delta))/ (2 * _a);
	}
	if (this->_delta == 0)
		_X1 = (-_b)/ (2 * _a);
}

void Poly::print_result()
{
	if (this->_delta > 0)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		std::cout << _X1<< std::endl;
		std::cout << _X2<< std::endl;
	}
	else if (this->_delta == 0)
	{
		std::cout << "Discriminant is strictly equal to 0, the solution is:" << std::endl;
		std::cout << _X1<< std::endl;

	}
	else
	{
		std::cout << "Discriminant is strictly negative, their is no solution." << std::endl;
	}
}

double Poly::Sqrt(double X)
{
  double A;
  double B;
  double M = 1.0;
  double XN;

  if(X==0.0) {
     return 0.0;
  } else {
     M=1.0;
     XN=X;
     while(XN>=2.0) {
        XN=0.25*XN;
        M=2.0*M;
     }
     while(XN<0.5) {
        XN=4.0*XN;
        M=0.5*M;
     }
     A=XN;
     B=1.0-XN;
     do {
        A=A*(1.0+0.5*B);
        B=0.25*(3.0+B)*B*B;
     } while(B>=1.0E-15);
     //std::cout << X << " vs " << A*M << std::endl;
     return A*M;
  }
}
