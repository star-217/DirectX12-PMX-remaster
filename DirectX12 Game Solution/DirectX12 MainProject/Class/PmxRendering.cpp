#include "PmxRendering.h"

#include "Base/pch.h"
#include "Base/dxtk.h"

void PmxRendering::Init()
{
	CreateDescriptorHeaps();

}

void PmxRendering::CreateDescriptorHeaps()
{
	m_resourceDescriptors = make_unique<DescriptorHeap>(DXTK->Device, 1);
	m_materialDescriptors = make_unique<DescriptorHeap>(DXTK->Device, m_data.numMaterial * 3);
}

void PmxRendering::VertexBufferAndView()
{
	D3D12_HEAP_PROPERTIES heapProp =
		CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	D3D12_RESOURCE_DESC resDesc =
		CD3DX12_RESOURCE_DESC::Buffer(sizeof(m_data.vertices[0]) * m_data.vertices.size());

	auto result = DXTK->Device->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_vertexBuffer.ReleaseAndGetAddressOf()));
	DX::ThrowIfFailed(result);

	void* map_addr = nullptr;
	m_vertexBuffer->Map(0, nullptr, &map_addr);
	CopyMemory(map_addr, m_data.vertices.data(), sizeof(m_data.vertices[0]) * m_data.vertices.size());
	m_vertexBuffer->Unmap(0, nullptr);

	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.SizeInBytes = sizeof(m_data.vertices[0]) * m_data.vertices.size();
	m_vertexBufferView.StrideInBytes = sizeof(m_data.vertices[0]);
}

void PmxRendering::IndexBufferAndView()
{
	D3D12_HEAP_PROPERTIES heapProp =
		CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	D3D12_RESOURCE_DESC resDesc =
		CD3DX12_RESOURCE_DESC::Buffer(sizeof(m_data.surfaces[0]) * m_data.surfaces.size());

	auto result = DXTK->Device->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(m_indexBuffer.ReleaseAndGetAddressOf()));

	m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
	m_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_indexBufferView.SizeInBytes = sizeof(m_data.surfaces[0]) * m_data.surfaces.size();

	//IndexBuffer‚Ì‘‚«o‚µ
	void* map_addr = nullptr;
	m_indexBuffer->Map(0, nullptr, &map_addr);
	CopyMemory(map_addr, m_data.surfaces.data(), sizeof(m_data.surfaces[0]) * m_data.surfaces.size());
	m_indexBuffer->Unmap(0, nullptr);
}

void PmxRendering::ConstantBufferAndView()
{
}

