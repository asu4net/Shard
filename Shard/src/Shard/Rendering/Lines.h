#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Shard::Rendering
{
    struct Line
    {
        Math::Vector3 start;
        Math::Vector3 end;
    };

    class Lines
    {
    public:
        Lines() = default;
        Lines(const std::vector<Line>& lines);

        inline int GetPointsCount() const { return m_pointsCount; }

    private:
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<VertexBuffer> m_vertexBuffer;

        int m_pointsCount = 0;

        friend class Renderer;
    };
}


