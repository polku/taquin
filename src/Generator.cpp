/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:40:37 by jquilez           #+#    #+#             */
//   Updated: 2015/03/22 13:14:03 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Generator.hpp"

Generator::Generator(void) : ACreate() {

}

Generator::Generator(int const & size) : ACreate(size) {

}

Generator::Generator(Generator const & src) : ACreate(src) {

}

Generator::~Generator(void) {

}

Generator &				Generator::operator=(Generator const & rhs) {

	ACreate::operator=(rhs);

	return *this;
}

Puzzle					*Generator::createPuzzle(void) {

	Puzzle				*puzzle = new Puzzle(this->_size);

	this->init(puzzle);
	this->blend(puzzle);
	puzzle->genSolution();
	puzzle->setLastMove(0);
	return puzzle;
}

void					Generator::init(Puzzle *puzzle) {

	int		val = 1;
	int		i = 0;
	int		count = 0;

	for (int len = this->_size; len > 0; --len) {

		if (len == this->_size) {

			this->fillHorizontalRight(i, i, this->_size, val, puzzle);
			val = this->_size;
			i++;
		} else if (count % 2 != 0) {

			this->fillVerticalTop(i - 1, this->_size - (i + 1), len, val + 1, puzzle);
			val += len;

			this->fillHorizontalRight(i, i, len, val + 1, puzzle);
			val += len;

			count++;
		} else if (count % 2 == 0) {

			if (count > 0)
				i++;

			this->fillVerticalDown(this->_size - i, i, len, val + 1, puzzle);
			val += len;

			this->fillHorizontalLeft(this->_size - (i + 1), this->_size - i, len, val + 1, puzzle);
			val += len;

			count++;
		}
	}
}

void					Generator::blend(Puzzle *puzzle) {

	int		i = 0;
	int		random = 0;

	while (i < ITERATION) {

		random = (rand() % 4) + 1;
		if (random == puzzle->getLastMove())
			continue;

		switch (random) {

			case 1:
				puzzle->moveTop();
				break;

			case 2:
				puzzle->moveDown();
				break;

			case 3:
				puzzle->moveLeft();
				break;

			case 4:
				puzzle->moveRight();
				break;
		}
		i++;
	}
}

void					Generator::fillVerticalDown(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size) {

			puzzle->setCase(x, y + i, 0);
			puzzle->setEmpty(x, y + i);
		}
		else
			puzzle->setCase(x, y + i, val + i);
	}
}

void					Generator::fillHorizontalRight(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size) {

			puzzle->setCase(x + i, y, 0);
			puzzle->setEmpty(x + i, y);
		}
		else
			puzzle->setCase(x + i, y, val + i);
	}
}

void					Generator::fillVerticalTop(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size) {

			puzzle->setCase(x, y - i, 0);
			puzzle->setEmpty(x, y - i);
		}
		else
			puzzle->setCase(x, y - i, val + i);
	}
}

void					Generator::fillHorizontalLeft(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i) {

		if (val + i == this->_size * this->_size) {

			puzzle->setCase(x, y - i, 0);
			puzzle->setEmpty(x, y - i);
		}
		else
			puzzle->setCase(x - i, y, val + i);
	}
}
