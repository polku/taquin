/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:05:03 by jquilez           #+#    #+#             */
//   Updated: 2015/03/21 18:55:24 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : ACreate() {

}

Parser::Parser(std::string const & path) : ACreate(), _path(path) {

	std::ifstream				file(this->_path);
	std::string					line;
	std::vector<std::string> 	substrs;
	bool						first = true;

	if (!file.is_open())
		throw FileException();

	while (!file.eof())
	{
		std::getline(file, line);
		if (first && line == "")
			throw ParseException();
		else
			first = false;
		boost::split( substrs, line, boost::is_any_of("#") );
		boost::split( substrs, substrs[0], boost::is_any_of(" ") );
		for (unsigned long j = 0 ; j < substrs.size() ; j++)
		{
			if (substrs[j] != "")
				this->_content.push_back( substrs[j] );
		}
	}
	this->_size = boost::lexical_cast<int>(this->_content[0]);
	this->_content.pop_front();
	if ( this->_content.size() != pow(this->_size, 2) )
		throw ParseException();

	file.close();
}

Parser::Parser(Parser const & src) : ACreate(src) {

}

Parser::~Parser(void) {

	this->_content.clear();
}

Parser &				Parser::operator=(Parser const & rhs) {

	if (this != &rhs) {

		this->_path = rhs._path;
		this->_content = rhs._content;
	}

	ACreate::operator=(rhs);

	return *this;
}

Puzzle					*Parser::createPuzzle(void)
{
	int							tmp;
	Puzzle						*result = new Puzzle(this->_size);

	for (int x = 0 ; x < this->_size ; x++)
	{
		for (int y = 0 ; y < this->_size ; y++)
		{
			tmp = boost::lexical_cast<int>(this->_content[ y * this->_size + x]);
			if (tmp == 0)
				result->setEmpty(x, y);
			result->setCase(x, y, tmp);
		}
	}
	if (!result->checkValid())
		throw ValidException();
	result->genSolution();
	return result;
}

const char *			Parser::FileException::what() const throw()
{
	return "File not found";
}

const char *			Parser::ParseException::what() const throw()
{
	return "Parse error in file";
}

const char *			Parser::ValidException::what() const throw() {

	return "Invalid puzzle";
}
