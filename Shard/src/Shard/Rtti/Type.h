#pragma once

namespace Shard
{
    class Object;

    class Type
    {
    private:
        std::string m_Name;
        Object* (*m_CreateObjectFunc)();
        Type* m_NextType;

    public:
        Type(std::string name, Object* (*createObjectFunc)());

        const Type* GetNextType() const { return m_NextType; }
        const std::string GetName() const { return m_Name; }
        Object* CreateObject() const { m_CreateObjectFunc(); }
    };
}
