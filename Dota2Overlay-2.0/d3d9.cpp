
#include "hD3D9.h"
#include "Dota2MemReader.h"


IDirect3D9Ex* dx_Object = NULL;
IDirect3DDevice9Ex* dx_Device = NULL;
D3DPRESENT_PARAMETERS dx_Params;
ID3DXLine* dx_Line;
ID3DXFont* dx_Font = 0;
int fontSize = 50;

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);
int DrawShadowString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);


// Set our current font size 50 default
void setFontSize(INT FontSize) {
	fontSize = FontSize;
	D3DXCreateFont(dx_Device, FontSize, 0, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial", &dx_Font);
}

/*
We require to initialize the D3D drawing, so we require hWnd. Windows identifies each form or application by assigning it a handle or also known as hWnd.
*/
int D3D9Init(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &dx_Object)))
		exit(1);


	ZeroMemory(&dx_Params, sizeof(dx_Params));
	dx_Params.Windowed = TRUE;
	dx_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dx_Params.hDeviceWindow = hWnd;
	dx_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	dx_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	dx_Params.BackBufferWidth = windowWidth;
	dx_Params.BackBufferHeight = windowHeight;
	dx_Params.EnableAutoDepthStencil = TRUE;
	dx_Params.AutoDepthStencilFormat = D3DFMT_D16;
	if (FAILED(dx_Object->CreateDeviceEx(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&dx_Params,
		0,
		&dx_Device)))
		exit(1);
	setFontSize(fontSize);
	return 0;

}


void Render()
{
	int vbe = getVbe();
	if (vbe == 14)
	{
		DrawString((char*)"Visible", overlayX_Pos, overlayY_Pos, 255, 0, 0, dx_Font);
	}
	else if (vbe >= 6 && vbe <= 10)
	{
		DrawString((char*)"Not Visible", overlayX_Pos, overlayY_Pos, 0, 255, 0, dx_Font);
	}
	else
	{
		DrawString((char*)"Waiting", overlayX_Pos, overlayY_Pos, 255, 0, 0, dx_Font);
	}
}

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT ShadowPos;
	ShadowPos.left = x + 1;
	ShadowPos.top = y + 1;
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	ifont->DrawTextA(0, String, strlen(String), &ShadowPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r / 3, g / 3, b / 3));
	ifont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}
int DrawShadowString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT Font;
	Font.left = x;
	Font.top = y;
	RECT Fonts;
	Fonts.left = x + 1;
	Fonts.top = y;
	RECT Fonts1;
	Fonts1.left = x - 1;
	Fonts1.top = y;
	RECT Fonts2;
	Fonts2.left = x;
	Fonts2.top = y + 1;	
	RECT Fonts3;
	Fonts3.left = x;
	Fonts3.top = y - 1;
	ifont->DrawTextA(0, String, strlen(String), &Fonts3, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts2, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts1, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}
