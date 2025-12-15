cmake_minimum_required(VERSION 3.22)
project(seqExecutable VERSION 0.0.1)

juce_add_console_app(seqExecutable PRODUCT_NAME "seqExecutable")
target_sources(seqExecutable PRIVATE main.cpp sine.cpp oscillator.cpp note.cpp melody.cpp callback.cpp)
target_compile_definitions(seqExecutable PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(seqExecutable
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(seqExecutable PRIVATE cxx_std_20)
