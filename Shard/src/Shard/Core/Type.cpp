#include "Type.h"
#include "TypeManager.h"

namespace Shard
{
    Type::Type(std::string name, Object* (*createObjectFunc)())
        : m_Name(name)
        , m_CreateObjectFunc(createObjectFunc)
        , m_NextType(nullptr)
    {
        if (TypeManager::m_FirstType)
        {
            m_NextType = TypeManager::m_FirstType;
        }

        TypeManager::m_FirstType = this;
    }
}