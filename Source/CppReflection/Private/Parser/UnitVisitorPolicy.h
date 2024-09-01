 #pragma once
#include "Cursor.h"

struct CRCondition_IsClassOrTypedef
{
    int Condition(CRCursor cursor, const CRNamespace& Namespace);

    static const int flag_is_class_or_struct = 1;
    static const int flag_is_typedef = 2;//such as typedef 
};

struct CRCondition_IsAnnotateAttr
{
    int Condition(CRCursor cursor, const CRNamespace& Namespace);
};

struct CRCondition_IsField
{
    int Condition(CRCursor cursor, const CRNamespace& Namespace);
};


class CRAction_PrintClass
{
public:
    void DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag);
};

class CRAction_PrintAnnotateAttr
{
public:
    void DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag);
};

class CRAction_PrintField
{
public:
    void DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag);
};