#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/fbretal/software/Billiard/mac-build
  make -f /Users/fbretal/software/Billiard/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/fbretal/software/Billiard/mac-build
  make -f /Users/fbretal/software/Billiard/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/fbretal/software/Billiard/mac-build
  make -f /Users/fbretal/software/Billiard/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/fbretal/software/Billiard/mac-build
  make -f /Users/fbretal/software/Billiard/mac-build/CMakeScripts/ReRunCMake.make
fi

