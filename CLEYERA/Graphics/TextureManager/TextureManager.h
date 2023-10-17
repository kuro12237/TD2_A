#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#define TEXTURE_LOAD_MAX 64

class TextureManager
{
public:
	
	static TextureManager* GetInstance();

	static void Initialize();
	static void Finalize();

	/// <summary>
	/// 実際に使う処理
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	static uint32_t LoadTexture(const std::string& filePath);

	/// <summary>
	/// すべてのtexの解放
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
	///	リソースの設定 
	/// </summary>
	/// <param name="metadata"></param>
	/// <returns></returns>
	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// ヒープの設定
	/// </summary>
	/// <returns></returns>
	static D3D12_HEAP_PROPERTIES SettingHeap();

	ComPtr<ID3D12Resource> Resource[TEXTURE_LOAD_MAX];
	uint32_t NumLoadTextureIndex = 0;

	//Singleton
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	const TextureManager& operator=(const TextureManager&) = delete;

};


