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
	static void				setSimpleForm();
	static void				setFactor();


private:
	double _X1;
	double _X2;
	double _delta;
	double _degree;

	double _a;
	double _b;
	double _c;

	bool print_first_part(Parser parse);
	int	getNewDegree(std::map<int, double> po);
	void calculate(Parser parse);
	void print_result(void);
	double Sqrt(double X);
	void imagine();
	void show_factor();
	void ope(char ope, double di);
	static bool				simpleForm;
	static bool				factor;
	//static bool				debug;

};

#endif
