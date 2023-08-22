//
// Copyright (c) .NET Foundation and Contributors
// See LICENSE file in the project root for full license information.
//

#include <nanoHAL_Types.h>
#include <nanoPAL_BlockStorage.h>

// 32kB blocks
const BlockRange BlockRange1[] = {

    // 0x08000000 nanoBooter
    {BlockRange_BLOCKTYPE_BOOTSTRAP, 0, 0},

    ///////////////////////////////////////////////////////////////////////////////////////
    // because this target is using a configuration block need to add the
    // configuration manager files to the CMake and call ConfigurationManager_Initialize()
    // in nanoBooter so the configuration can be managed when in booter mode
    ///////////////////////////////////////////////////////////////////////////////////////
    // 0x08008000 configuration block
    {BlockRange_BLOCKTYPE_CONFIG, 1, 1},
    ///////////////////////////////////////////////////////////////////////////////////////

    // 0x08010000 nanoCLR
    {BlockRange_BLOCKTYPE_CODE, 2, 3}};

// 128kB block
const BlockRange BlockRange2[] = {
    // 0x08020000 nanoCLR
    {BlockRange_BLOCKTYPE_CODE, 0, 0}};

// 256kB blocks
const BlockRange BlockRange3[] = {
    // 08040000 nanoCLR
    {BlockRange_BLOCKTYPE_CODE, 0, 0},

    // 08080000 deployment
    {BlockRange_BLOCKTYPE_DEPLOYMENT, 1, 2}};

const BlockRegionInfo BlockRegions[] = {
    {
        // no attributes for this region
        (0),

        // start address for block region
        0x08000000,
        // total number of blocks in this region
        4,
        // total number of bytes per block
        0x8000,
        ARRAYSIZE_CONST_EXPR(BlockRange1),
        BlockRange1,
    },

    {
        // no attributes for this region
        (0),
        // start address for block region
        0x08020000,
        // total number of blocks in this region
        1,
        // total number of bytes per block
        0x20000,
        ARRAYSIZE_CONST_EXPR(BlockRange2),
        BlockRange2,
    },

    {
        // no attributes for this region
        (0),
        // start address for block region
        0x08040000,
        // total number of blocks in this region
        3,
        // total number of bytes per block
        0x40000,
        ARRAYSIZE_CONST_EXPR(BlockRange3),
        BlockRange3,
    },

};

const DeviceBlockInfo Device_BlockInfo = {
    // STM32 flash memory is XIP
    (MediaAttribute_SupportsXIP),
    // UINT32 BytesPerSector
    2,
    // UINT32 NumRegions;
    ARRAYSIZE_CONST_EXPR(BlockRegions),
    // const BlockRegionInfo* pRegions;
    (BlockRegionInfo *)BlockRegions,
};

MEMORY_MAPPED_NOR_BLOCK_CONFIG Device_BlockStorageConfig = {
    {
        // BLOCK_CONFIG
        {
            // GPIO_PIN             Pin;
            0,
            // BOOL                 ActiveState;
            false,
        },

        // BlockDeviceinfo
        (DeviceBlockInfo *)&Device_BlockInfo,
    },

    {
        // CPU_MEMORY_CONFIG
        // UINT8  CPU_MEMORY_CONFIG::ChipSelect;
        0,
        // UINT8  CPU_MEMORY_CONFIG::ReadOnly;
        true,
        // UINT32 CPU_MEMORY_CONFIG::WaitStates;
        0,
        // UINT32 CPU_MEMORY_CONFIG::ReleaseCounts;
        0,
        // UINT32 CPU_MEMORY_CONFIG::BitWidth;
        16,
        // UINT32 CPU_MEMORY_CONFIG::BaseAddress;
        0x08000000,
        // UINT32 CPU_MEMORY_CONFIG::SizeInBytes;
        0x00200000,
        // UINT8  CPU_MEMORY_CONFIG::XREADYEnable
        0,
        // UINT8  CPU_MEMORY_CONFIG::ByteSignalsForRead
        0,
        // UINT8  CPU_MEMORY_CONFIG::ExternalBufferEnable
        0,
    },

    // UINT32 ChipProtection;
    0,
    // UINT32 ManufacturerCode;
    0,
    // UINT32 DeviceCode;
    0,
};

BlockStorageDevice Device_BlockStorage;
