#ifndef POLY_H
#define POLY_H

# include "Parser.hpp"
# include <vector>

class Poly
{
public:
	Poly();
	Poly(Parser parse);
	~Poly();

private:
	double _X1;
	double _X2;
	double _delta;

	double _a;
	double _b;
	double _c;

	bool print_first_part(Parser parse);
	void calculate(Parser parse);
	void print_result(void);
	double Sqrt(double X);
};

#endif
