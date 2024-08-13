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

PassPluginLibraryInfo getAddConstPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "Pass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                // 1: Register the AddConstAnalysis as an analysis pass so that
                // it can be requested by other passes as following:
                // FPM.getResult<AddConstAnalysis>(F), where FPM is the
                // FunctionAnalysisManager and F is the Function that shall be
                // analyzed.
                PB.registerAnalysisRegistrationCallback(registerAnalyses);

                // 2: Register the AddConstPrinterPass as "print<add-const>" so
                // that it can be used when specifying pass pipelines with
                // "-passes=". Also register AddConstPass as "add-const".
                PB.registerPipelineParsingCallback(registerPipeline);
            }};
}

// The public entry point for a pass plugin:
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getAddConstPluginInfo();
}