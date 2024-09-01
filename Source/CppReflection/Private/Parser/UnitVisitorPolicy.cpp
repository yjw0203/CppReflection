#include "UnitVisitorPolicy.h"
#include <iostream>

int CRCondition_IsClassOrTypedef::Condition(CRCursor cursor, const CRNamespace& Namespace)
{
    CXCursorKind kind = cursor.GetKind();
    if (cursor.IsDefinition() && (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl))
    {
        return flag_is_class_or_struct;
    }
    else if(kind == CXCursor_TypedefDecl)
    {
        return flag_is_typedef;
    }
    return 0;
}

int CRCondition_IsAnnotateAttr::Condition(CRCursor cursor, const CRNamespace& Namespace)
{
    return cursor.GetKind() == CXCursor_AnnotateAttr;
}

int CRCondition_IsField::Condition(CRCursor cursor, const CRNamespace& Namespace)
{
    return cursor.GetKind() == CXCursor_FieldDecl;
}

void CRAction_PrintClass::DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag)
{
    std::string displayName = "";
    for (auto& name : Namespace)(displayName += name) += "::";
    displayName += cursor.GetDisplayName();
    std::cout << "ClassName: " << displayName << std::endl;
}

void CRAction_PrintAnnotateAttr::DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag)
{
    std::string displayName = "";
    for (int index = 0; index < Namespace.size(); index++)(displayName += Namespace[index]) += ((index + 1 == Namespace.size())? " -> " : "::");
    displayName += cursor.GetDisplayName();
    std::cout << "AnnotateAttr: " << displayName << std::endl;
}

void CRAction_PrintField::DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag)
{
    std::string displayName = "";
    for (auto& name : Namespace)(displayName += name) += "::";
    displayName += cursor.GetDisplayName();
    std::cout << "FieldName: " << displayName << std::endl;
}