#ifndef TEST_H
# define TEST_H
# include <string>


class TestStr
{
	public:
		bool	isdigit(std::string);
		bool	isonlyspace(std::string str);
		void	trim(std::string & str);
		void	getsign(std::string & str);
		bool	isSpace(char c);
};

#endif
