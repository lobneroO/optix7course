#pragma once

#include "glfWindow/GLFWindow.h"
#include <GL/gl.h>

#include "gdt/math/vec.h"

#include "../Renderer.h"

using namespace osc;

struct Window// : public GLFWindow
{
public:
	Window(const std::string& windowTitle, const uint32_t& width = 1024, const uint32_t& height = 768);

	~Window();

	virtual void Render();

	virtual void Draw();

	virtual void Resize(const vec2i& size);

	/**
	* Starts (and maintains) the render loop
	*/
	virtual void Run();

protected:

	// glfw setup
	GLFWwindow* glfwWindow = nullptr;

	Renderer OptixRenderer;

	vec2i FramebufferSize;
	GLuint FramebufferTexture{ 0 };
	Renderer OptixRenderer;
	std::vector<uint32_t> Pixels;
};