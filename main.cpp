#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector3.h"
#include "Matrix4x4.h"


const char kWindowTitle[] = "LE2B_06_オオハシヒロキ";


Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 MakeAffineMatrix;

	MakeAffineMatrix.m[0][0] = scale.x * (1 * std::cos(rotate.y) * std::cos(rotate.z));
	MakeAffineMatrix.m[0][1] = scale.x * std::sin(rotate.z);
	MakeAffineMatrix.m[0][2] = scale.x * -std::sin(rotate.y);
	MakeAffineMatrix.m[0][3] = 0;
	MakeAffineMatrix.m[1][0] = scale.y * -std::sin(rotate.z);
	MakeAffineMatrix.m[1][1] = scale.y * (std::cos(rotate.x) * 1 * std::cos(rotate.z));
	MakeAffineMatrix.m[1][2] = scale.y * std::sin(rotate.x);
	MakeAffineMatrix.m[1][3] = 0;
	MakeAffineMatrix.m[2][0] = scale.z * std::sin(rotate.y);
	MakeAffineMatrix.m[2][1] = scale.z * std::sin(rotate.x);
	MakeAffineMatrix.m[2][2] = scale.z * (std::cos(rotate.x) * std::cos(rotate.y) * 1);
	MakeAffineMatrix.m[2][3] = 0;
	MakeAffineMatrix.m[3][0] = translate.x;
	MakeAffineMatrix.m[3][1] = translate.y;
	MakeAffineMatrix.m[3][2] = translate.z;
	MakeAffineMatrix.m[3][3] = 1;

	return MakeAffineMatrix;
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

		Vector3 scale{ 1.2f, 0.79f, -2.1f };
		Vector3 rotate{ 0.4f, 1.43f, -0.8f };
		Vector3 translate{ 2.7f, -4.15f, 1.57f };

		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

		//MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");
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

