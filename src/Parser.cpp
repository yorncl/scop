#include "Parser.hpp"
#include "Vec3.hpp"
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

	ParsingError(std::string msg) :
		_msg(msg)
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

static inline void parse_vertex(std::vector<std::string>& tokens, Object* obj)
{
	if (tokens.size() != 4)
		throw ParsingError("Vertex malformed");
	try 
	{
		Vec3<float> v;
		v.x = std::stof(tokens[1]);
		v.y = std::stof(tokens[2]);
		v.z = std::stof(tokens[3]);
		obj->data.vertices.push_back(v);
	}
	catch(std::invalid_argument &e)
	{
		throw ParsingError("Vertex coordinates malformed");
	}
	catch(std::out_of_range &e)
	{
		throw ParsingError("Vertex coordinates out of range");
	}
}
static inline void parse_face(std::vector<std::string>& tokens, Object* obj)
{
	if (tokens.size() < 4)
		throw ParsingError("Needs at least 3 vertices index");
	try
	{
		obj->data.indices.push_back(std::stoi(tokens[1]) - 1);
		obj->data.indices.push_back(std::stoi(tokens[2]) - 1);
		obj->data.indices.push_back(std::stoi(tokens[3]) - 1);
		// This is abysmally ugly
		// I don't want to implement a complete, complexe .obj parser
		// So you'll have to handle this herrendous hardcoded square triangulation
		// the -1 is because vertices indices start at 1 in .obj, not in OpengGL if I remember correctly
		if (tokens.size() > 4)
		{
			obj->data.indices.push_back(std::stoi(tokens[1]) - 1);
			obj->data.indices.push_back(std::stoi(tokens[3]) - 1);
			obj->data.indices.push_back(std::stoi(tokens[4]) - 1);
		}
	}
	catch(std::invalid_argument &e)
	{
		throw ParsingError("Indices malformed");
	}
	catch(std::out_of_range &e)
	{
		throw ParsingError("Indices out of range");
	}
}

static inline void parse_name(std::vector<std::string>& tokens, Object* obj)
{
	if (obj->name.length() > 0)
		throw ParsingError("Name already defined above");
	// if the name isn't defined
	if (tokens.size() != 2)
		throw ParsingError("Object name malformed");
	obj->name = tokens[1];
}

Object* Parser::read_obj(char* filename)
{
	std::ifstream fs;
	Object* obj;
	std::string line;
	std::vector<std::string> tokens;
	size_t linenumber = 0;
	try
	{
		obj = new Object();
		fs.open(filename);
		if (!fs.is_open())
			throw std::runtime_error("Could not open file: " + std::string(filename));
		while (std::getline(fs, line))
		{
			linenumber++;
			if (line.length() == 0)
				continue;
			//split the line
			split(line, tokens);
			// Object name
			if (tokens[0] == "o")
				parse_name(tokens, obj);
			// vertex coordinates
			else if (tokens[0] == "v")
				parse_vertex(tokens, obj);
			// Polygonal face element
			else if (tokens[0] == "f")
				parse_face(tokens, obj);
			tokens.clear();
		}
		// Converting all negative vertices to positive
		// for example, an index of -1 refers to the last vertex
		// TODO optimize, can get kind of slow for large 
		size_t sizev = obj->data.vertices.size();
		size_t sizei = obj->data.indices.size(); 
		if (sizev == 0 || sizei == 0)
			throw std::runtime_error("Object appears to be malformed");
		for (size_t i = 0; i < sizei; i++)
			if (obj->data.indices[i] < 0)
				obj->data.indices[i] = sizev + obj->data.indices[i];
		if (obj->name == "")
			obj->name = "No name :(";
		fs.close();
	}
	catch (ParsingError &e)
	{
		std::cerr << e._msg << " in file " << filename << " at line " << line << std::endl;
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

