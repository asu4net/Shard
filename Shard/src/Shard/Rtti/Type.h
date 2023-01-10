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
        const Type* m_parentType = nullptr;
        Object* (*m_createObjectFunc)() = nullptr;

    public:
        Type() = default;
        Type(const std::string& name, const Type* parentType, Object* (*createObjectFunc)());
        
        const Type* GetNextType() const { return m_nextType; }
        std::string GetName() const { return m_name; }
        Object* CreateObject() const { return m_createObjectFunc(); }
        
        bool IsChildOf(const Type* type) const;
        bool operator==(const Type* type) const { return this == type; }
    };
}
