#include "Parser.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>


struct ParsingError : public std::exception
{
	public:
	std::string _msg;
	std::string _filename;
	size_t _line;

	ParsingError(std::string msg, std::string filename, size_t line) :
		_msg(msg),
		_filename(filename),
		_line(line)
	{}
};

void inline split(std::string &s, std::vector<std::string> &tokens)
{
	int toksize = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (std::isspace(s[i]))
		{
			if (toksize == 0)
				continue;
			else
			{
				tokens.push_back(s.substr(i - toksize, toksize));
				toksize = 0;
			}
		}
		else
			toksize++;
	}
	if (toksize > 0)
		tokens.push_back(s.substr(s.length() - toksize, toksize));
}

Object* Parser::read_obj(char* filename)
{
	std::ifstream fs;
	fs.open(filename);
	if (!fs.is_open())
		throw std::runtime_error("Could not open file : " + std::string(filename));

	Object* obj = new Object();

	std::string line;
	std::vector<std::string> tokens;
	size_t linenumber = 0;
	try
	{
		while (std::getline(fs, line))
		{
			linenumber++;
			if (line.length() == 0)
				continue;

			//split the line
			split(line, tokens);

			// Object name
			if (tokens[0] == "o")
			{
				if (obj->name.length() > 0)
					throw ParsingError("Name already defined above", filename, linenumber);
				// if the name isn't defined
				if (tokens.size() != 2)
					throw ParsingError("Object name malformed", filename, linenumber);
				obj->name = tokens[2];
			}
			// vertex coordinates
			if (tokens[0] == "v")
			{
				if (tokens.size() != 4)
					throw ParsingError("Vertex malformed", filename, linenumber);
				
			}
			// Polygonal face element
			if (tokens[0] == "f")
			{
				if (tokens.size() < 4)
					throw ParsingError("Needs at least 3 vertices index", filename, linenumber);

			}
			std::cout << std::endl;
			tokens.clear();
			//convert all negative vertices
		}
		if (obj->name == "")
			obj->name = "default_name";
		fs.close();
	}
	catch (ParsingError &e)
	{
		std::cerr << e._msg << " in file " << e._filename << " at line " << e._line << std::endl;
		tokens.clear();
		delete obj;
		fs.close();
		throw e;
	}
	catch(std::exception &e)
	{
		tokens.clear();
		delete obj;
		fs.close();
		std::cerr << e.what() << std::endl;
		throw e;
	}
	return obj;
};
