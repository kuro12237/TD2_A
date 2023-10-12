#include"ParticlePlaneState.h"

void ParticlePlaneState::Initialize(Particle* state)
{
	if (NumInstansing)
	{
		//NumInstansingInitializeが二回呼び出されたらErrorを出す
		LogManager::Log("Particle Instansing Error");
		assert(0);
	}
	NumInstansing = state->GetNumInstancing();
	NumInstansingLock = true;

	resource_.instancingResource = CreateResources::CreateBufferResource(sizeof(ParticleData) * NumInstansing);
	dsvIndex = TextureManager::CreateSRV(NumInstansing, resource_.instancingResource, sizeof(ParticleData));

	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());
}

void ParticlePlaneState::Draw(Particle* state,list<Particle_param>param,ViewProjection viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	ParticleData* instansingData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instansingData));

	vertexData[0].position = { pos.x - size,pos.y + size,pos.z ,pos.w };
	vertexData[0].texcoord = { 0.0f,0.0f };//00
	vertexData[0].normal = { 0.0f,1.0f,0.0f };

	vertexData[1].position = { pos.x + size,pos.y + size,pos.z ,pos.w };
	vertexData[1].texcoord = { 1.0f,0.0f };//10
	vertexData[1].normal = { 0.0f,1.0f,0.0f };

	vertexData[2].position = { pos.x - size,pos.y - size,pos.z,pos.w };
	vertexData[2].texcoord = { 0.0f,1.0f };//01
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x + size,pos.y - size,pos.z,pos.w };
	vertexData[3].texcoord = { 1.0f,1.0f };//11
	vertexData[3].normal = { 0.0f,1.0f,0.0f };

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	materialData->color = { 1,1,1,1 };
	materialData->color = testColor;
	materialData->uvTransform = MatrixTransform::AffineMatrix({1,1,1}, {0,0,0},{0,0,0});
	
	//Billbordの計算
	CarmeraBillbord(viewprojection);
	
	NumDrawInstansing = 0;

	for (list<Particle_param>::iterator particleIterator = param.begin();
		particleIterator != param.end(); ++particleIterator){

		//スケールを出す
		sMat = MatrixTransform::ScaleMatrix((*particleIterator).worldTransform_.scale);
		//平行移動移動
		tMat = MatrixTransform::TranslateMatrix((*particleIterator).worldTransform_.translate);
		//Affine変換
		Matrix4x4 matWorld = MatrixTransform::Multiply(sMat, MatrixTransform::Multiply(billboardMatrix, tMat));
		//view変換
		matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewprojection.matView_, viewprojection.matProjection_));
		//uvのAffine
		(*particleIterator).uvTransform_.UpdateMatrix();
		//代入
		instansingData[NumDrawInstansing].WVP = matWorld;
		instansingData[NumDrawInstansing].world = MatrixTransform::Identity();
		instansingData[NumDrawInstansing].color = (*particleIterator).color_;
		instansingData[NumDrawInstansing].uvTransform = (*particleIterator).uvTransform_.matWorld;
		NumDrawInstansing++;
	}

	CommandCall(state->GetTexhandle());
}


void ParticlePlaneState::CarmeraBillbord(ViewProjection view)
{
	//回転
	Matrix4x4 backToFrontMatrix = MatrixTransform::Identity();
	Matrix4x4 rm = MatrixTransform::RotateXYZMatrix(view.rotation_.x, view.rotation_.y, view.rotation_.z);

	billboardMatrix = MatrixTransform::Multiply(backToFrontMatrix, rm);
	billboardMatrix.m[3][0] = 0.0f;
	billboardMatrix.m[3][1] = 0.0f;
	billboardMatrix.m[3][2] = 0.0f;
}

void ParticlePlaneState::CommandCall(uint32_t TexHandle)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSO pso = GraphicsPipelineManager::GetInstance()->GetPso();

	commands.m_pList->SetGraphicsRootSignature(pso.Particle3d.Add.rootSignature.Get());
	commands.m_pList->SetPipelineState(pso.Particle3d.Add.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//マテリアルCBufferの場所を設定
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	TextureManager::rootParamerterCommand(1, dsvIndex);
	TextureManager::rootParamerterCommand(2,TexHandle);
	
	commands.m_pList->DrawIndexedInstanced(IndexSize,NumDrawInstansing, 0, 0, 0);
}
