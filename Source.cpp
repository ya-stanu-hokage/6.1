#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

void delete_comment(std::string& str);

int main()
{
	std::string s;
	{
		std::ifstream file("test.txt", std::ios::in);
		if (file) {
			std::ostringstream os;
			os << file.rdbuf();
			s = os.str();
		}
		else {
			std::cerr << "File not found" << std::endl;
		}
	}

	delete_comment(s);

	std::ofstream fout;
	fout.open("test_out.txt", std::ios::out);
	fout << s;

	return 0;
}

void delete_comment(std::string& str)
{
	std::string::iterator last;
	for (std::string::iterator iterator = str.begin(); iterator != str.end(); iterator++)
	{
		if (*iterator == '"')
			for (iterator++; (*(iterator - 1) == '\\' || *iterator != '"') && iterator != str.end(); iterator++);
		if (*iterator == '/')
		{
			if (*(iterator + 1) == '/')
			{
				for (last = iterator + 1; *last != '\n' && last != str.end(); last++);
				str.erase(iterator, last);
			}
			else if (*(iterator + 1) == '*')
			{
				for (last = iterator + 2; *last != '*' && *(last + 1) != '/'; last++);
				last += 2;
				str.erase(iterator, last);
			}
		}
	}
}