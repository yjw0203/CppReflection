#pragma once
#include <clang-c/Index.h>
#include "Cursor.h"
#include "UnitVisitorPolicy.h"

class CRTranslationUnit
{
public:
    CRTranslationUnit(const CXTranslationUnit& handle);
    operator CXTranslationUnit();
    CRCursor GetRootCursor();

private:
    CXTranslationUnit m_handle;
};

#include "UnitVisitor.h"

template<class ActionPolicy>
using CRUnitVisitorForClass = CRTranslationUnitVisitor<CRCondition_IsClassOrTypedef, ActionPolicy>;

template<class ActionPolicy>
using CRUnitVisitorForAnnotateAttr = CRTranslationUnitVisitor<CRCondition_IsAnnotateAttr, ActionPolicy>;

template<class ActionPolicy>
using CRUnitVisitorForField = CRTranslationUnitVisitor<CRCondition_IsField, ActionPolicy>;

using CRUnitPrintAllClassVisitor = CRUnitVisitorForClass<CRAction_PrintClass>;
using CRUnitPrintAllAnnotateAttr = CRUnitVisitorForAnnotateAttr<CRAction_PrintAnnotateAttr>;
using CRUnitPrintAllField = CRUnitVisitorForField<CRAction_PrintField>;

CRTranslationUnit CRCreateTranslationUnitFromSourceFile(const char* source_filename);
