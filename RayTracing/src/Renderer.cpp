/*===============================================================================/
/ Sqwack Studios, 2022															 /
/===============================================================================*/
//==============================================================================//
// Name				: Renderer.cpp										
// Author			: Dani										 
// Version			:														     
// Creation time	: 11/10/2022 12:12:09													 
//==============================================================================//

#ifndef _RayTracing_Renderer_CPP_
#define _RayTracing_Renderer_CPP_

#pragma once
#include "Renderer.h"
#include "Walnut/Random.h"



namespace Utils {

	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r{ static_cast<uint8_t>(color.r * 255.0f) };
		uint8_t g{ static_cast<uint8_t>(color.g * 255.0f) };
		uint8_t b{ static_cast<uint8_t>(color.b * 255.0f) };
		uint8_t a{ static_cast<uint8_t>(color.a * 255.0f) };

		uint32_t result = (a << 24) | (b << 16) | (g << 8) | (r) ;

		return result;
	}
}

void Renderer::Render(const Camera& camera)
{
	const glm::vec3& rayOrigin = camera.GetPosition();

	Ray ray;
	ray.Origin = rayOrigin;


	//render every pixel
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); ++y)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); ++x)
		{
			const glm::vec3& rayDirection = camera.GetRayDirections()[x + y * m_FinalImage->GetWidth()];
			ray.Direction = rayDirection;

			glm::vec4 color = TraceRay(ray);
			color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
			
		}

	}
	m_FinalImage->SetData(m_ImageData);
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{

	if (m_FinalImage)
	{
		//Resize not necessary
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}
	
	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];


}

glm::vec4 Renderer::TraceRay(const Ray& ray)
{
	//Ray -> a + b * t
	// a: origin point a(ax,ay)
	// b: direction		b(bx, by)
	// t: distance
	//
	// Circle: (x - x0)^2 + (y - y0)^2 - r^2 = 0
	// x0, y0: offsets
	// r     : radii

	//expand the equation and solve for t
	//(bx^2 + by^2)*t^2 + 2*t(ax * bx + ay * by) + (ax^2 + ay^2 - r^2) = 0

	float radius{ 0.5f };


	//terms of the quadratic formula AT^2 + BT + C = 0
	float A = glm::dot(ray.Direction, ray.Direction);
	float B = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float C = glm::dot(ray.Origin, ray.Origin) - radius * radius;

	//quadratic formula discriminant B^2 - 4A*C
	float discriminant{ B * B - 4.0f * A * C };

	if (discriminant < 0.0f) 
	{
		//early return if the ray missed
		return glm::vec4(0, 0, 0, 1);
	}


	
	//compute "negative" solution 
	float t1 = (- B - glm::sqrt(discriminant)) / (2.0f * A); //- solution

	/*glm::vec3 hitPosition0 = rayOrigin + t0 * rayDirection;*/
	glm::vec3 hitPosition1 = ray.Origin + t1 * ray.Direction;
	glm::vec3 normal = glm::normalize(hitPosition1);
	glm::vec3 lightDirection = glm::normalize(m_lightSource);

	float d =glm::max(glm::dot(normal, -lightDirection), 0.0f); //cos of the angle



	return glm::vec4(m_Color * d, 1.0f);


}

	




#endif // !_RayTracing_Renderer_CPP_

