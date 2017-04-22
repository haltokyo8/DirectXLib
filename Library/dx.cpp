#include "dx.h"
/*[�O���[�o���ϐ�]*/
BOOL bKeys[KEY_MAX];
/*[Window�R���X�g���N�^]*/
Window::Window(UINT uWidth, UINT uHeight)
{
	ZeroMemory(&this->msg, sizeof(this->msg));
	this->uWidth = uWidth;
	this->uHeight = uHeight;
	this->Caption = "�^�C�g��";
	this->wndClass.cbSize = sizeof(this->wndClass);
	this->wndClass.style = CS_HREDRAW | CS_VREDRAW;
	this->wndClass.lpfnWndProc = WndProc;
	this->wndClass.cbClsExtra = 0;
	this->wndClass.cbWndExtra = 0;
	this->wndClass.hInstance = this->hInst;
	this->wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	this->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	this->wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	this->wndClass.lpszMenuName = NULL;
	this->wndClass.lpszClassName = Caption;
	this->wndClass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);

	RegisterClassEx(&this->wndClass);

	this->hWnd = CreateWindow(this->Caption, this->Caption, WS_OVERLAPPEDWINDOW,
		0, 0, this->uWidth, this->uHeight, NULL, NULL, this->hInst, NULL);

	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);
}
/*[Window�f�X�g���N�^]*/
Window::~Window(VOID)
{
	
}
/*[Window�v���V�[�W��]*/
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		bKeys[(CHAR)wParam] = TRUE;
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_KEYUP:
		bKeys[(CHAR)wParam] = FALSE;
		break;
	case WM_SIZE:
		
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
/*[Window�v���Z�X]*/
BOOL Window::Process(VOID)
{
	if (this->msg.message != WM_QUIT)
	{
		while (TRUE)
		{
			if (PeekMessage(&this->msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&this->msg);
				DispatchMessage(&this->msg);
			}
			else
			{
				break;
			}
		}
		return FALSE;
	}

	return TRUE;
}
/*[DX�R���X�g���N�^]*/
DX::DX(pWindow pWnd)
{
	this->pWnd = pWnd;
	//�uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (NULL == (this->pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return;
	}
	//�uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	if (FAILED(this->pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->pWnd->hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &this->pDevice)))
	{
		if (FAILED(this->pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->pWnd->hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &this->pDevice)))
		{
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(this->pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->pWnd->hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &this->pDevice)))
			{
				if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->pWnd->hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &this->pDevice)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return;
				}
			}
		}
	}

	D3DXCreateSprite(this->pDevice, &this->pSprite);
}
/*[DX�f�X�g���N�^]*/
DX::~DX(VOID)
{
	this->pD3d->Release();
	this->pD3d = NULL;
	this->pSprite->Release();
	this->pSprite = NULL;
	this->pDevice->Release();
	this->pDevice = NULL;
}
/*[DX�v���Z�X]*/
BOOL DX::Process(VOID)
{
	pSprite->End();
	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(30, 30, 30), 1.0f, 0);
	pDevice->BeginScene();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	return TRUE;
}
/*[Texture�R���X�g���N�^]*/
Texture::Texture(pDX pDx, LPSTR FileName, UINT uDivWidth, UINT uDivHeight )
{
	HRESULT hr = D3DXCreateTextureFromFileEx(pDx->pDevice, FileName,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, 0, 0, &this->pTexture);
	if (FAILED(hr)) {
		exit(0);
		this->pTexture = NULL;
		return;
	}
	IDirect3DSurface9 * pSurface;
	this->pTexture->GetSurfaceLevel(0, &pSurface);
	D3DSURFACE_DESC SurfaceInfo;
	pSurface->GetDesc(&SurfaceInfo);
	this->uWidth = SurfaceInfo.Width + (16 - (SurfaceInfo.Width % 16)) % 16;
	this->uHeight = SurfaceInfo.Height + (16 - (SurfaceInfo.Height % 16)) % 16;
	pSurface->Release();
	pSurface = NULL;
	this->uDivWidth = uDivWidth;
	this->uDivHeight = uDivHeight;
	this->pDx = pDx;
}
/*[Texture�f�X�g���N�^]*/
Texture::~Texture(VOID)
{
	this->pTexture->Release();
	this->pTexture = NULL;
}
/*[Texture�`��]*/
VOID Texture::Draw(FLOAT fPosX, FLOAT fPosY, FLOAT fPosZ, UINT uPattern)
{
	if (this->pTexture == NULL)
	{
		return;
	}
	RECT rect = {
		(LONG)(this->uWidth / this->uDivWidth * (uPattern % this->uDivWidth)),
		(LONG)(this->uHeight / this->uDivHeight * (uPattern / this->uDivWidth)),
		(LONG)(this->uWidth / this->uDivWidth * (uPattern % this->uDivWidth) + this->uWidth / this->uDivWidth),
		(LONG)(this->uHeight / this->uDivHeight * (uPattern / this->uDivWidth) + this->uHeight / this->uDivHeight)
	};
	D3DXVECTOR3 vec3Center(this->uWidth / this->uDivWidth / 2.0f, this->uHeight / this->uDivHeight / 2.0f, 0);
	D3DXVECTOR3 vec3Position(fPosX, fPosY, fPosZ);
	pDx->pSprite->Draw(this->pTexture, &rect, &vec3Center, &vec3Position, D3DCOLOR_ARGB(255, 255, 255, 255));
}
/*[Font�R���X�g���N�^]*/
Font::Font(pDX pDx, LPSTR FontName, UINT uWidth, UINT uHeight)
{
	//�t�H���g������
	this->logFont.Width = uWidth;
	this->logFont.Height = uHeight;

	this->logFont.Weight = FW_NORMAL;
	this->logFont.MipLevels = 0;
	this->logFont.Italic = FALSE;
	this->logFont.CharSet = SHIFTJIS_CHARSET;
	this->logFont.OutputPrecision = 0;
	this->logFont.Quality = DEFAULT_QUALITY;
	this->logFont.PitchAndFamily = DEFAULT_PITCH || FF_DONTCARE;

	lstrcpy(this->logFont.FaceName, FontName);
	D3DXCreateFontIndirect(pDx->pDevice, &this->logFont, &this->pFont);
	this->pDx = pDx;
}
/*[Font�f�X�g���N�^]*/
Font::~Font(VOID)
{
	this->pFont->Release();
	this->pFont = NULL;
}
/*[Font�`��]*/
VOID Font::Draw(FLOAT fPosX, FLOAT fPosY, D3DCOLOR rgb, LPSTR String, ...)
{
	char newStr[CHAR_MAX];
	va_list args;
	va_start(args, String);
	_vstprintf(newStr, String, args);
	va_end(args);
	RECT rect = { (LONG)fPosX, (LONG)fPosY, (LONG)this->pDx->pWnd->uWidth, (LONG)this->pDx->pWnd->uHeight };
	pFont->DrawText(NULL, newStr, -1, &rect, DT_LEFT | DT_NOCLIP, rgb);
}
/*[�֐�]*/
//�L�[���͏�Ԏ擾[�֐�]
BOOL GetKeyDown(UINT uKey)
{
	return bKeys[uKey];
}