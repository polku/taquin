/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:03:42 by jquilez           #+#    #+#             */
//   Updated: 2015/03/21 10:18:46 by jmaurice         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "ACreate.hpp"
# include <iostream>
# include <fstream>
# include <deque>
# include <boost/algorithm/string.hpp>
# include <boost/lexical_cast.hpp>

class							Parser : public ACreate {

	public:

		Parser(std::string const & path);
		Parser(Parser const & src);
		~Parser(void);

		Parser &				operator=(Parser const & rhs);

		Puzzle					*createPuzzle(void);

		class					FileException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		class					ParseException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

		class					ValidException : public std::exception
		{
			public:
				virtual const char *		what() const throw();
		};

	private:

		Parser(void);

		std::string				_path;
		std::deque<std::string>	_content;

};

#endif
