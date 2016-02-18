/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACreate.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquilez <jquilez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/20 10:35:12 by jquilez           #+#    #+#             */
/*   Updated: 2015/03/20 16:41:55 by jquilez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACreate.hpp"

ACreate::ACreate(void) {

}

ACreate::ACreate(int const & size) : _size(size) {

}

ACreate::ACreate(ACreate const & src) {

	*this = src;
}

ACreate::~ACreate(void) {

}

ACreate &				ACreate::operator=(ACreate const & rhs)
{
	if (this != &rhs) {

		this->_size = rhs._size;
	}

	return *this;
}
