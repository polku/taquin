/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 09:59:35 by jquilez           #+#    #+#             */
/*   Updated: 2015/03/23 13:23:44 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"
#include "Parser.hpp"
#include "Generator.hpp"
#include "Ai.hpp"

int				main(int ac, char **av)
{
	srand(time(NULL));

	if (ac == 4 && (std::strcmp(av[1], "-f") == 0 || std::strcmp(av[1], "-g") == 0) &&
		std::atoi(av[3]) >= 1 && std::atoi(av[3]) <= 4)
	{
		try
		{
			Puzzle		*puzzle;
			if (std::strcmp(av[1], "-f") == 0)
			{
				Parser parse(av[2]);
				puzzle = parse.createPuzzle();
			}
			else
			{
				Generator gen(std::atoi(av[2]));
				puzzle = gen.createPuzzle();
			}

			Ai res(std::atoi(av[3]));
			std::cout << "Initial state : " << std::endl;
			puzzle->show();
			std::cout << "-----------------------" << std::endl;
			res.solve(puzzle);
			delete puzzle;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}

	} else {

		std::cout << "\033[31mUsage: ./npuzzle [-f input_files | -g size_puzzle] heuristic\033[0m" << std::endl;
		std::cout << "\033[36mheuristic: 1 Manhattan-distance 2 Misplaced 3 TilesOut 4 All\033[0m" << std::endl;
	}

	return 1;
}
