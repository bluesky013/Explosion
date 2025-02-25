//
// Created by johnk on 6/3/2022.
//

#include <unordered_map>

#include <RHI/DirectX12/Common.h>
#include <RHI/DirectX12/BindGroupLayout.h>

namespace RHI::DirectX12 {
    DX12BindGroupLayout::DX12BindGroupLayout(const BindGroupLayoutCreateInfo* createInfo)
        : BindGroupLayout(createInfo), dx12RootParameters({}), layoutIndex(createInfo->layoutIndex)
    {
        CreateDX12RootParameters(createInfo);
    }

    DX12BindGroupLayout::~DX12BindGroupLayout() = default;

    void DX12BindGroupLayout::Destroy()
    {
        delete this;
    }

    uint8_t DX12BindGroupLayout::GetLayoutIndex()
    {
        return layoutIndex;
    }

    const std::vector<RootParameterKeyInfo>& DX12BindGroupLayout::GetRootParameterKeyInfos() const
    {
        return rootParameterKeyInfos;
    }

    const std::vector<CD3DX12_ROOT_PARAMETER1>& DX12BindGroupLayout::GetDX12RootParameters() const
    {
        return dx12RootParameters;
    }

    void DX12BindGroupLayout::CreateDX12RootParameters(const BindGroupLayoutCreateInfo* createInfo)
    {
        std::unordered_map<ShaderStageBits, std::vector<const BindGroupLayoutEntry*>> visibilitiesMap;
        {
            ForEachBitsType<ShaderStageBits>([&visibilitiesMap](ShaderStageBits shaderStage) -> void { visibilitiesMap[shaderStage] = {}; });
            for (auto i = 0; i < createInfo->entryNum; i++) {
                for (auto& visibility : visibilitiesMap) {
                    if (!(createInfo->entries[i].shaderVisibility & visibility.first)) {
                        continue;
                    }
                    visibility.second.emplace_back(createInfo->entries + i);
                }
            }
        }

        for (const auto& visibility : visibilitiesMap) {
            for (const auto* entry : visibility.second) {
                dx12RootParameters.emplace_back();
                {
                    CD3DX12_DESCRIPTOR_RANGE1 dx12DescriptorRange;
                    dx12DescriptorRange.Init(DX12EnumCast<BindingType, D3D12_DESCRIPTOR_RANGE_TYPE>(entry->type), 1, entry->binding, createInfo->layoutIndex, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);
                    dx12RootParameters.back().InitAsDescriptorTable(1, &dx12DescriptorRange, DX12EnumCast<ShaderStageBits, D3D12_SHADER_VISIBILITY>(visibility.first));
                }

                rootParameterKeyInfos.emplace_back();
                {
                    auto& keyInfo = rootParameterKeyInfos.back();
                    keyInfo.shaderStage = visibility.first;
                    keyInfo.bindingType = entry->type;
                    keyInfo.layoutIndex = createInfo->layoutIndex;
                    keyInfo.binding = entry->binding;
                }
            }
        }
    }
}
