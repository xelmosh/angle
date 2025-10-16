//
// Copyright 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// SymbolUniqueId.h: Encapsulates a unique id for a symbol.

#ifndef COMPILER_TRANSLATOR_SYMBOLUNIQUEID_H_
#define COMPILER_TRANSLATOR_SYMBOLUNIQUEID_H_

#include "compiler/translator/Common.h"

namespace sh
{

class TSymbolTable;
class TSymbol;

class TSymbolUniqueId
{
  public:
    POOL_ALLOCATOR_NEW_DELETE
    explicit TSymbolUniqueId(const TSymbol &symbol);
    constexpr TSymbolUniqueId(const TSymbolUniqueId &) = default;
    TSymbolUniqueId &operator=(const TSymbolUniqueId &) = default;
    bool operator==(const TSymbolUniqueId &other) const { return mId == other.mId; }
    bool operator!=(const TSymbolUniqueId &other) const { return !(*this == other); }

    constexpr int get() const { return mId; }

    static constexpr TSymbolUniqueId kInvalid() { return TSymbolUniqueId(-1); }

  private:
    friend class TSymbolTable;
    explicit TSymbolUniqueId(TSymbolTable *symbolTable);

    friend class BuiltInId;
    constexpr TSymbolUniqueId(int staticId) : mId(staticId) {}

    int mId;
};

enum class SymbolType : uint8_t
{
    BuiltIn,
    UserDefined,
    AngleInternal,
    Empty  // Meaning symbol without a name.
};

enum class SymbolClass : uint8_t
{
    Function,
    Variable,
    Struct,
    InterfaceBlock
};

}  // namespace sh

namespace std
{
template <>
struct hash<sh::TSymbolUniqueId>
{
    size_t operator()(const sh::TSymbolUniqueId &key) const { return key.get(); }
};
}  // namespace std

#endif  // COMPILER_TRANSLATOR_SYMBOLUNIQUEID_H_
