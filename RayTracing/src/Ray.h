﻿/*===============================================================================/
/ Sqwack Studios, 2022															 /
/===============================================================================*/
//==============================================================================//
// Name				: Ray.h											 
// Author			: Dani										
// Version			:														     
// Creation time	: 11/10/2022 19:04:38													 
//==============================================================================//

#ifndef _RayTracing_Ray_H_
#define _RayTracing_Ray_H_

#pragma once
#include "glm/glm.hpp"
struct Ray
{
	glm::vec3 Origin;
	glm::vec3 Direction;
};
#endif // !_RayTracing_Ray_H_
