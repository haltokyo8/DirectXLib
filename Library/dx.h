#pragma once
/*[インクルードファイル]*/
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <d3dx9.h>
/*[ライブラリーファイル]*/
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
/*[警告]*/
#pragma warning(disable:4996)
/*[マクロ定義]*/
#define WIN_PARAM HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szStr, INT nCmdShow
#define KEY_MAX   256
/*[クラス]*/
//Window[クラス]
typedef class Window {
	//公開
	public:
		/*[メンバー変数]*/
		HINSTANCE  hInst;           //インスタンス
		WNDCLASSEX wndClass;        //ウィンドウクラス
		LPSTR      Caption;         //タイトル
		UINT       uWidth, uHeight; //大きさ
		HWND       hWnd;            //ハンドル
		MSG        msg;             //メッセージ
		/*[メンバー関数]*/
		Window(UINT uWidth, UINT uHeight); //コンストラクタ
		
		BOOL Process(VOID); //プロセス
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam); //ウィンドウプロシージャ
		
		~Window(VOID); //デストラクタ
} *pWindow;
//DirectX[クラス]
typedef class DX {
	/*公開*/
	public:
		/*[メンバー変数]*/
		LPDIRECT3D9        pD3d;
		LPDIRECT3DDEVICE9  pDevice;
		LPD3DXSPRITE       pSprite;
		pWindow            pWnd;
		/*[メンバー関数]*/
		DX(pWindow pWnd);  //コンストラクタ
		
		BOOL Process(VOID); //プロセス
		
		~DX(VOID); //デストラクタ
} *pDX;
//Texture[クラス]
typedef class Texture {
	private:
		/*[メンバー変数]*/
		LPSTR              FileName;
		LPDIRECT3DTEXTURE9 pTexture;
		UINT               uWidth, uHeight;
		UINT               uDivWidth, uDivHeight;
		pDX                pDx;
	public:
		/*[メンバー関数]*/
		Texture(pDX pDx, LPSTR FileName, UINT uDivWidth, UINT uDivHeight);
		
		VOID Draw(FLOAT fPosX, FLOAT fPosY, FLOAT fPosZ, UINT uPattern);
		
		~Texture(VOID);
} *pTexture;
//Font[クラス]
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
/*[関数]*/
//キー入力状態取得[関数]
BOOL GetKeyDown(UINT uKey);