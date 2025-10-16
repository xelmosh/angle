//
// Copyright 2025 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_TRANSLATOR_WGSL_WGSL_PROGRAM_PRELUDE_H_
#define COMPILER_TRANSLATOR_WGSL_WGSL_PROGRAM_PRELUDE_H_

#include "compiler/translator/ImmutableString.h"
#include "compiler/translator/InfoSink.h"
#include "compiler/translator/IntermNode.h"
namespace sh
{
struct WGSLWrapperFunction
{
    ImmutableString prefix;
    ImmutableString suffix;
};

class WGSLProgramPrelude
{
  public:
    WGSLWrapperFunction preIncrement(const TType &preIncrementedType);
    WGSLWrapperFunction preDecrement(const TType &preDecrementedType);
    WGSLWrapperFunction postIncrement(const TType &postIncrementedType);
    WGSLWrapperFunction postDecrement(const TType &postDecrementedType);

    void outputPrelude(TInfoSinkBase &sink);

  private:
    TSet<TType> mPreIncrementedTypes;
    TSet<TType> mPreDecrementedTypes;
    TSet<TType> mPostIncrementedTypes;
    TSet<TType> mPostDecrementedTypes;
};
}  // namespace sh

#endif  // COMPILER_TRANSLATOR_WGSL_WGSL_PROGRAM_PRELUDE_H_
