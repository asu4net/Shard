#pragma once
#include "Entity.h"

namespace Shard::Ecs
{
    struct Tag
    {
        std::string tag;

        Tag() = default;
        Tag(const Tag&) = default;
        Tag(std::string tag) : tag(std::move(tag)) {}
    };
    
    struct Transform
    {
        Math::Vector3 position;
        glm::quat rotation;
        Math::Vector3 scale;
        
        Entity parent;
        
        Transform()
            : position(Math::Vector3::zero)
            , rotation(IdentityQuat)
            , scale(Math::Vector3::zero)
        {}
        
        Transform(const Transform&) = default;
    };

    struct Camera
    {
        
    };
}