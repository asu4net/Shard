#include "shpch.h"
#include "TypeManager.h"
#include "Type.h"

namespace Shard
{
    Type* TypeManager::m_firstType = nullptr;

    void TypeManager::PrintTypes()
    {
        const Type* currentType = m_firstType;
        while (currentType)
        {
            printf("%s\n", currentType->GetName().c_str());
            currentType = currentType->GetNextType();
        }
    }

    const Type* TypeManager::GetType(std::string name)
    {
        const Type* currentType = m_firstType;

        while (currentType)
        {
            if (currentType->GetName().compare(name) == 0)
                return currentType;

            currentType = currentType->GetNextType();
        }
        return nullptr;
    }
}