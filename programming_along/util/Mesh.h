#pragma once

#include <vector>

#include <gdt/math/vec.h>
#include <gdt/math/AffineSpace.h>

using namespace gdt;

struct Mesh
{
	void AddUnitCube(const affine3f& transfomrationMatrix);

	void AddCube(const vec3f& center, const vec3f& size);

	void AddTriangle(const vec3f vertices[3], const vec3i indices);

	std::vector<vec3f> Vertices;
	std::vector<vec3i> Indices;
};