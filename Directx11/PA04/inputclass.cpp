#include "inputclass.h"

InputClass::InputClass()
	: m_directInput(nullptr), m_keyboard(nullptr), m_mouse(nullptr), m_mouseX(0), m_mouseY(0), m_deltaX(0), m_deltaY(0) 
{
}

InputClass::InputClass(const InputClass& other) 
{
}

InputClass::~InputClass() 
{
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd) 
{
	HRESULT result;

	// DirectInput 객체 생성
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)) 
	{
		return false;
	}

	// 키보드 디바이스 초기화
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result)) 
	{
		return false;
	}
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)) 
	{
		return false;
	}
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)) 
	{
		return false;
	}
	result = m_keyboard->Acquire();
	if (FAILED(result)) 
	{
		return false;
	}

	// 마우스 디바이스 초기화
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result)) 
	{
		return false;
	}
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)) 
	{
		return false;
	}
	//result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(result)) 
	{
		return false;
	}
	result = m_mouse->Acquire();
	if (FAILED(result)) 
	{
		return false;
	}

	return true;
}

void InputClass::Shutdown() 
{
	// 마우스 디바이스 해제
	if (m_mouse) 
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = nullptr;
	}

	// 키보드 디바이스 해제
	if (m_keyboard) 
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = nullptr;
	}

	// DirectInput 객체 해제
	if (m_directInput) 
	{
		m_directInput->Release();
		m_directInput = nullptr;
	}
}

bool InputClass::Frame() 
{
	// 키보드와 마우스 상태를 읽음
	if (!ReadKeyboard() || !ReadMouse()) 
	{
		return false;
	}

	// 마우스 Delta 값을 처리
	ResetMouseDelta();

	return true;
}

bool InputClass::ReadKeyboard() 
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result)) 
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) 
		{
			m_keyboard->Acquire();
		}
		else 
		{
			return false;
		}
	}

	return true;
}

bool InputClass::ReadMouse() 
{
	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result)) 
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) 
		{
			m_mouse->Acquire();
		}
		else 
		{
			return false;
		}
	}

	return true;
}

void InputClass::ResetMouseDelta() 
{
	// 마우스 이동량 업데이트
	m_deltaX = m_mouseState.lX;
	m_deltaY = m_mouseState.lY;
}

bool InputClass::IsKeyDown(unsigned char key) const 
{
	// 키가 눌렸는지 확인
	return (m_keyboardState[key] & 0x80);
}

void InputClass::GetMouseDelta(int& deltaX, int& deltaY) const 
{
	deltaX = m_deltaX;
	deltaY = m_deltaY;
}
