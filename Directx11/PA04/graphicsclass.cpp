////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		m_Models[i] = 0;
	}
	
	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	//m_Bitmap = 0;
	m_Text = 0;

	m_objectCount = 0;
	m_polygonCount = 0;

	b_red = 0;
	b_green = 0;
	b_blue = 0;
	b_alpha = 1.0f;

	delay = 0.0f;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, -50.0f, -100.0f);	

	// Create the model object.
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		m_Models[i] = new ModelClass;
		if (!m_Models[i])
		{
			return false;
		}
	}

	m_Skybox = new ModelClass;
	if (!m_Skybox)
	{
		return false;
	}

	result = m_Skybox->Initialize(m_D3D->GetDevice(), L"./data/cube.obj", L"./data/skybox1.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the skybox object.", L"Error", MB_OK);
		return false;
	}
	
	// Initialize the model object.
	result = m_Models[0]->Initialize(m_D3D->GetDevice(), L"./data/plane2.obj", L"./data/grass.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[1]->Initialize(m_D3D->GetDevice(), L"./data/windmill.obj", L"./data/windmill.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[2]->Initialize(m_D3D->GetDevice(), L"./data/windmill2.obj", L"./data/windmill2.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[3]->Initialize(m_D3D->GetDevice(), L"./data/house.obj", L"./data/house.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[4]->Initialize(m_D3D->GetDevice(), L"./data/dog.obj", L"./data/dog.dds", 2);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[5]->Initialize(m_D3D->GetDevice(), L"./data/fence.obj", L"./data/house.dds", 40);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[6]->Initialize(m_D3D->GetDevice(), L"./data/fence.obj", L"./data/house.dds", 20);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[7]->Initialize(m_D3D->GetDevice(), L"./data/ani2.obj", L"./data/ani2.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Models[8]->Initialize(m_D3D->GetDevice(), L"./data/monarch.obj", L"./data/monarch.dds", 3);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object. 8", L"Error", MB_OK);
		return false;
	}

	result = m_Models[9]->Initialize(m_D3D->GetDevice(), L"./data/tower.obj", L"./data/tower.dds", 1);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object. 8", L"Error", MB_OK);
		return false;
	}

	// Check Model Object and Polygon Count
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		if (m_Models[i])
		{
			m_objectCount += m_Models[i]->GetInstanceCount();
			m_polygonCount += m_Models[i]->GetFaceCount();
		}
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, -1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	result = m_Text->SetObjectCount(m_objectCount, m_D3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set the object text.", L"Error", MB_OK);
		return false;
	}

	result = m_Text->SetPolygonCount(m_polygonCount, m_D3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set the polygon text.", L"Error", MB_OK);
		return false;
	}
	return true;
}


void GraphicsClass::Shutdown()
{
	if (m_Skybox)
	{
		m_Skybox->Shutdown();
		delete m_Skybox;
		m_Skybox = 0;
	}

	// Release the model object.
	for (int i = 0; i < MODEL_COUNT; i++)
	{
		if (m_Models[i])
		{
			m_Models[i]->Shutdown();
			delete m_Models[i];
			m_Models[i] = 0;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame(int fps, int cpu)
{
	bool result;

	float rotationSpeed = 1.0f;

	// Update the rotation variable each frame.
	m_Models[2]->SetPosition(0.0f, 0.0f, 5.0f);
	m_Models[2]->UpdateRotation(rotationSpeed, 0, 0);

	rotationSpeed = 0.5f;
	m_Models[4]->UpdateRotation(0, -rotationSpeed, 0);
	m_Models[8]->UpdateRotation(0, -rotationSpeed, 0);

	m_Models[5]->SetPosition(45.0f, 0.0f, 50.0f);

	// PA01_2.2_2.3_ChangeRasterDesc
	if (delay != 0.0f)
	{
		delay -= 1.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	XMFLOAT3 modelPosition;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(b_red, b_green, b_blue, b_alpha);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Skybox
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixTranslation(0, -60.0f, 0);

	m_Skybox->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Skybox->GetIndexCount(), 1,
		worldMatrix, viewMatrix, projectionMatrix, m_Skybox->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[0]->GetPosition();
	worldMatrix = XMMatrixTranslation(modelPosition.x, -60.0f, modelPosition.z);

	m_Models[0]->Render(m_D3D->GetDeviceContext());
	/*result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Models[0]->GetIndexCount(), m_Models[0]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Models[0]->GetTexture());*/
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[0]->GetIndexCount(), m_Models[0]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[0]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[1]->GetPosition();
	worldMatrix = XMMatrixTranslation(-50.0f, modelPosition.y, modelPosition.z);

	m_Models[1]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[1]->GetIndexCount(), m_Models[1]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[1]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	
	modelPosition = m_Models[2]->GetPosition();
	XMFLOAT3 modelRotation = m_Models[2]->GetRotation();

	worldMatrix *= XMMatrixTranslation(-modelPosition.x, -modelPosition.y, -modelPosition.z);
	worldMatrix *= XMMatrixRotationX(XMConvertToRadians(modelRotation.x));
	worldMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	m_Models[2]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[2]->GetIndexCount(), m_Models[2]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[2]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[3]->GetPosition();
	worldMatrix = XMMatrixTranslation(100.0f, -60.0f, modelPosition.z);

	m_Models[3]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[3]->GetIndexCount(), m_Models[3]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[3]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[4]->GetPosition();
	worldMatrix = XMMatrixTranslation(-20.0f, -60.0f, modelPosition.z);

	modelRotation = m_Models[4]->GetRotation();

	worldMatrix *= XMMatrixTranslation(-modelPosition.x, -modelPosition.y, -modelPosition.z);
	worldMatrix *= XMMatrixRotationY(XMConvertToRadians(modelRotation.y));
	worldMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	m_Models[4]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[4]->GetIndexCount(), m_Models[4]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[4]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[5]->GetPosition();
	worldMatrix = XMMatrixTranslation(60.0f, -60.0f, modelPosition.z);

	worldMatrix *= XMMatrixTranslation(-modelPosition.x, -modelPosition.y, -modelPosition.z);
	worldMatrix *= XMMatrixRotationY(XMConvertToRadians(90));
	worldMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	m_Models[5]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[5]->GetIndexCount(), m_Models[5]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[5]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[6]->GetPosition();
	worldMatrix = XMMatrixTranslation(60.0f, -60.0f, -40.0f);

	m_Models[6]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[6]->GetIndexCount(), m_Models[6]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[6]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[7]->GetPosition();
	worldMatrix = XMMatrixTranslation(modelPosition.x, -60.0f, modelPosition.z);

	m_Models[7]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[7]->GetIndexCount(), m_Models[7]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[7]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[8]->GetPosition();
	worldMatrix = XMMatrixTranslation(modelPosition.x, -45.0f, modelPosition.z);

	worldMatrix *= XMMatrixTranslation(-modelPosition.x, -modelPosition.y, -modelPosition.z);
	worldMatrix *= XMMatrixRotationY(XMConvertToRadians(90));
	worldMatrix *= XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z);

	m_Models[8]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[8]->GetIndexCount(), m_Models[8]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[8]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	modelPosition = m_Models[9]->GetPosition();
	worldMatrix = XMMatrixTranslation(-60.0f, -60.0f, -100.0f);

	m_Models[9]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[9]->GetIndexCount(), m_Models[9]->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Models[9]->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

// PA01_2.1_ChangeBackground
bool GraphicsClass::ChangeBackground(float r, float g, float b, float a)
{
	this->b_red = r;
	this->b_green = g;
	this->b_blue = b;
	this->b_alpha = a;

	return true;
}

// PA01_2.2_2.3_ChangeRasterDesc
bool GraphicsClass::ChangeRasterDesc(D3D11_FILL_MODE r_fillmode, D3D11_CULL_MODE r_cullmode)
{
	if (delay > 0)
	{
		return false;
	}

	delay = 10.0f;
	m_D3D->ChangeRasterDesc(r_fillmode, r_cullmode);

	return true;
}

// PA02_3
bool GraphicsClass::ChangeTextureFilter(int mode)
{
	m_TextureShader->ChangeTextureFilter(m_D3D->GetDevice(), mode);

	return true;
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}