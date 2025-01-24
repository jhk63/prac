////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//////////////
// INCLUDES //
//////////////
#include <dinput.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass {
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();
	bool Frame();

	bool IsKeyDown(unsigned char key) const;
	void GetMouseDelta(int& deltaX, int& deltaY) const;

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ResetMouseDelta();

private:
	IDirectInput8* m_directInput;          // DirectInput 인터페이스
	IDirectInputDevice8* m_keyboard;      // 키보드 디바이스
	IDirectInputDevice8* m_mouse;         // 마우스 디바이스

	unsigned char m_keyboardState[256];   // 키보드 상태
	DIMOUSESTATE m_mouseState;            // 마우스 상태

	int m_mouseX, m_mouseY;               // 마우스 커서 위치
	int m_deltaX, m_deltaY;               // 마우스 이동량(Delta)
};

#endif