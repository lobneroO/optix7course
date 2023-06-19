
#include <stdexcept>
#include <iostream>
#include <string>

#include "cuda_runtime.h"

#include "util/Window.h"
#include "util/Mesh.h"


using namespace gdt;


int main(int ac, char **av)
{
	try
	{
		Window window("OptiX window", 1920, 1080);

		Mesh mesh;
		mesh.AddCube(vec3f(0.f, -1.5f, 0.f), vec3f(10.f, .1f, 10.f));
		mesh.AddCube(vec3f(0.f, 0.f, 0.f), vec3f(2.f, 2.f, 2.f));
		mesh.Color = vec3f(.2f, .9f, .05f);

		window.GetRenderer()->AddMesh(mesh);

		window.GetRenderer()->SetCameraPositionAndOrientation(
			vec3f(-10.f, 2.f, -12.f),	//eye
			vec3f(0.f, 0.f, 0.f),		//at
			vec3f(0.f, 1.f, 0.f)		//up
		);

		window.GetRenderer()->Init();

		window.Run();
	}
	catch (std::runtime_error& e)
	{
		std::cerr << "Runtime error!" << std::endl;
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}