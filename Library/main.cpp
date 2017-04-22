#include "dx.h"

INT WINAPI WinMain(WIN_PARAM)
{
	pWindow pWnd = new Window(800,600); //�E�B���h�E����(����[UINT], ����[UINT]);
	pDX pDx = new DX(pWnd); //DirectX������(�������Ώ�[HWND]);
	pTexture pTxt = new Texture(pDx, "Data/Textures/Absorb.png", 5, 5); //�e�N�X�`���ǂݍ���(�Ǎ���[pDx], �t�@�C����[LPSTR], ��������[UINT], �c������[UINT]);
	pFont pFnt = new Font(pDx, "�l�r�@�S�V�b�N", 10, 30); //�t�H���g�ǂݍ���(�Ǎ���[pDx], �t�H���g��[LPSTR], ����, ����);
	D3DXVECTOR2 Pos = { 100.0f, 100.0f }; //X,Y���W[FLOAT]
	/*���C�����[�v*/
	while (!pWnd->Process() && pDx->Process()) //���b�Z�[�W����(), ��ʃN���A�E�؂�ւ�();
	{
		if (GetKeyDown(VK_UP)) Pos.y -= 1.0f;
		if (GetKeyDown(VK_DOWN)) Pos.y += 1.0f;
		if (GetKeyDown(VK_LEFT)) Pos.x -= 1.0f;
		if (GetKeyDown(VK_RIGHT)) Pos.x += 1.0f;
		pTxt->Draw(Pos.x, Pos.y, 0, 0); //�e�N�X�`���`��(X���W[FLOAT], Y���W[FLOAT], Z���W[FLOAT], �p�^�[��[UINT]);
		pFnt->Draw(0, 0, D3DCOLOR_ARGB( 255, 0, 200, 200), "X:%.2f\nY:%.2f", Pos.x, Pos.y);//
	}
}