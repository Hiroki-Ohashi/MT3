#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LE2B_06_オオハシヒロキ";

struct Matrix4x4 {
	float m[4][4];
};

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 add;
	add.m[0][0] = m1.m[0][0] + m2.m[0][0];
	add.m[0][1] = m1.m[0][1] + m2.m[0][1];
	add.m[0][2] = m1.m[0][2] + m2.m[0][2];
	add.m[0][3] = m1.m[0][3] + m2.m[0][3];
	add.m[1][0] = m1.m[1][0] + m2.m[1][0];
	add.m[1][1] = m1.m[1][1] + m2.m[1][1];
	add.m[1][2] = m1.m[1][2] + m2.m[1][2];
	add.m[1][3] = m1.m[1][3] + m2.m[1][3];
	add.m[2][0] = m1.m[2][0] + m2.m[2][0];
	add.m[2][1] = m1.m[2][1] + m2.m[2][1];
	add.m[2][2] = m1.m[2][2] + m2.m[2][2];
	add.m[2][3] = m1.m[2][3] + m2.m[2][3];
	add.m[3][0] = m1.m[3][0] + m2.m[3][0];
	add.m[3][1] = m1.m[3][1] + m2.m[3][1];
	add.m[3][2] = m1.m[3][2] + m2.m[3][2];
	add.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return add;
}
// 行列の減法
Matrix4x4 subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 subtract;
	subtract.m[0][0] = m1.m[0][0] - m2.m[0][0];
	subtract.m[0][1] = m1.m[0][1] - m2.m[0][1];
	subtract.m[0][2] = m1.m[0][2] - m2.m[0][2];
	subtract.m[0][3] = m1.m[0][3] - m2.m[0][3];
	subtract.m[1][0] = m1.m[1][0] - m2.m[1][0];
	subtract.m[1][1] = m1.m[1][1] - m2.m[1][1];
	subtract.m[1][2] = m1.m[1][2] - m2.m[1][2];
	subtract.m[1][3] = m1.m[1][3] - m2.m[1][3];
	subtract.m[2][0] = m1.m[2][0] - m2.m[2][0];
	subtract.m[2][1] = m1.m[2][1] - m2.m[2][1];
	subtract.m[2][2] = m1.m[2][2] - m2.m[2][2];
	subtract.m[2][3] = m1.m[2][3] - m2.m[2][3];
	subtract.m[3][0] = m1.m[3][0] - m2.m[3][0];
	subtract.m[3][1] = m1.m[3][1] - m2.m[3][1];
	subtract.m[3][2] = m1.m[3][2] - m2.m[3][2];
	subtract.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return subtract;
}
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 Multiply;
	Multiply.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	Multiply.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	Multiply.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	Multiply.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	Multiply.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	Multiply.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	Multiply.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	Multiply.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	Multiply.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	Multiply.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	Multiply.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	Multiply.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	Multiply.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	Multiply.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	Multiply.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	Multiply.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
	return Multiply;
}
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 Inverse;
	float gyaku = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	float gyakusuu = 1 / gyaku;

	Inverse.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * gyakusuu;
	Inverse.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * gyakusuu;
	Inverse.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * gyakusuu;
	Inverse.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * gyakusuu;

	Inverse.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2])* gyakusuu;
	Inverse.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * gyakusuu;
	Inverse.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * gyakusuu;
	Inverse.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * gyakusuu;

	Inverse.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * gyakusuu;

	Inverse.m[2][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][1] = (m.m[0][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][1]) * gyakusuu;
	Inverse.m[2][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * gyakusuu;

	return Inverse;
}
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 Transpose;
	Transpose.m[0][0] = m.m[0][0];
	Transpose.m[0][1] = m.m[1][0];
	Transpose.m[0][2] = m.m[2][0];
	Transpose.m[0][3] = m.m[3][0];
	Transpose.m[1][0] = m.m[0][1];
	Transpose.m[1][1] = m.m[1][1];
	Transpose.m[1][2] = m.m[2][1];
	Transpose.m[1][3] = m.m[3][1];
	Transpose.m[2][0] = m.m[0][2];
	Transpose.m[2][1] = m.m[1][2];
	Transpose.m[2][2] = m.m[2][2];
	Transpose.m[2][3] = m.m[3][2];
	Transpose.m[3][0] = m.m[0][3];
	Transpose.m[3][1] = m.m[1][3];
	Transpose.m[3][2] = m.m[2][3];
	Transpose.m[3][3] = m.m[3][3];
	return Transpose;
}
// 単位行列の作成
Matrix4x4 MakeIndentity4x4() {
	Matrix4x4 MakeIndentity4x4;

	MakeIndentity4x4.m[0][0] = 1;
	MakeIndentity4x4.m[0][1] = 0;
	MakeIndentity4x4.m[0][2] = 0;
	MakeIndentity4x4.m[0][3] = 0;
	MakeIndentity4x4.m[1][0] = 0;
	MakeIndentity4x4.m[1][1] = 1;
	MakeIndentity4x4.m[1][2] = 0;
	MakeIndentity4x4.m[1][3] = 0;
	MakeIndentity4x4.m[2][0] = 0;
	MakeIndentity4x4.m[2][1] = 0;
	MakeIndentity4x4.m[2][2] = 1;
	MakeIndentity4x4.m[2][3] = 0;
	MakeIndentity4x4.m[3][0] = 0;
	MakeIndentity4x4.m[3][1] = 0;
	MakeIndentity4x4.m[3][2] = 0;
	MakeIndentity4x4.m[3][3] = 1;

	return MakeIndentity4x4;
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

	Matrix4x4 m1 = {
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f 
	};

	Matrix4x4 m2 = {
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
	};

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

		Matrix4x4 resultAdd = Add(m1, m2);
		Matrix4x4 resultSubtract = subtract(m1, m2);
		Matrix4x4 resultMultiply = Multiply(m1, m2);
		Matrix4x4 inverseM1 = Inverse(m1);
		Matrix4x4 inverseM2 = Inverse(m2);
		Matrix4x4 transposeM1 = Transpose(m1);
		Matrix4x4 transposeM2 = Transpose(m2);
		Matrix4x4 identity = MakeIndentity4x4();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2, "transposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "identity");

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
