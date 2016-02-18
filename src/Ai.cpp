/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ai.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:35:12 by jquilez           #+#    #+#             */
/*   Updated: 2015/03/24 16:22:49 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ai.hpp"

Ai::Ai(void) : _steps(0) {

}

Ai::Ai(int const & heuristic) : _heuristic(heuristic), _steps(0) {

}

Ai::Ai(Ai const & src) {

	*this = src;
}

Ai::~Ai(void) {

}

Ai &				Ai::operator=(Ai const & rhs) {

	if (this != &rhs) {

		this->_heuristic = rhs._heuristic;
		this->_steps = rhs._steps;
		this->_opened = rhs._opened;
		this->_result = rhs._result;
	}

	return *this;
}

bool				Ai::isSolvable(Puzzle *puzzle)
{
	int				i = 1;
	int				inversion = 0;

	this->genSolvable(puzzle);
	for (auto it = this->_solvable.begin(); it + 1 != this->_solvable.end(); ++it) {

		for (auto it2 = this->_solvable.begin() + i; it2 != this->_solvable.end(); ++it2) {

			if (*it != 0 && *it2 != 0 && *it > *it2)
				inversion++;
		}
		i++;
	}
	if (puzzle->getSize() % 2 == 1)
	{
		if (inversion % 2 == 0)
			return true;
		else
			return false;
	}
	else
	{
		int blank_row = puzzle->getEmpty().second;
		std::cout << inversion << " " << blank_row << std::endl;
	//	if (inversion % 2 == 0)
	//		return true;
		 if (inversion % 2 == 0 && blank_row % 2 == 0)
		 	return true;
		 if (inversion % 2 == 1 && blank_row % 2 == 1)
		 	return true;
	}
	return false;
}

void					Ai::genSolvable(Puzzle *puzzle) {

	int		i = 0;
	int		count = 0;
	int		size = puzzle->getSize();

	for (int len = size; len > 0; --len) {

		if (len == size) {

			this->genHorizontalRight(i, i, size, puzzle);
			i++;
		} else if (count % 2 != 0) {

			this->genVerticalTop(i - 1, size - (i + 1), len, puzzle);

			this->genHorizontalRight(i, i, len, puzzle);

			count++;
		} else if (count % 2 == 0) {

			if (count > 0)
				i++;

			this->genVerticalDown(size - i, i, len, puzzle);

			this->genHorizontalLeft(size - (i + 1), size - i, len, puzzle);

			count++;
		}
	}
}

void					Ai::genVerticalDown(int const & x, int const & y, int const & size, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i)
			this->_solvable.push_back(puzzle->getCase(x, y + i));
}

void					Ai::genHorizontalRight(int const & x, int const & y, int const & size, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i)
			this->_solvable.push_back(puzzle->getCase(x + i, y));
}

void					Ai::genVerticalTop(int const & x, int const & y, int const & size, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i)
			this->_solvable.push_back(puzzle->getCase(x, y - i));
}

void					Ai::genHorizontalLeft(int const & x, int const & y, int const & size, Puzzle *puzzle) {

	for (int i = 0; i < size; ++i)
			this->_solvable.push_back(puzzle->getCase(x - i, y));
}


int					Ai::solve(Puzzle *puzzle)
{
	int			limit;
	int			cost;

	limit = this->heuristic(puzzle);

	if (!this->isSolvable(puzzle)) {

			std::cout << "This puzzle in unsolvable " << std::endl;
			return -1;
	}
	while (true)
	{
		cost = this->search(puzzle, 0, limit);
		if (cost == FOUND)
		{
			std::cout << "Number of steps : " << this->_steps << std::endl;
			break ;
		}
		if (cost == MINI)
		{
			std::cout << "This puzzle in unsolvable2 " << std::endl;
			break ;
		}
		limit = cost;
		this->_opened.clear();
//		std::cerr << "debug : cost = " << cost << std::endl;
	}

	std::cout << "Opened : " << Ai::opened << std::endl;
	std::cout << "Max in memory : " << Puzzle::max_memory << std::endl;

	// for (size_t i = 0; i < this->_result.size(); ++i) {

	// 	std::cout << std::endl << "\033[32mStep " << i << " :\033[0m" << std::endl;
	// 	std::cout << this->_result[i];
	// }
	// this->_result.clear();

	return cost;
}

int					Ai::heuristic(Puzzle *puzzle) {

	int				total = 0;

	switch (this->_heuristic) {

		case 1:
			return this->manhattanDistance(puzzle);

		case 2:
			return this->misplaced(puzzle);

		case 3:
			return this->tilesOut(puzzle);

		case 4:
			total += this->manhattanDistance(puzzle);
			total += this->misplaced(puzzle);
			total += this->tilesOut(puzzle);
			return total;
	}
	return total;
}

int					Ai::search(Puzzle *puzzle, int g, int limit)
{
	int						cost;
	int						h;
	int						min;
	std::deque<Puzzle *>	children;

	h = this->heuristic(puzzle);
	cost = g + h;
	if (cost > limit)
		return cost;
	if (h == 0)
	{
		this->_result.push_front(puzzle->to_string());
		return FOUND;
	}
	min = MINI;
	children = this->getStates(puzzle);
	for (size_t i = 0 ; i < children.size() ; i++)
	{
		cost = this->search(children[i], g + 1, limit);
		if (cost == FOUND)
		{
			if (this->_steps == 0)
				this->_steps = g + 1;
			this->cleanup(children);
			this->_result.push_front(puzzle->to_string());
			Ai::opened = this->_opened.size();
			return FOUND;
		}
		if (cost < min)
			min = cost;
	}
	this->cleanup(children);
	return min;
}

void				Ai::cleanup(std::deque<Puzzle *> & children)
{
	for (unsigned long i = 0 ; i < children.size() ; i++)
		delete children[i];
	children.clear();
}

int					Ai::manhattanDistance(Puzzle *puzzle) {

	int						size = puzzle->getSize();
	std::pair<int, int>		current;
	int						total = 0;

	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			if (puzzle->getCase(x, y) == 0)
				continue;
			current = puzzle->getMapping(puzzle->getCase(x, y));
			total += abs(x - current.first);
			total += abs(y - current.second);
		}
	}

	return total;
}

int					Ai::misplaced(Puzzle *puzzle)
{
	int				size = puzzle->getSize();
	int				total = 0;
	Puzzle::t_coord	c;

	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			c = puzzle->getMapping(puzzle->getCase(x, y));
			if (x != c.first || y != c.second)
				total += 1;
		}
	}

	return total;
}

int					Ai::tilesOut(Puzzle *puzzle)
{
	int				size = puzzle->getSize();
	int				total = 0;
	Puzzle::t_coord	c;

	for (int x = 0; x < size; ++x)
	{
		for (int y = 0; y < size; ++y)
		{
			c = puzzle->getMapping(puzzle->getCase(x, y));
			if (x != c.first)
				total += 1;
			if (y != c.second)
				total += 1;
		}
	}

	return total;
}

std::deque<Puzzle *>	Ai::getStates(Puzzle *puzzle)
{
	std::deque<Puzzle *>	states;
	Puzzle					*tmp;
	int		x = puzzle->getEmpty().first;
	int		y = puzzle->getEmpty().second;
	int		size = puzzle->getSize();
	int		last_move = puzzle->getLastMove();
	boost::hash<std::vector<std::vector<int>>> hash;
	std::size_t h;

	h = hash(puzzle->getCases());
	this->_opened.insert(h);

	if (x + 1 < size && last_move != MOVE_LEFT)
	{
		tmp = new Puzzle(*puzzle);
		tmp->moveRight();
		h = hash(tmp->getCases());
		if (this->_opened.insert(h).second)
			states.push_back(tmp);
		else
			delete tmp;
	}

	if (x > 0 && last_move != MOVE_RIGHT)
	{
		tmp = new Puzzle(*puzzle);
		tmp->moveLeft();
		h = hash(tmp->getCases());
		if (this->_opened.insert(h).second)
			states.push_back(tmp);
		else
			delete tmp;
	}

	if (y > 0 && last_move != MOVE_DOWN)
	{
		tmp = new Puzzle(*puzzle);
		tmp->moveTop();
		h = hash(tmp->getCases());
		if (this->_opened.insert(h).second)
			states.push_back(tmp);
		else
			delete tmp;
	}

	if (y < size - 1 && last_move != MOVE_TOP)
	{
		tmp = new Puzzle(*puzzle);
		tmp->moveDown();
		h = hash(tmp->getCases());
		if (this->_opened.insert(h).second)
			states.push_back(tmp);
		else
			delete tmp;
	}

	this->sortStates(states);

	return states;
}

void				Ai::sortStates(std::deque<Puzzle *> & states)
{
	int				unsort = 1;
	int				size = states.size();
	Puzzle			*tmp;

	while (unsort)
	{
		unsort = 0;
		for (int i = 0; i < size - 1; ++i)
		{
			if (this->heuristic(states[i]) > this->heuristic(states[i + 1]))
			{
				unsort = 1;
				tmp = states[i];
				states[i] = states[i + 1];
				states[i + 1] = tmp;
			}
		}
	}
}

int		Ai::opened = 0;
