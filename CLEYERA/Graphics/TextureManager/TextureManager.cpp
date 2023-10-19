#include"TextureManager.h"

void TextureManager::Initialize()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
}

void TextureManager::Finalize()
{
	CoUninitialize();
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

DirectX::ScratchImage TextureManager::CreateMipImage(const std::string& filePath)
{
	//テクスチャファイルを読み込みプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = LogManager::ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));
	//ミップマップの作成
	DirectX::ScratchImage mipImage{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImage);

	return mipImage;

}

void TextureManager::UploadTexData( const DirectX::ScratchImage& mipImage)
{
	const DirectX::TexMetadata& metadata = mipImage.GetMetadata();

	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel)
	{
		const DirectX::Image* img = mipImage.GetImage(mipLevel, 0, 0);
		TextureManager::GetInstance()->Resource[DescriptorManager::GetIndex()]->
		WriteToSubresource(
			UINT(mipLevel),
			nullptr,
			img->pixels,
			UINT(img->rowPitch),
			UINT(img->slicePitch)
		);
	}

}

D3D12_RESOURCE_DESC TextureManager::SettingResource(const DirectX::TexMetadata& metadata)
{
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);
	resourceDesc.Height = UINT(metadata.height);
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	resourceDesc.Format = metadata.format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	return resourceDesc;

}

D3D12_HEAP_PROPERTIES TextureManager::SettingHeap()
{
	D3D12_HEAP_PROPERTIES heapProperties{};

	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	return heapProperties;
}

ComPtr<ID3D12Resource> TextureManager::CreateTexResource(const DirectX::TexMetadata& metadata)
{
	ComPtr<ID3D12Resource> Resource;
	D3D12_RESOURCE_DESC resourceDesc{};
	D3D12_HEAP_PROPERTIES heapProperties{};

	//リソースの設定
	resourceDesc = SettingResource(metadata);
	heapProperties = SettingHeap();

	//本体を作る
	DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&Resource));


	return Resource;
}

uint32_t TextureManager::LoadTexture(const std::string& filePath)
{
	
	DescriptorManager::IndexIncrement();
	const uint32_t index = DescriptorManager::GetIndex();
	TextureManager::GetInstance()->NumLoadTextureIndex++;

	DirectX::ScratchImage mipImages = CreateMipImage(filePath);
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	TextureManager::GetInstance()->Resource[index] = CreateTexResource(metadata);
	UploadTexData(mipImages);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = UINT(metadata.mipLevels);

   //Desp\cripter
	DescriptorManager::SetCPUDescripterHandle(
		DescriptorManager::GetCPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap().Get(),
			DescriptorManager::GetDescripterSize().SRV,index),
		index
	);

	DescriptorManager::SetGPUDescripterHandle(
		DescriptorManager::GetGPUDescriptorHandle(
			DirectXCommon::GetInstance()->GetSrvHeap().Get(),
			DescriptorManager::GetDescripterSize().SRV, index),
		index
	);

	DescriptorManager::CGHandlePtr();

	DescriptorManager::CreateShaderResourceView(
		TextureManager::GetInstance()->Resource[index].Get(),
		srvDesc,
		index);
	
	return index;
}

void TextureManager::AllUnTexture()
{
	for (int i = DescriptorManager::GetIndex(); i > 0; i--)
	{
	   TextureManager::GetInstance()->Resource[i].Reset();
	}
	TextureManager::GetInstance()->NumLoadTextureIndex = 0;
}



