#include "Pass.h"

using namespace llvm;

namespace pass {
    // Initialize the analysis key.
    AnalysisKey AnalysisPass::Key;

    AnalysisPass::Result AnalysisPass::run(Function &F, FunctionAnalysisManager &FAM) {
        return {};
    }

    PreservedAnalyses PrintAnalysisPass::run(Function &F, FunctionAnalysisManager &FAM) {
        AnalysisPass::Result res = FAM.getResult<AnalysisPass>(F);
        return PreservedAnalyses::all();
    }
}