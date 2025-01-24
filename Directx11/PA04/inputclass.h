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
	IDirectInput8* m_directInput;          // DirectInput �������̽�
	IDirectInputDevice8* m_keyboard;      // Ű���� ����̽�
	IDirectInputDevice8* m_mouse;         // ���콺 ����̽�

	unsigned char m_keyboardState[256];   // Ű���� ����
	DIMOUSESTATE m_mouseState;            // ���콺 ����

	int m_mouseX, m_mouseY;               // ���콺 Ŀ�� ��ġ
	int m_deltaX, m_deltaY;               // ���콺 �̵���(Delta)
};

#endif