#ifndef PASS_H
#define PASS_H

#include "llvm/IR/PassManager.h"

namespace pass {
    struct AnalysisPass : public llvm::AnalysisInfoMixin<AnalysisPass> {
        // set Result to whatever your AnalysisPass is supposed to return
        using Result = llvm::SmallVector<int>;
        
        Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
        
        static llvm::AnalysisKey Key;
    };

    struct PrintAnalysisPass : public llvm::PassInfoMixin<PrintAnalysisPass> {
        explicit PrintAnalysisPass(llvm::raw_ostream &OS) : OS(OS) {}
        llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
    private:
        llvm::raw_ostream &OS;
    };

    struct TransformPass : public llvm::PassInfoMixin<TransformPass> {
        llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
    };
}

#endif