defineReplace(gnArch) {
    qtArch = $$1
    contains(qtArch, "i386"): return(x86)
    contains(qtArch, "x86_64"): return(x64)
    contains(qtArch, "arm"): return(arm)
    contains(qtArch, "arm64"): return(arm64)
    contains(qtArch, "mips"): return(mipsel)
    contains(qtArch, "mips64"): return(mips64el)
    return(unknown)
}
