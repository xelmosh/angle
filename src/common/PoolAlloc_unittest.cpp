//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// PoolAlloc_unittest:
//   Tests of the PoolAlloc class
//

#ifdef UNSAFE_BUFFERS_BUILD
#    pragma allow_unsafe_buffers
#endif

#include <gtest/gtest.h>

#include "common/PoolAlloc.h"

namespace angle
{
// Verify the public interface of PoolAllocator class
TEST(PoolAllocatorTest, Interface)
{
    size_t numBytes               = 1024;
    constexpr uint32_t kTestValue = 0xbaadbeef;
    // Create a default pool allocator and allocate from it
    PoolAllocator poolAllocator;
    void *allocation = poolAllocator.allocate(numBytes);
    // Verify non-zero ptr returned
    EXPECT_NE(nullptr, allocation);
    // Write to allocation to check later
    uint32_t *writePtr = static_cast<uint32_t *>(allocation);
    *writePtr          = kTestValue;
    // Test other allocator creating a new allocation
    {
        PoolAllocator poolAllocator2;
        allocation = poolAllocator2.allocate(numBytes);
        EXPECT_NE(nullptr, allocation);
        // Make an allocation that spans multiple pages
        allocation = poolAllocator2.allocate(10 * 1024);
        // Free previous two allocations.
    }
    // Verify first allocation still has data
    EXPECT_EQ(kTestValue, *writePtr);
    // Make a bunch of allocations
    for (uint32_t i = 0; i < 1000; ++i)
    {
        numBytes   = (rand() % (1024 * 4)) + 1;
        allocation = poolAllocator.allocate(numBytes);
        EXPECT_NE(nullptr, allocation);
        // Write data into full allocation. In debug case if we
        //  overwrite any other allocation we get error.
        memset(allocation, 0xb8, numBytes);
    }
}

#if !defined(ANGLE_POOL_ALLOC_GUARD_BLOCKS)
// Verify allocations are correctly aligned for different alignments
class PoolAllocatorAlignmentTest : public testing::TestWithParam<int>
{};

TEST_P(PoolAllocatorAlignmentTest, Alignment)
{
    int alignment = GetParam();
    // Create a pool allocator to allocate from
    PoolAllocator poolAllocator(4096, alignment);
    // Test a number of allocation sizes for each alignment
    for (uint32_t i = 0; i < 100; ++i)
    {
        // Vary the allocation size around 4k to hit some multi-page allocations
        const size_t numBytes = rand() % (1024 * 4) + 1;
        void *allocation      = poolAllocator.allocate(numBytes);
        // Verify alignment of allocation matches expected default
        EXPECT_EQ(0u, reinterpret_cast<uintptr_t>(allocation) % alignment)
            << "Iteration " << i << " allocating " << numBytes;
    }
}

INSTANTIATE_TEST_SUITE_P(,
                         PoolAllocatorAlignmentTest,
                         testing::Values(2, 4, 8, 16, 32, 64, 128),
                         testing::PrintToStringParamName());
#endif
}  // namespace angle
