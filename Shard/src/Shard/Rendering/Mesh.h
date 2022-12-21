#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define MESH_3D 3
#define MESH_2D 2

namespace Shard
{
	class Mesh
	{

	public:
		Mesh() = default;
		Mesh(unsigned int mode, bool uvLayout, float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);

		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
	
		const unsigned int m_uvOffset = 2;
	};
}
