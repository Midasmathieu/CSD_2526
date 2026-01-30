
project(oop_Synth VERSION 0.0.1)
juce_add_console_app(${PROJECT_NAME} PRODUCT_NAME "oopSynthExecutable")
target_sources(${PROJECT_NAME} PRIVATE main.cpp oscillator.cpp sine.cpp callback.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0 SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
