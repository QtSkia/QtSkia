gn_args = is_official_build=false
CONFIG(debug, debug|release) {
    gn_args += \
        is_debug=true
} else {
    gn_args += \
        is_debug=false
}
QtSkia_Static_Build = true
if($$QtSkia_Static_Build) {
    gn_args += \
        is_component_build=false
} else {
    gn_args += \
        is_component_build=true
}
gn_args += target_cpu=\"x64\"
ccstr=$$split(QMAKE_CC, /)
ccname=$$last(ccstr)
cxxstr=$$split(QMAKE_CXX, /)
cxxname=$$last(cxxstr)
!isEmpty(ccname):!isEmpty(cxxname) {
    gn_args += cc=\"$$ccname\" cxx=\"$$cxxname\"
}

