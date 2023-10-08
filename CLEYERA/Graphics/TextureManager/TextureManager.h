#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
struct texResourceProperty
{
	D3D12_CPU_DESCRIPTOR_HANDLE SrvHandleCPU{};
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU{};
	ComPtr<ID3D12Resource> Resource;
};

struct DescriptorSize
{
	uint32_t SRV;
	uint32_t RTV;
	uint32_t DSV;
};

class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	static void Initialize();
	static void Finalize();

	static TextureManager* GetInstance();
	/// <summary>
	/// ���ۂɎg������
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	static uint32_t LoadTexture(const std::string& filePath);

	/// <summary>
	/// ���ׂĂ�tex�̉��
	/// </summary>
	/// <param name="texHandle"></param>
	/// <returns></returns>
	static void AllUnTexture();

	static uint32_t CreateSRV(uint32_t NumInstansing, ComPtr<ID3D12Resource>& resource);

	static void texCommand(UINT rootPatramerterIndex,uint32_t texhandle);
private:

	static ComPtr<ID3D12Resource> CreateTexResource(const DirectX::TexMetadata& metadata);

	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	static void UploadTexData(const DirectX::ScratchImage& mipImage);

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap, uint32_t desiripterSize, uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap, uint32_t desiripterSize, uint32_t index);

	/// <summary>
	///	���\�[�X�̐ݒ� 
	/// </summary>
	/// <param name="metadata"></param>
	/// <returns></returns>
	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// �q�[�v�̐ݒ�
	/// </summary>
	/// <returns></returns>
	static D3D12_HEAP_PROPERTIES SettingHeap();

	const static uint32_t TexLoadMax = 256;
	texResourceProperty tex[TexLoadMax];
};


