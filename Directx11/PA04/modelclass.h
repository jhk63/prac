////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	    XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
		XMFLOAT3 rotation;
	};

	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*, int);
	bool InitializeGround(ID3D11Device*, float, float, const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	XMFLOAT3 GetPosition() const;
	void SetPosition(float, float, float);

	XMFLOAT3 GetRotation();
	void SetRotation(float x, float y, float z);
	void UpdateRotation(float x, float y, float z);

	int GetIndexCount();
	int GetInstanceCount();
	int GetFaceCount();
	ID3D11ShaderResourceView* GetTexture();

	bool LoadModel(const WCHAR*);
	void ReleaseModel();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	ID3D11Buffer* m_instanceBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	int m_instanceCount = 0;

	TextureClass* m_Texture = nullptr;
	ModelType* m_model = nullptr;
	int	m_textureCount = 0;
	int m_normalCount = 0;
	int m_faceCount = 0;
};

#endif