#include "parser.hpp"
#include "rules/rule501.hpp"
#include <clang/Tooling/CommonOptionsParser.h>
#include <llvm/Support/CommandLine.h>

using namespace clang::tooling;
using namespace llvm;

static cl::OptionCategory AnalyzerCategory("Custom Static Analyzer Options");

bool ASTVisitor::VisitBinaryOperator(clang::BinaryOperator *op)
{
    rule501::check(op, context_);
    return true;
}

int main(int argc, const char **argv)
{
    auto expectedParser = CommonOptionsParser::create(argc, argv, AnalyzerCategory);
    if (!expectedParser)
    {
        llvm::errs() << expectedParser.takeError();
        return 1;
    }

    CommonOptionsParser &optionsParser = expectedParser.get();
    ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());

    return tool.run(newFrontendActionFactory<AnalyzerFrontendAction>().get());
}