#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector3.h"
#include "Matrix4x4.h"


const char kWindowTitle[] = "LE2B_06_オオハシヒロキ";

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 mom;
	mom.m[0][0] = 2 / (right - left);
	mom.m[0][1] = 0;
	mom.m[0][2] = 0;
	mom.m[0][3] = 0;

	mom.m[1][0] = 0;
	mom.m[1][1] = 2 / (top - bottom);
	mom.m[1][2] = 0;
	mom.m[1][3] = 0;

	mom.m[2][0] = 0;
	mom.m[2][1] = 0;
	mom.m[2][2] = 1 / (farClip - nearClip);
	mom.m[2][3] = 0;

	mom.m[3][0] = (left + right) / (left - right);
	mom.m[3][1] = (top + bottom) / (bottom - top);
	mom.m[3][2] = nearClip / (nearClip - farClip);
	mom.m[3][3] = 1;
	return mom;
}
// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 mvm;
	mvm.m[0][0] = width / 2;
	mvm.m[0][1] = 0;
	mvm.m[0][2] = 0;
	mvm.m[0][3] = 0;

	mvm.m[1][0] = 0;
	mvm.m[1][1] = -height / 2;
	mvm.m[1][2] = 0;
	mvm.m[1][3] = 0;

	mvm.m[2][0] = 0;
	mvm.m[2][1] = 0;
	mvm.m[2][2] = maxDepth - minDepth;
	mvm.m[2][3] = 0;

	mvm.m[3][0] = left + (width / 2);
	mvm.m[3][1] = top + (height / 2);
	mvm.m[3][2] = minDepth;
	mvm.m[3][3] = 1;
	return mvm;
}

// 透視投影行列
Matrix4x4 MakePerspectiveMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 mpm;
	mpm.m[0][0] = 1 / aspectRatio * (1 / std::tan(fovY / 2));
	mpm.m[0][1] = 0;
	mpm.m[0][2] = 0;
	mpm.m[0][3] = 0;

	mpm.m[1][0] = 0;
	mpm.m[1][1] = 1 / std::tan(fovY / 2);
	mpm.m[1][2] = 0;
	mpm.m[1][3] = 0;

	mpm.m[2][0] = 0;
	mpm.m[2][1] = 0;
	mpm.m[2][2] = farClip / (farClip - nearClip);
	mpm.m[2][3] = 1;

	mpm.m[3][0] = 0;
	mpm.m[3][1] = 0;
	mpm.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	mpm.m[3][3] = 0;
	return mpm;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column], label);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 orthographicMatrix =
			MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
		Matrix4x4 perspectiveMatrix =
			MakePerspectiveMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
		Matrix4x4 viewportMatrix =
			MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveMatrix, "perspectiveMatrix");
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

