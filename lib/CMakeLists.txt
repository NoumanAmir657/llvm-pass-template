add_library(
    Pass MODULE
        AnalysisPass.cpp
        Plugin.cpp
)

target_include_directories(Pass PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include")