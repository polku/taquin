/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACreate.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:36:04 by jquilez           #+#    #+#             */
//   Updated: 2015/03/20 17:57:45 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ACREATE_HPP
# define ACREATE_HPP

# include "Puzzle.hpp"

class							ACreate {

	public:

		ACreate(ACreate const & src);
		~ACreate(void);

		ACreate &				operator=(ACreate const & rhs);

		virtual Puzzle			*createPuzzle(void) = 0;

	protected:

		ACreate(void);
		ACreate(int const & size);

		int						_size;

};

#endif
