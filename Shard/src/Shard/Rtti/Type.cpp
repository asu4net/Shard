#include "shpch.h"
#include "Type.h"
#include "TypeManager.h"

namespace Shard
{
    Type::Type(const std::string& name, const Type* parentType, Object* (*createObjectFunc)())
        : m_name(name)
        , m_parentType(parentType)
        , m_createObjectFunc(createObjectFunc)
    {
        if (TypeManager::m_firstType)
        {
            m_nextType = TypeManager::m_firstType;
        }

        TypeManager::m_firstType = this;
    }

    bool Type::IsChildOf(const Type* type) const
    {
        const Type* parentType = m_parentType;
        while (parentType != nullptr && parentType != type)
        {
            parentType = parentType->m_parentType;
        }
        return parentType != nullptr;
    }
}