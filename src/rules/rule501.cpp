#include "rules/rule501.hpp"
#include <clang/Basic/SourceManager.h>
#include <llvm/ADT/FoldingSet.h>
#include <iostream>

bool rule501::areEquivalentSubExprs(const clang::Expr *lhs,
                                    const clang::Expr *rhs,
                                    clang::ASTContext *context)
{
    if (!lhs || !rhs || !context)
        return false;

    const clang::Expr *cleanLHS = lhs->IgnoreParenImpCasts();
    const clang::Expr *cleanRHS = rhs->IgnoreParenImpCasts();

    llvm::FoldingSetNodeID idLHS, idRHS;
    cleanLHS->Profile(idLHS, *context, true);
    cleanRHS->Profile(idRHS, *context, true);

    return idLHS == idRHS;
}

void rule501::check(clang::BinaryOperator *op, clang::ASTContext *context)
{
    if (!op || !context)
        return;

    clang::SourceManager &sm = context->getSourceManager();
    clang::SourceLocation loc = op->getOperatorLoc();

    if (sm.isInSystemHeader(loc))
    {
        return;
    }

    if (op->isLogicalOp() || op->isComparisonOp() ||
        op->getOpcode() == clang::BO_Sub || op->getOpcode() == clang::BO_Div)
    {

        if (areEquivalentSubExprs(op->getLHS(), op->getRHS(), context))
        {
            unsigned lineNo = sm.getSpellingLineNumber(loc);
            std::cout << "\033[1;31m[WARNING 501]\033[0m Identical sub-expressions to the left "
                      << "and right of '" << op->getOpcodeStr().str() << "' "
                      << "at line " << lineNo << std::endl;
        }
    }
}