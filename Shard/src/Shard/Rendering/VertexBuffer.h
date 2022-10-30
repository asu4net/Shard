#pragma once
#include "GLEW/glew.h"

namespace Shard::Rendering
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_rendererID = 0;
	};
}
