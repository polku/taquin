/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:39:53 by jquilez           #+#    #+#             */
/*   Updated: 2015/03/23 15:16:00 by jquilez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

# define MIN_SIZE	2
# define MAX_SIZE	50
# define MOVE_TOP	1
# define MOVE_DOWN	2
# define MOVE_LEFT	3
# define MOVE_RIGHT	4

# include <stdexcept>
# include <vector>
# include <iostream>
# include <math.h>
# include <utility>

class							Puzzle {

	public:

		typedef					std::pair<int, int> t_coord;

		Puzzle(int const & size);
		Puzzle(Puzzle const & src);
		~Puzzle(void);

		Puzzle &				operator=(Puzzle const & rhs);

		void					genSolution(void);
		bool					checkValid(void);
		void					show(void) const;
		std::string const		to_string(void) const;
		void					moveTop(void);
		void					moveDown(void);
		void					moveLeft(void);
		void					moveRight(void);
		void					setCase(int const & x, int const & y, int const & content);
		void					setEmpty(int const & x, int const & y);
		void					setMapping(int const & index, std::pair<int, int> const & pos);
		void					setLastMove(int const & move);
		int const &				getLastMove(void) const;
		int const &				getCase(int const & x, int const & y);
		int const &				getSize(void) const;
		std::vector<std::vector<int>>	const & 			getCases(void) const;
		void					displayMapping(void);
		std::pair<int, int> const &		getMapping(int const & index) const;
		std::pair<int, int> const &		getEmpty(void) const;

		class					SizeException : public std::exception {

			public:

				virtual const char *		what() const throw();

		};

		static int				in_memory;
		static int				max_memory;

	private:

		Puzzle(void);

		int								_size;
		std::vector<std::vector<int>>	_cases;
		std::pair<int, int>				_empty;
		int								_lastMove;
		std::vector<std::pair<int, int>>	_mapping;

		void		genVerticalDown(int const & x, int const & y, int const & size, int const & val);
		void		genHorizontalRight(int const & x, int const & y, int const & size, int const & val);
		void		genVerticalTop(int const & x, int const & y, int const & size, int const & val);
		void		genHorizontalLeft(int const & x, int const & y, int const & size, int const & val);
};

#endif
