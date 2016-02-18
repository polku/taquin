/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:39:53 by jquilez           #+#    #+#             */
/*   Updated: 2015/03/21 16:48:49 by jquilez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_HPP
# define GENERATOR_HPP

# define ITERATION		2000000

# include "ACreate.hpp"

class							Generator : public ACreate {

	public:

		Generator(int const & size);
		Generator(Generator const & src);
		~Generator(void);

		Generator &				operator=(Generator const & rhs);

		Puzzle					*createPuzzle(void);

	private:

		Generator(void);

		void					init(Puzzle *puzzle);
		void					blend(Puzzle *puzzle);
		void					fillVerticalDown(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle);
		void					fillHorizontalRight(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle);
		void					fillVerticalTop(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle);
		void					fillHorizontalLeft(int const & x, int const & y, int const & size, int const & val, Puzzle *puzzle);

};

#endif
