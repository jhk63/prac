///////////////////////////////////////////////////////////////////////////////
// Filename: textclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "textclass.h"


TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;

	for (int i = 0; i < SENTENCE_COUNT; i++)
	{
		m_sentence[i] = 0;
	}
}


TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
}


bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, 
	int screenWidth, int screenHeight, XMMATRIX baseViewMatrix)
{
	bool result;


	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;

	// Create the font object.
	m_Font = new FontClass;
	if(!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, L"./data/fontdata.txt", L"./data/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the sentence.
	for (int i = 0; i < SENTENCE_COUNT; i++)
	{
		result = InitializeSentence(&m_sentence[i], 16, device);
		if (!result)
		{
			return false;
		}
	}

	SetScreenSize(deviceContext);
	SetTitle(deviceContext);
	SetName(deviceContext);
	SetKey(deviceContext);

	return true;
}


void TextClass::Shutdown()
{
	// Release the sentence.
	for (int i = 0; i < SENTENCE_COUNT; i++)
	{
		ReleaseSentence(&m_sentence[i]);
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}


bool TextClass::Render(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX orthoMatrix)
{
	bool result;

	// Draw the sentence.
	for (int i = 0; i < SENTENCE_COUNT; i++)
	{
		result = RenderSentence(deviceContext, m_sentence[i], worldMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	return true;
}


bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for(i=0; i<(*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}


bool TextClass::UpdateSentence(SentenceType* sentence, const char* text, int positionX, int positionY, 
	float red, float green, float blue, ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;


	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		// Release the sentence vertex buffer.
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}

	return;
}


bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, XMMATRIX worldMatrix, 
							   XMMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	XMFLOAT4 pixelColor;
	bool result;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = XMFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, 
		orthoMatrix, m_Font->GetTexture(), pixelColor);
	if(!result)
	{
		false;
	}

	return true;
}

bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char fpsString[16];

	bool result;

	// Truncate the fps to below 10,000.
	if (fps > 9999)
	{
		fps = 9999;
	}

	// Convert the fps integer to string format.
	_itoa_s(fps, tempString, sizeof(tempString), 10);

	// Setup the fps string.
	strcpy_s(fpsString, "Fps: ");
	strcat_s(fpsString, sizeof(fpsString), tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence[0], fpsString, 20, 60, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char cpuString[16];

	bool result;

	// Convert the cpu integer to string format.
	_itoa_s(cpu, tempString, sizeof(tempString), 10);

	// Setup the cpu string.
	strcpy_s(cpuString, "Cpu: ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence[1], cpuString, 20, 80, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetObjectCount(int objects, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char modelString[16];

	bool result;

	_itoa_s(objects, tempString, sizeof(tempString), 10);
	strcpy_s(modelString, "Objects: ");
	strcat_s(modelString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence[2], modelString, 20, 100, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetPolygonCount(int polygons, ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char modelString[16];

	bool result;

	_itoa_s(polygons, tempString, sizeof(tempString), 10);
	strcpy_s(modelString, "Polygons: ");
	strcat_s(modelString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence[3], modelString, 20, 120, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetScreenSize(ID3D11DeviceContext* deviceContext)
{
	char tempString[16];
	char screenString[16];

	bool result;

	_itoa_s(m_screenWidth, tempString, sizeof(tempString), 10);
	strcpy_s(screenString, tempString);

	strcat_s(screenString, " x ");

	_itoa_s(m_screenHeight, tempString, sizeof(tempString), 10);
	strcat_s(screenString, tempString);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence[4], screenString, 20, 140, 1.0f, 1.0f, 0.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetTitle(ID3D11DeviceContext* deviceContext)
{
	char titleString[16];

	bool result;

	strcpy_s(titleString, "Title: Any Farm");

	result = UpdateSentence(m_sentence[5], titleString, 1500, 60, 0.0f, 0.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetName(ID3D11DeviceContext* deviceContext)
{
	char nameString[16];

	bool result;

	strcpy_s(nameString, "B977008 KJH");

	result = UpdateSentence(m_sentence[6], nameString, 1500, 80, 0.0f, 0.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::SetKey(ID3D11DeviceContext* deviceContext)
{
	char keyString[16];

	bool result;

	strcpy_s(keyString, "Move: WASD");

	result = UpdateSentence(m_sentence[7], keyString, 1500, 100, 0.0f, 0.0f, 1.0f, deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}