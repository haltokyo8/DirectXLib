#pragma once
/*[�C���N���[�h�t�@�C��]*/
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <d3dx9.h>
/*[���C�u�����[�t�@�C��]*/
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
/*[�x��]*/
#pragma warning(disable:4996)
/*[�}�N����`]*/
#define WIN_PARAM HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szStr, INT nCmdShow
#define KEY_MAX   256
/*[�N���X]*/
//Window[�N���X]
typedef class Window {
	//���J
	public:
		/*[�����o�[�ϐ�]*/
		HINSTANCE  hInst;           //�C���X�^���X
		WNDCLASSEX wndClass;        //�E�B���h�E�N���X
		LPSTR      Caption;         //�^�C�g��
		UINT       uWidth, uHeight; //�傫��
		HWND       hWnd;            //�n���h��
		MSG        msg;             //���b�Z�[�W
		/*[�����o�[�֐�]*/
		Window(UINT uWidth, UINT uHeight); //�R���X�g���N�^
		
		BOOL Process(VOID); //�v���Z�X
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam); //�E�B���h�E�v���V�[�W��
		
		~Window(VOID); //�f�X�g���N�^
} *pWindow;
//DirectX[�N���X]
typedef class DX {
	/*���J*/
	public:
		/*[�����o�[�ϐ�]*/
		LPDIRECT3D9        pD3d;
		LPDIRECT3DDEVICE9  pDevice;
		LPD3DXSPRITE       pSprite;
		pWindow            pWnd;
		/*[�����o�[�֐�]*/
		DX(pWindow pWnd);  //�R���X�g���N�^
		
		BOOL Process(VOID); //�v���Z�X
		
		~DX(VOID); //�f�X�g���N�^
} *pDX;
//Texture[�N���X]
typedef class Texture {
	private:
		/*[�����o�[�ϐ�]*/
		LPSTR              FileName;
		LPDIRECT3DTEXTURE9 pTexture;
		UINT               uWidth, uHeight;
		UINT               uDivWidth, uDivHeight;
		pDX                pDx;
	public:
		/*[�����o�[�֐�]*/
		Texture(pDX pDx, LPSTR FileName, UINT uDivWidth, UINT uDivHeight);
		
		VOID Draw(FLOAT fPosX, FLOAT fPosY, FLOAT fPosZ, UINT uPattern);
		
		~Texture(VOID);
} *pTexture;
//Font[�N���X]
typedef class Font {
	private:
		LPD3DXFONT    pFont;
		D3DXFONT_DESC logFont;
		UINT          uWidth, uHeight;
		pDX           pDx;
	public:
		Font(pDX pDx, LPSTR FontName, UINT uWidth, UINT uHeight);

		VOID Draw(FLOAT fPosX, FLOAT fPosY, D3DCOLOR rgb, LPSTR String, ...);

		~Font(VOID);
} *pFont;
/*[�֐�]*/
//�L�[���͏�Ԏ擾[�֐�]
BOOL GetKeyDown(UINT uKey);