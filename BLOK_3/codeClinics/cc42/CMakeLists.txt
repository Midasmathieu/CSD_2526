project(Filters2 VERSION 0.0.1)
juce_add_console_app(Filters2 PRODUCT_NAME "Filters2")
target_sources(Filters2 PRIVATE main.cpp)
target_compile_definitions(Filters2 PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(Filters2
        PRIVATE
        csd_lib

        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(Filters2 PRIVATE cxx_std_20)
