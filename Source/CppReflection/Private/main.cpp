#include <iostream>
#include <vector>
#include <string>
#include <clang-c/Index.h>
#include "Parser/Unit.h"

int main()
{
    CRTranslationUnit unit = CRCreateTranslationUnitFromSourceFile("E:/workspace/CppReflection/Source/Example/Private/main.cpp");
    CRUnitPrintAllClassVisitor visitor1;
    visitor1.Visit(unit);
    CRUnitPrintAllAnnotateAttr visitor2;
    visitor2.Visit(unit);
    CRUnitPrintAllField visitor3;
    visitor3.Visit(unit);
    return 0;
}
