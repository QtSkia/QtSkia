CONFIG(debug, debug|release) {
    verbose_flags = -v
    gn_args += \
        is_official_build=false \
        is_debug=true
} else {
    verbose_flags =
    gn_args += \
        is_official_build=false \
        is_debug=false
}
if($$QtSkia_Static_Build) {
    gn_args += \
        is_component_build=false
} else {
    gn_args += \
        is_component_build=true
}
gn_args += target_cpu=\"x64\"
