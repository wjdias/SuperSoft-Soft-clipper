cmake_minimum_required(VERSION 3.22)
project(SuperSoftSoftClipper VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    message(FATAL_ERROR "JUCE submodule not found. Run: git submodule update --init --recursive")
endif()

add_subdirectory(JUCE)

juce_add_plugin(SuperSoftSoftClipper
    COMPANY_NAME "SuperSoft"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE SSpf
    PLUGIN_CODE SScp
    FORMATS VST3 AU
    PRODUCT_NAME "SoftClipper")

target_sources(SuperSoftSoftClipper
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/Dsp/SoftClipper.h)

target_compile_definitions(SuperSoftSoftClipper
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0)

target_link_libraries(SuperSoftSoftClipper
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
