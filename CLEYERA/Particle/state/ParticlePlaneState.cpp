#include"ParticlePlaneState.h"

void ParticlePlaneState::Initialize(Particle* state)
{

	if (NumInstansing)
	{
		//NumInstansingInitializeが二回呼び出されたらErrorを出す
		LogManager::Log("Particle Instansing Error");
		assert(0);
	}
	NumInstansing = state->GetNumInstance();
	NumInstansingLock = true;

	resource_.instancingResource = CreateResources::CreateBufferResource(sizeof(TransformationMatrix) * NumInstansing);

	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * VertexSize);
	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * VertexSize, resource_.Vertex.Get(), VertexSize);
	resource_.Material = CreateResources::CreateBufferResource(sizeof(Material));
	resource_.Index = CreateResources::CreateBufferResource(sizeof(uint32_t) * IndexSize);
	resource_.IndexBufferView = CreateResources::IndexCreateBufferView(sizeof(uint32_t) * IndexSize, resource_.Index.Get());

	dsvIndex = TextureManager::CreateSRV(2,resource_.instancingResource);
}

void ParticlePlaneState::Draw(Particle* state, WorldTransform worldTransform, ViewProjection viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;
	uint32_t* indexData = nullptr;
	TransformationMatrix* instansingData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	resource_.Index->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
	resource_.instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instansingData));

	vertexData[0].position = { pos.x - size,pos.y + size,pos.z ,pos.w };
	vertexData[0].texcoord = { 0.0f,0.0f };
	vertexData[0].normal = { 0.0f,1.0f,0.0f };

	vertexData[1].position = { pos.x + size,pos.y + size,pos.z ,pos.w };
	vertexData[1].texcoord = { 1.0f,0.0f };
	vertexData[1].normal = { 0.0f,1.0f,0.0f };

	vertexData[2].position = { pos.x - size,pos.y - size,pos.z,pos.w };
	vertexData[2].texcoord = { 0.0f,1.0f };
	vertexData[2].normal = { 0.0f,1.0f,0.0f };

	vertexData[3].position = { pos.x + size,pos.y - size,pos.z,pos.w };
	vertexData[3].texcoord = { 1.0f,1.0f };
	vertexData[3].normal = { 0.0f,1.0f,0.0f };

	indexData[0] = 0; indexData[1] = 1; indexData[2] = 2;
	indexData[3] = 1; indexData[4] = 3; indexData[5] = 2;

	ImGui::Begin("testColorChange");
	ImGui::DragFloat4("Testcolor", &testColor.x, -0.01f);
	ImGui::End();

	materialData->color = testColor;
	materialData->uvTransform = MatrixTransform::AffineMatrix({1,1,1}, {0,0,0},{0,0,0});

	Matrix4x4  matWorld = MatrixTransform::Multiply(state->GetWorldTransform().matWorld, MatrixTransform::Multiply(viewprojection.matView_, viewprojection.matProjection_));
	worldTransform;

	instansingData[0].WVP =matWorld;
	instansingData[0].world = MatrixTransform::Identity();
	
	ImGui::Begin("b");
	ImGui::DragFloat3("r", &testTrans.x, -0.1f);
	ImGui::End();

	Matrix4x4 TestMat = MatrixTransform::AffineMatrix(state->GetWorldTransform().scale, {0,0,0}, testTrans);
	TestMat = MatrixTransform::Multiply(TestMat, MatrixTransform::Multiply(viewprojection.matView_, viewprojection.matProjection_));

	instansingData[1].WVP = TestMat;
	instansingData[1].world = MatrixTransform::Identity();
	
	CommandCall(state->GetTexhandle());
}

void ParticlePlaneState::CommandCall(uint32_t TexHandle)
{
	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSO pso = GraphicsPipelineManager::GetInstance()->GetPso();

	commands.m_pList->SetGraphicsRootSignature(pso.Particle3d.none.rootSignature.Get());
	commands.m_pList->SetPipelineState(pso.Particle3d.none.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);
	commands.m_pList->IASetIndexBuffer(&resource_.IndexBufferView);

	//形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//マテリアルCBufferの場所を設定
	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());

	TextureManager::rootParamerterCommand(1, dsvIndex);
	TextureManager::rootParamerterCommand(2,TexHandle);
	
	commands.m_pList->DrawIndexedInstanced(IndexSize, 2, 0, 0, 0);
}
