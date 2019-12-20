use_relative_paths = True

vars = {
  "checkout_chromium": False,
}

deps = {
  "buildtools"                            : "https://gitee.com/QtSkia/buildtools.git@505de88083136eefd056e5ee4ca0f01fe9b33de8",
  "common"                                : "https://gitee.com/QtSkia/common.git@9737551d7a52c3db3262db5856e6bcd62c462b92",
  "third_party/externals/angle2"          : "https://gitee.com/QtSkia/angle.git@d1860ea17e8e9434c3124821f192a09bb8e5ecdd",
  "third_party/externals/dawn"            : "https://gitee.com/QtSkia/dawn.git@3c086a0c2e1dc3e2e14aaa3d78c052c7e07274b4",
  "third_party/externals/dng_sdk"         : "https://gitee.com/QtSkia/dng_sdk.git@c8d0c9b1d16bfda56f15165d39e0ffa360a11123",
  "third_party/externals/egl-registry"    : "https://gitee.com/QtSkia/EGL-Registry@a0bca08de07c7d7651047bedc0b653cfaaa4f2ae",
  "third_party/externals/expat"           : "https://gitee.com/QtSkia/expat.git@e5aa0a2cb0a5f759ef31c0819dc67d9b14246a4a",
  "third_party/externals/freetype"        : "https://gitee.com/QtSkia/freetype2.git@0a3d2bb99b45b72e1d45185ab054efa993d97210",
  "third_party/externals/harfbuzz"        : "https://gitee.com/QtSkia/harfbuzz.git@1bada656a86e9cb27d4a6b9fcc50748f0bd9c1d9",
  "third_party/externals/icu"             : "https://gitee.com/QtSkia/icu.git@407b39301e71006b68bd38e770f35d32398a7b14",
  "third_party/externals/imgui"           : "https://gitee.com/QtSkia/imgui.git@d38d7c6628bebd02692cfdd6fa76b4d992a35b75",
  "third_party/externals/libgifcodec"     : "https://gitee.com/QtSkia/libgifcodec@38d9c73f49b861bb4a9829371ac311544b120023",
  "third_party/externals/libjpeg-turbo"   : "https://gitee.com/QtSkia/libjpeg-turbo.git@574f3a772c96dc9db2c98ef24706feb3f6dbda9a",
  "third_party/externals/libpng"          : "https://gitee.com/QtSkia/libpng.git@386707c6d19b974ca2e3db7f5c61873813c6fe44",
  "third_party/externals/libwebp"         : "https://gitee.com/QtSkia/libwebp.git@0fe1a89dbf1930fc2554dbe76adad5d962054ead",
  "third_party/externals/lua"             : "https://gitee.com/QtSkia/lua.git@e354c6355e7f48e087678ec49e340ca0696725b1",
  "third_party/externals/microhttpd"      : "https://gitee.com/QtSkia/libmicrohttpd@748945ec6f1c67b7efc934ab0808e1d32f2fb98d",
  "third_party/externals/opencl-lib"      : "https://gitee.com/QtSkia/opencl-lib@4e6d30e406d2e5a65e1d65e404fe6df5f772a32b",
  "third_party/externals/opencl-registry" : "https://gitee.com/QtSkia/OpenCL-Registry@932ed55c85f887041291cef8019e54280c033c35",
  "third_party/externals/opengl-registry" : "https://gitee.com/QtSkia/OpenGL-Registry@14b80ebeab022b2c78f84a573f01028c96075553",
  "third_party/externals/piex"            : "https://gitee.com/QtSkia/piex.git@bb217acdca1cc0c16b704669dd6f91a1b509c406",
  "third_party/externals/sdl"             : "https://gitee.com/QtSkia/sdl@5d7cfcca344034aff9327f77fc181ae3754e7a90",
  "third_party/externals/sfntly"          : "https://gitee.com/QtSkia/sfntly.git@b55ff303ea2f9e26702b514cf6a3196a2e3e2974",
  "third_party/externals/spirv-cross"     : "https://gitee.com/QtSkia/SPIRV-Cross@53ab2144b90abede33be5161aec5dfc94ddc3caf",
  "third_party/externals/spirv-headers"   : "https://gitee.com/QtSkia/SPIRV-Headers.git@29c11140baaf9f7fdaa39a583672c556bf1795a1",
  "third_party/externals/spirv-tools"     : "https://gitee.com/QtSkia/SPIRV-Tools.git@0c4feb643b89d1792b02f7cbef315e9d95633bd7",
  "third_party/externals/swiftshader"     : "https://gitee.com/QtSkia/SwiftShader@fbbfeb700295d1fe1ec6419a93594e5e1540ea32",
  #"third_party/externals/v8"              : "https://gitee.com/QtSkia/v8.git@5f1ae66d5634e43563b2d25ea652dfb94c31a3b4",
  "third_party/externals/wuffs"           : "https://gitee.com/QtSkia/wuffs.git@4080840928c0b05a80cda0d14ac2e2615f679f1a",
  "third_party/externals/zlib"            : "https://gitee.com/QtSkia/zlib@47af7c547f8551bd25424e56354a2ae1e9062859",

  "../src": {
    "url": "https://chromium.googlesource.com/chromium/src.git@b1568f298495e06c26fe33c7d3dbb77ecbda949b",
    "condition": "checkout_chromium",
  },
}

recursedeps = [
  "common",
  "../src",
]

gclient_gn_args_from = 'src'
