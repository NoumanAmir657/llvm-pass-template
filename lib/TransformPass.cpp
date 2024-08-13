#include "Pass.h"

using namespace llvm;

namespace pass {
    PreservedAnalyses TransformPass::run(Function &F, FunctionAnalysisManager &FAM) {
        return PreservedAnalyses::all();
    }
}