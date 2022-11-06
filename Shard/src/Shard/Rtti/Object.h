#pragma once
#include "Type.h"

namespace Shard
{
    class Object
    {
        static Type m_Type;
    public:
        static Object* CreateObject() { return new Object(); };

        const Type* GetStaticType() const { return &m_Type; }

        virtual const Type* GetDynamicType() const { return &m_Type; }

        virtual std::string ToString() const { return "Base Object"; }
    };
}