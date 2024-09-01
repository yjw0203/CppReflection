#include "UnitVisitorPolicy.h"
#include "Utils.h"
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
    if (cursor.GetKind() == CXCursor_AnnotateAttr)
    {
        if (cursor.GetDisplayName() == "type=class")
        {
            return flag_is_class;
        }
        else
        {
            return 1;
        }
    }
    return 0;
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

CRAction_GenerateFromAnnotateAttr::CRAction_GenerateFromAnnotateAttr(const char* generated_file_h)
    : m_generated_file_h(generated_file_h)
{}

void CRAction_GenerateFromAnnotateAttr::DoAction(CRCursor cursor, const CRNamespace& Namespace, int flag)
{
    if (flag == CRCondition_IsAnnotateAttr::flag_is_class)
    {
        std::string displayName = "";
        for (int index = 0; index < Namespace.size(); index++)(displayName += Namespace[index]) += ((index + 1 == Namespace.size()) ? "" : "::");

        std::string template_str = std::string("") + "#define GENERATED_BODY() public: const char* GetClassName(){return \"" + displayName +"\";} ";
    
        CRWriteFile(m_generated_file_h.c_str(), template_str);
    }
}