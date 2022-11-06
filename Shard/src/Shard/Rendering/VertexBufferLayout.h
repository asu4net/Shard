#pragma once
#include <GLEW/glew.h>

namespace Shard::Rendering
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetTypeSize(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};

	class VertexBufferLayout
	{
	private:

		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride = 0;

	public:

		VertexBufferLayout() {}

		template<typename T>
		void Push(unsigned int count) {}

		template<>
		void Push<float>(unsigned int count)
		{
			m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
		}

		const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
		unsigned int GetStride() const { return m_stride; }
	};
}