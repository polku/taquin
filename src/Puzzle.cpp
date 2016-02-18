/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:40:37 by jquilez           #+#    #+#             */
//   Updated: 2015/03/23 18:24:30 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

Puzzle::Puzzle(void) {

	Puzzle::in_memory += 1;
	if (Puzzle::in_memory > Puzzle::max_memory)
		Puzzle::max_memory = Puzzle::in_memory;
}

Puzzle::Puzzle(int const & size) : _size(size), _lastMove(0) {

	if (this->_size < MIN_SIZE || this->_size > MAX_SIZE)
		throw SizeException();

	this->_cases = std::vector<std::vector<int>>(this->_size, std::vector<int>(this->_size));
	this->_mapping = std::vector<std::pair<int, int>>(this->_size * this->_size);

	Puzzle::in_memory += 1;
	if (Puzzle::in_memory > Puzzle::max_memory)
		Puzzle::max_memory = Puzzle::in_memory;
}

Puzzle::Puzzle(Puzzle const & src) {

	this->_size = src._size;
	this->_cases = src._cases;
	this->_empty = src._empty;
	this->_mapping = src._mapping;

	Puzzle::in_memory += 1;
	if (Puzzle::in_memory > Puzzle::max_memory)
		Puzzle::max_memory = Puzzle::in_memory;
}

Puzzle::~Puzzle(void) {

	Puzzle::in_memory -= 1;
}

Puzzle &				Puzzle::operator=(Puzzle const & rhs) {

	if (this != &rhs) {

		this->_size = rhs._size;
		this->_cases = rhs._cases;
		this->_empty = rhs._empty;
		this->_mapping = rhs._mapping;
	}

	return *this;
}

void					Puzzle::show(void) const {

	std::cout << std::endl;
	for (int y = 0; y < this->_size; ++y) {

		for (int x = 0; x < this->_size; ++x) {

			if (this->_cases[x][y] != 0)
				std::cout << "\033[36m" << this->_cases[x][y] << "\033[0m	";
			else
				std::cout << "\033[36m \033[0m	";
		}
		std::cout << std::endl << std::endl;
	}

}

std::string const		Puzzle::to_string(void) const {

	std::string			str;

	str.append("\n");
	for (int y = 0; y < this->_size; ++y) {

		for (int x = 0; x < this->_size; ++x) {

			if (this->_cases[x][y] != 0) {

				str.append("\033[36m");
				str.append(std::to_string(this->_cases[x][y]));
				str.append("\033[0m	");
			}
			else
				str.append("\033[36m \033[0m	");
		}
		str.append("\n\n");
	}
	return str;
}

void					Puzzle::moveTop(void) {

	int					x = this->getEmpty().first;
	int					y = this->getEmpty().second;

	if (y > 0) {

		this->setCase(x, y, this->_cases[x][y - 1]);
		this->setCase(x, y - 1, 0);
		this->setEmpty(x, y - 1);
		this->_lastMove = MOVE_TOP;
	}
}

void					Puzzle::moveDown(void) {

	int					x = this->getEmpty().first;
	int					y = this->getEmpty().second;

	if (y + 1 < this->_size) {

		this->setCase(x, y, this->_cases[x][y + 1]);
		this->setCase(x, y + 1, 0);
		this->setEmpty(x, y + 1);
		this->_lastMove = MOVE_DOWN;
	}
}

void					Puzzle::moveLeft(void) {

	int					x = this->getEmpty().first;
	int					y = this->getEmpty().second;

	if (x > 0) {

		this->setCase(x, y, this->_cases[x - 1][y]);
		this->setCase(x - 1, y, 0);
		this->setEmpty(x - 1, y);
		this->_lastMove = MOVE_LEFT;
	}
}

void					Puzzle::moveRight(void) {

	int					x = this->getEmpty().first;
	int					y = this->getEmpty().second;

	if (x + 1 < this->_size) {

		this->setCase(x, y, this->_cases[x + 1][y]);
		this->setCase(x + 1, y, 0);
		this->setEmpty(x + 1, y);
		this->_lastMove = MOVE_RIGHT;
	}
}

bool				Puzzle::checkValid(void)
{
	int						sz = pow(this->_size,2);
	std::vector<bool>		check(sz, false);

	for (int x = 0 ; x < this->_size ; x++)
	{
		for (int y = 0 ; y < this->_size ; y++)
		{
			if (this->_cases[x][y] < 0 || this->_cases[x][y] > pow(this->_size, 2) - 1
				|| check[this->_cases[x][y]] == true)
				return false;
			check[this->_cases[x][y]] = true;
		}
	}
	return true;
}

void					Puzzle::genSolution(void) {

	int		val = 1;
	int		i = 0;
	int		count = 0;

	for (int len = this->_size; len > 0; --len) {

		if (len == this->_size) {

			this->genHorizontalRight(i, i, this->_size, val);
			val = this->_size;
			i++;
		} else if (count % 2 != 0) {

			this->genVerticalTop(i - 1, this->_size - (i + 1), len, val + 1);
			val += len;

			this->genHorizontalRight(i, i, len, val + 1);
			val += len;

			count++;
		} else if (count % 2 == 0) {

			if (count > 0)
				i++;

			this->genVerticalDown(this->_size - i, i, len, val + 1);
			val += len;

			this->genHorizontalLeft(this->_size - (i + 1), this->_size - i, len, val + 1);
			val += len;

			count++;
		}
	}
}

void					Puzzle::genVerticalDown(int const & x, int const & y, int const & size, int const & val) {

	for (int i = 0; i < size; ++i)	{

		if (val + i == this->_size * this->_size)
			this->setMapping(0, std::make_pair(x, y + i));
		else
			this->setMapping(val + i, std::make_pair(x, y + i));
	}
}

void					Puzzle::genHorizontalRight(int const & x, int const & y, int const & size, int const & val) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size)
			this->setMapping(0, std::make_pair(x + i, y));
		else
			this->setMapping(val + i, std::make_pair(x + i, y));
	}
}

void					Puzzle::genVerticalTop(int const & x, int const & y, int const & size, int const & val) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size)
			this->setMapping(0, std::make_pair(x, y - i));
		else
			this->setMapping(val + i, std::make_pair(x, y - i));
	}
}

void					Puzzle::genHorizontalLeft(int const & x, int const & y, int const & size, int const & val) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size)
			this->setMapping(0, std::make_pair(x, y - i));
		else
			this->setMapping(val + i, std::make_pair(x - i, y));
	}
}

void					Puzzle::displayMapping(void)
{
	for (int i = 0 ; i < pow( this->_size, 2) ; i++)
	{
		std::cout << i << " : " << this->_mapping[i].first << ", " << this->_mapping[i].second << std::endl;
	}
}

void					Puzzle::setCase(int const & x, int const & y, int const & content) {

	this->_cases[x][y] = content;
}

void					Puzzle::setEmpty(int const & x, int const & y) {

	this->_empty.first = x;
	this->_empty.second = y;
}

int const &				Puzzle::getLastMove(void) const {

	return this->_lastMove;
}

int const &				Puzzle::getCase(int const & x, int const & y) {

	return this->_cases[x][y];
}

int const &				Puzzle::getSize(void) const {

	return this->_size;
}

void					Puzzle::setMapping(int const & index, std::pair<int, int> const & pos) {

	this->_mapping[index] = pos;
}

std::pair<int, int> const &		Puzzle::getMapping(int const & index) const {

	return this->_mapping[index];
}

std::pair<int, int> const &		Puzzle::getEmpty(void) const {

	return this->_empty;
}

void					Puzzle::setLastMove(int const & move)
{
	this->_lastMove = move;
}

std::vector<std::vector<int>>	const & 	Puzzle::getCases(void) const
{
	return this->_cases;
}

const char *			Puzzle::SizeException::what() const throw() {

	return "Bad size value";
}

int						Puzzle::in_memory = 0;
int						Puzzle::max_memory = 0;
