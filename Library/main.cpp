#include "dx.h"

INT WINAPI WinMain(WIN_PARAM)
{
	pWindow pWnd = new Window(800,600); //ウィンドウ生成(横幅[UINT], 高さ[UINT]);
	pDX pDx = new DX(pWnd); //DirectX初期化(初期化対象[HWND]);
	pTexture pTxt = new Texture(pDx, "Data/Textures/Absorb.png", 5, 5); //テクスチャ読み込み(読込先[pDx], ファイル名[LPSTR], 横分割数[UINT], 縦分割数[UINT]);
	pFont pFnt = new Font(pDx, "ＭＳ　ゴシック", 10, 30); //フォント読み込み(読込先[pDx], フォント名[LPSTR], 横幅, 高さ);
	D3DXVECTOR2 Pos = { 100.0f, 100.0f }; //X,Y座標[FLOAT]
	/*メインループ*/
	while (!pWnd->Process() && pDx->Process()) //メッセージ処理(), 画面クリア・切り替え();
	{
		if (GetKeyDown(VK_UP)) Pos.y -= 1.0f;
		if (GetKeyDown(VK_DOWN)) Pos.y += 1.0f;
		if (GetKeyDown(VK_LEFT)) Pos.x -= 1.0f;
		if (GetKeyDown(VK_RIGHT)) Pos.x += 1.0f;
		pTxt->Draw(Pos.x, Pos.y, 0, 0); //テクスチャ描画(X座標[FLOAT], Y座標[FLOAT], Z座標[FLOAT], パターン[UINT]);
		pFnt->Draw(0, 0, D3DCOLOR_ARGB( 255, 0, 200, 200), "X:%.2f\nY:%.2f", Pos.x, Pos.y);//
	}
}