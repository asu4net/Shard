#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Shard::Rendering
{
	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void AddLayout(const std::shared_ptr<VertexBuffer> vb, const VertexBufferLayout& layout);
	
	private:

		unsigned int m_rendererID = 0;
	};
}
