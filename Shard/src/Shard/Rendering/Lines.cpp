#include "shpch.h"
#include "Lines.h"

namespace Shard::Rendering
{
    Lines::Lines(const std::vector<Line>& lines)
    {
        m_vertexArray = std::make_shared<VertexArray>();

        //Lines to points
        m_pointsCount = lines.size() * 6;
        std::vector<float> pointsVector;
        
        std::function<void(const Line&)> addPoint = [&pointsVector] (const Line& line)
        {
            pointsVector.push_back(line.start.x);
            pointsVector.push_back(line.start.y);
            pointsVector.push_back(line.start.z);

            pointsVector.push_back(line.end.x);
            pointsVector.push_back(line.end.y);
            pointsVector.push_back(line.end.z);
        };

        std::for_each(lines.begin(), lines.end(), addPoint);
        m_vertexBuffer = std::make_shared<VertexBuffer>(&pointsVector[0], sizeof(float) * m_pointsCount);

        //Each point
        VertexBufferLayout pointLayout;
        pointLayout.Push<float>(3);
        m_vertexArray->AddLayout(m_vertexBuffer, pointLayout);
        m_vertexBuffer->Unbind();
    }
}
