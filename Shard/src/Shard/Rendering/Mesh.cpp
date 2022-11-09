#include "shpch.h"
#include "Mesh.h"

namespace Shard::Rendering
{
	Mesh::Mesh(unsigned int mode, bool uvLayout, float* vertices, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount)
    {
		m_vertexArray = std::make_shared<VertexArray>();
		m_vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices[0]) * verticesCount);
		VertexBufferLayout layout;

		if (mode < MESH_2D || mode > MESH_3D)
			mode = MESH_3D;

		layout.Push<float>(mode);
		if (uvLayout)
			layout.Push<float>(m_uvOffset);

		m_vertexArray->AddLayout(m_vertexBuffer, layout);

		m_indexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices[0]) * indicesCount);

		m_indexBuffer->Unbind();
		m_vertexBuffer->Unbind();
    }
}