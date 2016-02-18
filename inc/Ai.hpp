/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ai.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:36:04 by jquilez           #+#    #+#             */
//   Updated: 2015/03/23 19:05:48 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_HPP
# define AI_HPP

# define FOUND		0
# define NOT_FOUND	-1
# define MINI 		1000000

# include "Puzzle.hpp"
# include <deque>
# include <unordered_set>
# include <boost/functional/hash.hpp>

class							Ai {

	public:

		Ai(int const & heuristic);
		Ai(Ai const & src);
		~Ai(void);

		Ai &					operator=(Ai const & rhs);

		bool					isSolvable(Puzzle *puzzle);
		void					genSolvable(Puzzle *puzzle);
		void					genVerticalDown(int const & x, int const & y, int const & size, Puzzle *puzzle);
		void					genHorizontalRight(int const & x, int const & y, int const & size, Puzzle *puzzle);
		void					genVerticalTop(int const & x, int const & y, int const & size, Puzzle *puzzle);
		void					genHorizontalLeft(int const & x, int const & y, int const & size, Puzzle *puzzle);
		int						solve(Puzzle *puzzle);
		int						search(Puzzle *puzzle, int g, int limit);

		static int				opened;

	private:

		Ai(void);

		int						heuristic(Puzzle *puzzle);
		int						manhattanDistance(Puzzle *puzzle);
		int						misplaced(Puzzle *puzzle);
		int						tilesOut(Puzzle *puzzle);

		std::deque<Puzzle *>	getStates(Puzzle *puzzle);
		void					sortStates(std::deque<Puzzle *> & states);
		void					cleanup(std::deque<Puzzle *> & children);

		int						_heuristic;
		int						_steps;
		std::unordered_set<std::size_t>		_opened;
		std::deque<std::string>				_result;
		std::deque<int>						_solvable;

};

#endif
