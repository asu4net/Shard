#pragma once

namespace Shard
{
    class Type;

    class TypeManager
    {
    private:
        static Type* m_FirstType;

    public:
        static void PrintTypes();
        static const Type* GetType(std::string name);

        friend class Type;
    };
}
