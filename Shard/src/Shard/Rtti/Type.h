#pragma once
#include <string>
#include <iostream>

namespace Shard
{
    class Object;

    class Type
    {
    private:
        std::string m_name;
        Type* m_nextType = nullptr;
        const Type* m_parentType;
        Object* (*m_createObjectFunc)();

    public:
        Type(const std::string& name, const Type* parentType, Object* (*createObjectFunc)());

        const Type* GetNextType() const { return m_nextType; }
        const std::string GetName() const { return m_name; }
        Object* CreateObject() const { m_createObjectFunc(); }

        bool IsChildOf(const Type* type) const;
        bool operator==(const Type* type) const { return this == type; }

        template<typename T>
        T* Cast()
        {
            if (!IsChildOf(T::GetType())) return nullptr;
            return static_cast<T*>(this);
        }
    };
}
