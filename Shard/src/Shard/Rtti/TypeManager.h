#pragma once
#include <string>

namespace Shard
{
    class Type;

    class TypeManager
    {
    private:
        static Type* m_firstType;

    public:
        static void PrintTypes();
        static const Type* GetType(std::string name);

        friend class Type;
    };
}