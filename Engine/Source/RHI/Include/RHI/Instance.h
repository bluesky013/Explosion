//
// Created by johnk on 9/1/2022.
//

#pragma once

#include <cstdint>

#include <Common/Utility.h>

#include <RHI/Common.h>

namespace RHI {
    class Gpu;

    class Instance {
    public:
        static Instance* CreateByPlatform();
        static Instance* CreateByType(const RHIType& type);

        NON_COPYABLE(Instance)
        virtual ~Instance();
        virtual RHIType GetRHIType() = 0;
        virtual uint32_t GetGpuNum() = 0;
        virtual Gpu* GetGpu(uint32_t index) = 0;
        virtual void Destroy() = 0;

    protected:
        explicit Instance();
    };

    using RHIGetInstanceFunc = Instance*(*)();
}
