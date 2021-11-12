#pragma once

#include "PmxStructList.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class PmxRendering {
public:

	void Init();
	void CreateDescriptorHeaps();
	void VertexBufferAndView();
	void IndexBufferAndView();
	void ConstantBufferAndView();
	void MaterialBufferAndView();

	PmxData m_data;
private:

	unique_ptr<DescriptorHeap>  m_resourceDescriptors;
	unique_ptr<DescriptorHeap>  m_materialDescriptors;

	//! ���_�o�b�t�@�[�@�r���[
	ComPtr<ID3D12Resource>		m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView;

	//!�@�C���f�b�N�X�o�b�t�@�[�@�r���[
	ComPtr<ID3D12Resource>		m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		m_indexBufferView;
};