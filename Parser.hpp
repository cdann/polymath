#ifndef PARSE_H
# define PARSE_H
# include <string>
# include <map>
# include "TestStr.hpp"

class Parser
{
public:
	Parser(std::string equa);
	~Parser();
	Parser();

	bool 					parse(std::string);
	void 					test(void);
	static void				setDebug(void);
	static bool				getDebug(void);

	int						getDegree();
	std::map<int,double>	getPoly();
	double 					operator[](int n);

private:
	int 					degree;
	std::map<int,double>	p;
	bool					error;
	TestStr					Tester;

	int extractMember(std::string, bool);// si le bool est a 0 premiere partie de l'equation sinon 2eme partie
	int addMember(std::string,std::string, bool);// si le bool est a 0 premiere partie de l'equation sinon 2eme partie
	void splitByPart(std::string);
	static bool				debug;

};

#endif

