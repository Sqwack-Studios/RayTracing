/*===============================================================================/
/ Sqwack Studios, 2022															 /
/===============================================================================*/
//==============================================================================//
// Name				: Renderer.h											 
// Author			: Dani										
// Version			:														     
// Creation time	: 11/10/2022 12:09:57													 
//==============================================================================//

#ifndef _RayTracing_Renderer_H_
#define _RayTracing_Renderer_H_

#pragma once
#include "Walnut/Image.h"
#include <memory>
#include "glm/glm.hpp"
#include "Camera.h"
#include "Ray.h"

class Renderer
{
public:
	Renderer() = default;

	void Render(const Camera& camera);

	void OnResize(uint32_t width, uint32_t height);
	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }

	float* ColorRedChannel() { return &m_Color.r; }
	float* ColorGreenChannel() { return &m_Color.g; }
	float* ColorBlueChannel() { return &m_Color.b; }
	float* LightSourceX() { return &m_lightSource.x; }
	float* LightSourceY() { return &m_lightSource.y; }
	float* LightSourceZ() { return &m_lightSource.z; }


private:
	glm::vec4 TraceRay(const Ray& ray);
private:
	std::shared_ptr<Walnut::Image>				m_FinalImage;
	uint32_t*									m_ImageData{nullptr};
	glm::vec3									m_lightSource{-1.0f, -1.0f, -1.0f};
	glm::vec3									m_Color{1.0f, 0, 1.0f};
protected:


};
#endif // !_RayTracing_Renderer_H_

