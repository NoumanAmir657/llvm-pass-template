#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

#include "Pass.h"

using namespace llvm;

void registerAnalyses(FunctionAnalysisManager &FAM) {
    FAM.registerPass([] { return pass::AnalysisPass(); });
}

bool registerPipeline(StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
    if (Name == "print<my_pass>") {
        FPM.addPass(pass::PrintAnalysisPass(errs()));
        return true;
    }
    if (Name == "my_pass") {
        FPM.addPass(pass::TransformPass());
        return true;
    }
    return false;
}

PassPluginLibraryInfo getPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "Pass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerAnalysisRegistrationCallback(registerAnalyses);
                PB.registerPipelineParsingCallback(registerPipeline);
            }};
}

// The public entry point for a pass plugin:
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getPassPluginInfo();
}