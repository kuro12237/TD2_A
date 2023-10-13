#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#define TEXTURE_LOAD_MAX 32

class TextureManager
{
public:
	
	static TextureManager* GetInstance();

	static void Initialize();
	static void Finalize();

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

	static uint32_t NumLoadTexture() { return TextureManager::GetInstance()->NumLoadTextureIndex; }

private:

	static ComPtr<ID3D12Resource> CreateTexResource(const DirectX::TexMetadata& metadata);

	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	static void UploadTexData(const DirectX::ScratchImage& mipImage);

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


	ComPtr<ID3D12Resource> Resource[TEXTURE_LOAD_MAX];
	uint32_t NumLoadTextureIndex = 0;

};


