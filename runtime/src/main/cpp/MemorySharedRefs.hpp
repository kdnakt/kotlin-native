/*
 * Copyright 2010-2019 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license
 * that can be found in the LICENSE file.
 */

#ifndef RUNTIME_MEMORYSHAREDREFS_HPP
#define RUNTIME_MEMORYSHAREDREFS_HPP

#include <type_traits>

#include "Memory.h"

class KRefSharedHolder {
 public:
  void initLocal(ObjHeader* obj);

  void init(ObjHeader* obj);

  // Terminates if called from the wrong thread.
  ObjHeader* ref() const;
  ObjHeader* refOrNull() const;

  void dispose() const;

  OBJ_GETTER0(describe) const;

 private:
  ObjHeader* obj_;
  ForeignRefContext context_;

  bool isRefAccessible() const;
};

static_assert(std::is_trivially_destructible<KRefSharedHolder>::value,
    "KRefSharedHolder destructor is not guaranteed to be called.");

class BackRefFromAssociatedObject {
 public:
  void initAndAddRef(ObjHeader* obj);

  // Terminates if called from the wrong thread.
  void addRef();

  // Terminates if called from the wrong thread.
  bool tryAddRef();

  void releaseRef();

  // Terminates if called from the wrong thread.
  ObjHeader* ref() const;
  ObjHeader* refOrNull() const;

  inline bool permanent() const {
    return obj_->permanent(); // Safe to query from any thread.
  }

 private:
  ObjHeader* obj_;
  ForeignRefContext context_;
  volatile int refCount;

  bool isRefAccessible() const;
  void ensureRefAccessible() const;
};

static_assert(std::is_trivially_destructible<BackRefFromAssociatedObject>::value,
    "BackRefFromAssociatedObject destructor is not guaranteed to be called.");

#endif // RUNTIME_MEMORYSHAREDREFS_HPP
