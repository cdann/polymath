#include "Poly.hpp"
# include "Parser.hpp"
#include <iostream>
#include <complex>
#include <unistd.h>




Poly::Poly(): _delta(0), _a(0), _b(0), _c(0)
{
}

Poly::~Poly(){}

Poly::Poly(Parser parse):  _delta(0), _a(0), _b(0), _c(0)
{
	//if (Parser::getDebug())
	//	Poly::debug = true;
	if (this->print_first_part(parse) == true)
	{

		this->calculate(parse);
		if (Poly::verbose)
			this->show_verb();
		this->print_result();
		if (Poly::factor)
			this->show_factor();
		if (Poly::TableSign)
			this->show_TableSign();
	}
}

void 	Poly::show_verb()
{
	//std::cout << " _degree : " << _degree;
	std::cout << "In ax^2 + bx + c" << std::endl;
	std::cout << " c =  " << _c << std::endl;
	std::cout << " b =  " << _b << std::endl;
	std::cout << " a =  " << _a << std::endl << std::endl;
	//this->_delta = (_b * _b) - (4 * _a * _c);
	if (_degree >= 2)
		std::cout << " delta = " << _b << " ^2 - 4 * " << _a << " * " << _c << " = " << _delta << std::endl;
	std::cout << " racine 1 = " << _X1 << std::endl;
	if (_delta != 0)
		std::cout << " racine 2 = " << _X2 << std::endl<< std::endl;


}


void 	Poly::show_TableSign()
{
	std::string line;
	char sign;
	char sign2;
	double d1;
	double d2;

	if (this->_a != 0)
		sign = (this->_a >= 0) ? '+' : '-';
	else
		sign = (this->_b >= 0) ? '+' : '-';
	sign2 = (sign == '-') ? '+' : '-';

	if (_degree == 1)
	{
		line = "------------------------------\n";
		std::cout << "X0 = " << (-1 * _c) / _b << std::endl;

		std::cout << line;
		std::cout << "|   x  | -inf   | X0 |   +inf |"<< std::endl;
		std::cout << line;
		std::cout << "| f(x) | " << sign << "      |  0 |     " << sign << "  |"<< std::endl;
		std::cout << line;
	}
	 else if (_delta != 0)
	{
		line = "-----------------------------------------\n";
		d1 = (this->_X1 < this->_X2) ? this->_X1 : this->_X2;
		d2 = (d1 == this->_X2) ? this->_X1 : this->_X2;

		std::cout << "X1 = " << _X1 << std::endl;
		std::cout << "X2 = " << _X2 << std::endl;
		std::cout << line;
		std::cout << "|   x  | -inf    |  X1  |  X2  |    +inf |"<< std::endl;
		std::cout << line;
		std::cout << "| f(x) |   " << sign << "        |   " << sign2 << "   |        " << sign << "   |"<< std::endl;
		std::cout << line;
	}
	else
	{
		line = "-----------------------------\n";

		std::cout << "X0 = " << _X1 << std::endl;
		std::cout << line;
		std::cout << "|   x  | -inf   | X0 |   +inf |"<< std::endl;
		std::cout << line;
		std::cout << "| f(x) | " << sign << "      |  0 |     " << sign << "  |"<< std::endl;
		std::cout << line;
	}
	std::cout << std::endl;

}

void 	Poly::show_factor()
{
	if (_delta > 0)
	{
		std::cout << "factor form: ";
		std::cout << _a <<" * (X ";
		this->ope('-', _X1);
		std::cout << ") * (X ";
		this->ope('-', _X2);
		std::cout << ") = 0" << std::endl << std::endl;

	}
	else if (_delta == 0 && _degree  == 2)
	{
		std::cout << "factor form: ";
		std::cout << _a <<" * (X ";
		this->ope('-', _X1);
		std::cout << ")" << std::endl << std::endl;
	}
}


int		Poly::getNewDegree(std::map<int, double> po)
{
	int deg;

	deg = 0;
	for (std::map<int,double>::iterator it=po.begin(); it!=po.end(); ++it)
	{
		if (it->first > deg && it->second != 0)
			deg = it->first;
	}
	return deg;
}


bool Poly::print_first_part(Parser parse)
{
	std::map<int, double>	po;

	po = parse.getPoly();
	std::cout << "Reduced form: ";
	for (std::map<int,double>::iterator it=po.begin(); it!=po.end(); ++it)
	{
		if (it->second != 0)
		{
			if (it == po.begin())
				std::cout << it->second << " ";
			else
				this->ope('+', it->second);
			if (!(Poly::simpleForm && it->first == 0))
			{
				std::cout << "*X";
				if (!(Poly::simpleForm && it->first == 1))
					std::cout << "^" << it->first;
			}
		}
	}
	std::cout << " = 0" << std::endl;
	this->_degree = parse.getDegree();
	if (po[this->_degree] == 0)
		this->_degree = this->getNewDegree(po);
	std::cout << "Polynomial degree: " << this->_degree << std::endl;
	if (this->_degree <= 2)
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


	if (this->_degree == 2 && _a != 0)
	{
		this->_delta = (_b * _b) - (4 * _a * _c);

		if (this->_delta > 0)
		{
			_X1 = (-_b - this->Sqrt(_delta))/ (2 * _a);
			_X2 = (-_b + this->Sqrt(_delta))/ (2 * _a);
		}
		 else if (this->_delta == 0)
			_X1 = (-_b)/ (2 * _a);
		else
			this->imagine();

	}
	else
	{
		_X1 = (-_c)/ _b;
	}
	if (_X1 == -0)
		_X1 = 0;
	if (_X2 == -0)
		_X2 = 0;
}

void Poly::imagine()
{
	double im = this->Sqrt(_delta);

	_X2 = -_b/2*_a ;
	_X1 = im /2*_a;


}

void Poly::print_result()
{
		//std::cout << "_a = " << _a << " _b = " << _b << std::endl;

	if (this->_degree == 0 || (_a == 0 && _b == 0))
	{
		if ( _c != 0)
			std::cout << "No real number can be solution for this equation." << std::endl;
		else
			std::cout << "Every real number can be solution of this equation." << std::endl;
	}
	else if (this->_delta > 0)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		std::cout << _X1<< std::endl;
		std::cout << _X2<< std::endl;
	}
	else if (this->_delta == 0)
	{
		std::cout << "The solution is:" << std::endl;
		std::cout << _X1<< std::endl;
	}
	else
	{
		std::cout << "Discriminant is strictly negative, the two solutions are:" << std::endl;
		this->ope(' ', _X2);
		this->ope('+', _X1);
		std::cout << " * i" << std::endl;
		this->ope(' ', _X2);
		this->ope('-', _X1);
		std::cout << " * i" << std::endl;

		//(-b+isqrt(-delta))/2a
	}
}

void Poly::ope(char ope, double di)
{
	if (di >= 0)
		std::cout << ope;
	else if (ope == '-' && di != 0)
	{
		std::cout << "+";
		di *= -1;
	}
	else if (ope == '+' && di != 0)
	{
		std::cout << "-";
		di *= -1;
	}
	if (di != 0)
	{
		std::cout << " " << di;
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
  	if (X < 0)
  		X *= -1;
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
     return A*M;
  }
}

//----------------------------------------------------------------//
//                             Options                            //
//----------------------------------------------------------------//

bool Poly::verbose = false;
bool Poly::simpleForm = false;
bool Poly::TableSign = false;
bool Poly::factor = false;


void				Poly::setSimpleForm()
{
	Poly::simpleForm = true;
	//std::cout << "Les potes" << std::endl;
}

void				Poly::setVerbose()
{
	Poly::verbose = true;
	//std::cout << "Les potes" << std::endl;
}

void				Poly::setFactor()
{
	Poly::factor = true;
	//std::cout << "Les potes" << std::endl;
}

void				Poly::setTableSign()
{
	Poly::TableSign = true;
	//std::cout << "Les potes" << std::endl;
}


