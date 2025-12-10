cmake_minimum_required(VERSION 3.22)
project(mySine VERSION 0.0.1)

juce_add_console_app(mySine PRODUCT_NAME "mySine")
target_sources(mySine PRIVATE main.cpp sine.cpp oscillator.cpp)
target_compile_definitions(mySine PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(mySine
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(mySine PRIVATE cxx_std_20)
