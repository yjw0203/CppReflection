#include <iostream>
#include <vector>
#include <string>
#include "Parser/Unit.h"

int main()
{
    std::string cpp_file = "E:/workspace/CppReflection/Source/Example/Private/main.cpp";
    std::string generate_file_h = "E:/workspace/CppReflection/Source/Example/Private/main.generated.h";
    CRTranslationUnit unit = CRCreateTranslationUnitFromSourceFile(cpp_file.c_str());
    CRUnitPrintAllClassVisitor visitor1;
    visitor1.Visit(unit);
    CRUnitPrintAllField visitor2;
    visitor2.Visit(unit);
    CRUnitPrintAllAnnotateAttr visitor3;
    visitor3.Visit(unit);
    CRUnitGenerateFromAnnotateAttr visitor4(generate_file_h.c_str());
    visitor4.Visit(unit);
    return 0;
}
