////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"

#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const int MODEL_COUNT = 10;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);

	bool ChangeBackground(float, float, float, float);
	bool ChangeRasterDesc(D3D11_FILL_MODE, D3D11_CULL_MODE);

	bool ChangeTextureFilter(int);

	CameraClass* GetCamera();

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Models[MODEL_COUNT];
	ModelClass* m_Skybox;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;
	//BitmapClass* m_Bitmap;

	TextClass* m_Text;

	//////////////////////////////////////////////////////////////////////////////

	int m_objectCount;
	int m_polygonCount;

	float b_red;
	float b_green;
	float b_blue;
	float b_alpha;

	float delay;
};

#endif