#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Tooling/Tooling.h>

class ASTVisitor : public clang::RecursiveASTVisitor<ASTVisitor>
{
public:
    explicit ASTVisitor(clang::ASTContext *context) : context_(context) {}

    bool VisitBinaryOperator(clang::BinaryOperator *op);

private:
    clang::ASTContext *context_;
};

class AnalyzerASTConsumer : public clang::ASTConsumer
{
public:
    explicit AnalyzerASTConsumer(clang::ASTContext *context) : visitor_(context) {}

    void HandleTranslationUnit(clang::ASTContext &context) override
    {
        visitor_.TraverseDecl(context.getTranslationUnitDecl());
    }

private:
    ASTVisitor visitor_;
};

class AnalyzerFrontendAction : public clang::ASTFrontendAction
{
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance &compiler, llvm::StringRef file) override
    {
        return std::make_unique<AnalyzerASTConsumer>(&compiler.getASTContext());
    }
};