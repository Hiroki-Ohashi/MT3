#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <assert.h>
#include<Matrix4x4.h>
#include <imGui.h>
#include <Vector3.h>
#include <algorithm>

const char kWindowTitle[] = "LE2B_06_オオハシヒロキ";

struct Sphere {
	Vector3 center;
	float radius;
};

struct Line {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};
struct Ray {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};
struct Segment {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

struct Plane {
	Vector3 normal;//法線
	float distance;//距離
};

struct TriAngle {
	Vector3 vertices[3];//頂点
};

struct AABB {
	Vector3 min;//!<最小点
	Vector3 max;//!<最大点
};

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	return Vector3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
Vector3 Subtract(const Vector3& v1, const float& f1) {
	return Vector3{ v1.x - f1, v1.y - f1, v1.z - f1 };
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

float Length(const Vector3& v) {
	return sqrtf(Dot(v, v));
}
Vector3 Transforme(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// 回転行列
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 m4;
	m4.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
		m1.m[0][3] * m2.m[3][0];
	m4.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
		m1.m[0][3] * m2.m[3][1];
	m4.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
		m1.m[0][3] * m2.m[3][2];
	m4.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
		m1.m[0][3] * m2.m[3][3];

	m4.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
		m1.m[1][3] * m2.m[3][0];
	m4.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
		m1.m[1][3] * m2.m[3][1];
	m4.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
		m1.m[1][3] * m2.m[3][2];
	m4.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
		m1.m[1][3] * m2.m[3][3];

	m4.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
		m1.m[2][3] * m2.m[3][0];
	m4.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
		m1.m[2][3] * m2.m[3][1];
	m4.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
		m1.m[2][3] * m2.m[3][2];
	m4.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
		m1.m[2][3] * m2.m[3][3];

	m4.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
		m1.m[3][3] * m2.m[3][0];
	m4.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
		m1.m[3][3] * m2.m[3][1];
	m4.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
		m1.m[3][3] * m2.m[3][2];
	m4.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
		m1.m[3][3] * m2.m[3][3];
	return m4;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	return { v.x * scalar,v.y * scalar,v.z * scalar };
}
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 Cross;
	Cross.x = v1.y * v2.z - v1.z * v2.y;
	Cross.y = v1.z * v2.x - v1.x * v2.z;
	Cross.z = v1.x * v2.y - v1.y * v2.x;
	return Cross;
}
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfwidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);
	Vector3 worldVerticles[2];
	Vector3 screenVerticles[2];
	Vector3 ndcVertices;
	//横
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		worldVerticles[0] = { kGridEvery * xIndex - kGridHalfwidth,0.0f,kGridHalfwidth };
		worldVerticles[1] = { kGridEvery * xIndex - kGridHalfwidth,0.0f,-kGridHalfwidth };
		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertices = Transforme(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Transforme(ndcVertices, viewportMatrix);
		}
		Novice::DrawLine((int)screenVerticles[0].x, (int)screenVerticles[0].y, (int)screenVerticles[1].x, (int)screenVerticles[1].y, 0x0000FF);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		worldVerticles[0] = { kGridHalfwidth,0.0f,kGridEvery * zIndex - kGridHalfwidth };
		worldVerticles[1] = { -kGridHalfwidth,0.0f, kGridEvery * zIndex - kGridHalfwidth };

		for (uint32_t i = 0; i < 2; ++i) {
			ndcVertices = Transforme(worldVerticles[i], viewProjectionMatrix);
			screenVerticles[i] = Transforme(ndcVertices, viewportMatrix);
		}
		Novice::DrawLine((int)screenVerticles[0].x, (int)screenVerticles[0].y, (int)screenVerticles[1].x, (int)screenVerticles[1].y, 0x000000FF);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {
	const uint32_t kSubDivision = 30;
	const float kLonEvery = 2.0f * (float)M_PI / float(kSubDivision);
	const float kLatEvery = (float)M_PI / float(kSubDivision);

	for (uint32_t latIndex = 0; latIndex < kSubDivision; ++latIndex) {
		float lat = -1.0f * (float)M_PI / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			Vector3 a, b, c;
			a = { sphere.radius * std::cosf(lat) * std::cosf(lon), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			a = Add(a, sphere.center);
			b = { sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon) };
			b = Add(b, sphere.center);
			c = { sphere.radius * std::cosf(lat) * std::cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) };
			c = Add(c, sphere.center);

			a = Transforme(a, viewProjectionMatrix);
			a = Transforme(a, viewportMatrix);
			b = Transforme(b, viewProjectionMatrix);
			b = Transforme(b, viewportMatrix);
			c = Transforme(c, viewProjectionMatrix);
			c = Transforme(c, viewportMatrix);


			Novice::DrawLine(
				int(a.x), int(a.y),
				int(b.x), int(b.y),
				color
			);

			Novice::DrawLine(
				int(a.x), int(a.y),
				int(c.x), int(c.y),
				color
			);

		}
	}

};

Vector3 Normalize(const Vector3& v1) {
	Vector3 Result = v1;
	float length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	assert(length != 0);
	Result.x /= length;
	Result.y /= length;
	Result.z /= length;
	return Result;
}

//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result = Multiply(Dot(v1, Normalize(v2)), Normalize(v2));
	return result;
}
//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	float length = sqrt(segment.diff.x * segment.diff.x + segment.diff.y * segment.diff.y + segment.diff.z * segment.diff.z);
	Vector3 normaliseSegment = { segment.diff.x / length,segment.diff.y / length,segment.diff.z / length };

	float distance = Dot(Subtract(point, segment.origin), normaliseSegment);
	distance = std::clamp(distance, 0.0f, length);
	Vector3 proj = Multiply(distance, normaliseSegment);
	return Add(segment.origin, proj);
};
Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transforme(Transforme(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}
bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(Subtract(s2.center, s1.center));
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& s1, const Plane& p1) {
	float distance = Dot(Normalize(p1.normal), Subtract(s1.center, p1.distance));
	if (std::abs(distance) <= s1.radius) {
		return true;
	}
	else {
		return false;
	}
}
bool IsCollision(const Segment& segment, const Plane& plane)
{
	float dot = Dot(segment.diff, plane.normal);
	//垂直=平行であるので、衝突しているはずがない
	if (dot == 0.0f) {
		return false;
	}
	//tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal) / dot);
	//tの値と線の種類によって衝突しているかを判定
	if (0.0f <= t && t <= 1.0f) {
		return true;
	}
	return false;
}

void DrawTriAngle(const TriAngle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color)
{
	Vector3 verticle[3];
	for (int i = 0; i < 3; i++) {
		verticle[i] = Transforme(Transforme(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle((int)verticle[0].x, (int)verticle[0].y, (int)verticle[1].x, (int)verticle[1].y, (int)verticle[2].x, (int)verticle[2].y, color, kFillModeWireFrame);
}
bool IsCollision(const Segment& segment, const TriAngle& triangle)
{
	//TriAngleから面を作る
	Plane plane{};
	plane.normal =
		Normalize(
			Cross(
				Subtract(triangle.vertices[1], triangle.vertices[0]),
				Subtract(triangle.vertices[2], triangle.vertices[1])
			)
		);

	plane.distance = Dot(triangle.vertices[0], plane.normal);

	float dot = Dot(plane.normal, segment.diff);

	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (0.0f < t && t < 1.0f) {
		Vector3 p = Add(segment.origin, Multiply(t, segment.diff));


		Vector3 cross01 = Cross(
			Subtract(triangle.vertices[1], triangle.vertices[0]),
			Subtract(p, triangle.vertices[1])
		);
		Vector3 cross12 = Cross(
			Subtract(triangle.vertices[2], triangle.vertices[1]),
			Subtract(p, triangle.vertices[2])
		);
		Vector3 cross20 = Cross(
			Subtract(triangle.vertices[0], triangle.vertices[2]),
			Subtract(p, triangle.vertices[0])
		);


		if (Dot(cross01, plane.normal) >= 0.0f &&
			Dot(cross12, plane.normal) >= 0.0f &&
			Dot(cross20, plane.normal) >= 0.0f) {
			return true;
		}

	}

	return false;
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 point[8];
	point[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	point[1] = { aabb.min.x, aabb.min.y, aabb.max.z };
	point[2] = { aabb.min.x, aabb.max.y, aabb.min.z };
	point[3] = { aabb.max.x, aabb.min.y, aabb.min.z };
	point[4] = { aabb.max.x, aabb.max.y, aabb.min.z };
	point[5] = { aabb.min.x, aabb.max.y, aabb.max.z };
	point[6] = { aabb.max.x, aabb.min.y, aabb.max.z };
	point[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

	Vector3 screenpoint[8]{};
	for (int i = 0; i < 8; i++) {
		point[i] = Transforme(point[i], viewProjectionMatrix);
		screenpoint[i] = Transforme(point[i], viewportMatrix);
	}
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[1].x), int(screenpoint[1].y), color);
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[2].x), int(screenpoint[2].y), color);
	Novice::DrawLine(int(screenpoint[0].x), int(screenpoint[0].y), int(screenpoint[3].x), int(screenpoint[3].y), color);

	Novice::DrawLine(int(screenpoint[1].x), int(screenpoint[1].y), int(screenpoint[5].x), int(screenpoint[5].y), color);
	Novice::DrawLine(int(screenpoint[1].x), int(screenpoint[1].y), int(screenpoint[6].x), int(screenpoint[6].y), color);

	Novice::DrawLine(int(screenpoint[2].x), int(screenpoint[2].y), int(screenpoint[4].x), int(screenpoint[4].y), color);
	Novice::DrawLine(int(screenpoint[2].x), int(screenpoint[2].y), int(screenpoint[5].x), int(screenpoint[5].y), color);

	Novice::DrawLine(int(screenpoint[3].x), int(screenpoint[3].y), int(screenpoint[4].x), int(screenpoint[4].y), color);
	Novice::DrawLine(int(screenpoint[3].x), int(screenpoint[3].y), int(screenpoint[6].x), int(screenpoint[6].y), color);

	Novice::DrawLine(int(screenpoint[4].x), int(screenpoint[4].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
	Novice::DrawLine(int(screenpoint[5].x), int(screenpoint[5].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
	Novice::DrawLine(int(screenpoint[6].x), int(screenpoint[6].y), int(screenpoint[7].x), int(screenpoint[7].y), color);
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {

		return true;

	}

	return false;

}

	return false;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	float A;
	Matrix4x4 Inverse;
	A = { m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] };

	float B = 1 / A;
	Inverse.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) * B;
	Inverse.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) * B;

	Inverse.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) * B;
	Inverse.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) * B;
	Inverse.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) * B;

	Inverse.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) * B;
	Inverse.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) * B;
	Inverse.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) * B;
	Inverse.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) * B;

	Inverse.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) * B;
	Inverse.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) * B;
	Inverse.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) * B;
	Inverse.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) * B;

	return Inverse;
}
// X軸周りの回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 MakeRotateXMatrix;
	MakeRotateXMatrix.m[0][0] = 1;
	MakeRotateXMatrix.m[0][1] = 0;
	MakeRotateXMatrix.m[0][2] = 0;
	MakeRotateXMatrix.m[0][3] = 0;

	MakeRotateXMatrix.m[1][0] = 0;
	MakeRotateXMatrix.m[1][1] = std::cos(radian);
	MakeRotateXMatrix.m[1][2] = std::sin(radian);
	MakeRotateXMatrix.m[1][3] = 0;

	MakeRotateXMatrix.m[2][0] = 0;
	MakeRotateXMatrix.m[2][1] = -std::sin(radian);
	MakeRotateXMatrix.m[2][2] = std::cos(radian);
	MakeRotateXMatrix.m[2][3] = 0;

	MakeRotateXMatrix.m[3][0] = 0;
	MakeRotateXMatrix.m[3][1] = 0;
	MakeRotateXMatrix.m[3][2] = 0;
	MakeRotateXMatrix.m[3][3] = 1;

	return MakeRotateXMatrix;
}
// Y軸周りの回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 MakeRotateYMatrix;
	MakeRotateYMatrix.m[0][0] = std::cos(radian);
	MakeRotateYMatrix.m[0][1] = 0;
	MakeRotateYMatrix.m[0][2] = -std::sin(radian);
	MakeRotateYMatrix.m[0][3] = 0;

	MakeRotateYMatrix.m[1][0] = 0;
	MakeRotateYMatrix.m[1][1] = 1;
	MakeRotateYMatrix.m[1][2] = 0;
	MakeRotateYMatrix.m[1][3] = 0;

	MakeRotateYMatrix.m[2][0] = std::sin(radian);
	MakeRotateYMatrix.m[2][1] = 0;
	MakeRotateYMatrix.m[2][2] = std::cos(radian);
	MakeRotateYMatrix.m[2][3] = 0;

	MakeRotateYMatrix.m[3][0] = 0;
	MakeRotateYMatrix.m[3][1] = 0;
	MakeRotateYMatrix.m[3][2] = 0;
	MakeRotateYMatrix.m[3][3] = 1;

	return MakeRotateYMatrix;
}
// Z軸周りの回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 MakeRotateZMatrix;
	MakeRotateZMatrix.m[0][0] = std::cos(radian);
	MakeRotateZMatrix.m[0][1] = std::sin(radian);
	MakeRotateZMatrix.m[0][2] = 0;
	MakeRotateZMatrix.m[0][3] = 0;

	MakeRotateZMatrix.m[1][0] = -std::sin(radian);
	MakeRotateZMatrix.m[1][1] = std::cos(radian);
	MakeRotateZMatrix.m[1][2] = 0;
	MakeRotateZMatrix.m[1][3] = 0;

	MakeRotateZMatrix.m[2][0] = 0;
	MakeRotateZMatrix.m[2][1] = 0;
	MakeRotateZMatrix.m[2][2] = 1;
	MakeRotateZMatrix.m[2][3] = 0;

	MakeRotateZMatrix.m[3][0] = 0;
	MakeRotateZMatrix.m[3][1] = 0;
	MakeRotateZMatrix.m[3][2] = 0;
	MakeRotateZMatrix.m[3][3] = 1;

	return MakeRotateZMatrix;
}
//  アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 MakeAffineMatrix;

	MakeRotateXMatrix(rotate.x);
	MakeRotateYMatrix(rotate.y);
	MakeRotateZMatrix(rotate.z);

	Matrix4x4 XYZ = Multiply(
		MakeRotateXMatrix(rotate.x),
		Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

	MakeAffineMatrix.m[0][0] = XYZ.m[0][0] * scale.x;
	MakeAffineMatrix.m[0][1] = XYZ.m[0][1] * scale.x;
	MakeAffineMatrix.m[0][2] = XYZ.m[0][2] * scale.x;
	MakeAffineMatrix.m[0][3] = 0;

	MakeAffineMatrix.m[1][0] = XYZ.m[1][0] * scale.y;
	MakeAffineMatrix.m[1][1] = XYZ.m[1][1] * scale.y;
	MakeAffineMatrix.m[1][2] = XYZ.m[1][2] * scale.y;
	MakeAffineMatrix.m[1][3] = 0;

	MakeAffineMatrix.m[2][0] = XYZ.m[2][0] * scale.z;
	MakeAffineMatrix.m[2][1] = XYZ.m[2][1] * scale.z;
	MakeAffineMatrix.m[2][2] = XYZ.m[2][2] * scale.z;
	MakeAffineMatrix.m[2][3] = 0;

	MakeAffineMatrix.m[3][0] = translate.x;
	MakeAffineMatrix.m[3][1] = translate.y;
	MakeAffineMatrix.m[3][2] = translate.z;
	MakeAffineMatrix.m[3][3] = 1;

	return MakeAffineMatrix;
}
//1.透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 MakePerspectiveFovMatrix;
	MakePerspectiveFovMatrix.m[0][0] = 1 / aspectRatio * (1 / std::tan(fovY / 2));
	MakePerspectiveFovMatrix.m[0][1] = 0.0f;
	MakePerspectiveFovMatrix.m[0][2] = 0.0f;
	MakePerspectiveFovMatrix.m[0][3] = 0.0f;

	MakePerspectiveFovMatrix.m[1][0] = 0.0f;
	MakePerspectiveFovMatrix.m[1][1] = 1 / std::tan(fovY / 2);
	MakePerspectiveFovMatrix.m[1][2] = 0.0f;
	MakePerspectiveFovMatrix.m[1][3] = 0.0f;

	MakePerspectiveFovMatrix.m[2][0] = 0.0f;
	MakePerspectiveFovMatrix.m[2][1] = 0.0f;
	MakePerspectiveFovMatrix.m[2][2] = farClip / (farClip - nearClip);
	MakePerspectiveFovMatrix.m[2][3] = 1.0f;

	MakePerspectiveFovMatrix.m[3][0] = 0.0f;
	MakePerspectiveFovMatrix.m[3][1] = 0.0f;
	MakePerspectiveFovMatrix.m[3][2] = -(farClip * nearClip) / (nearClip - farClip);
	MakePerspectiveFovMatrix.m[3][3] = 0.0f;

	return MakePerspectiveFovMatrix;
}
//2.正射影行列
Matrix4x4 MakOrthographicMatrix(float left, float right, float top, float bottom, float nearClip, float farClip) {
	Matrix4x4 MakOrthographicMatrix;
	MakOrthographicMatrix.m[0][0] = 2 / (right - left);
	MakOrthographicMatrix.m[0][1] = 0;
	MakOrthographicMatrix.m[0][2] = 0;
	MakOrthographicMatrix.m[0][3] = 0;

	MakOrthographicMatrix.m[1][0] = 0;
	MakOrthographicMatrix.m[1][1] = 2 / (top - bottom);
	MakOrthographicMatrix.m[1][2] = 0;
	MakOrthographicMatrix.m[1][3] = 0;

	MakOrthographicMatrix.m[2][0] = 0;
	MakOrthographicMatrix.m[2][1] = 0;
	MakOrthographicMatrix.m[2][2] = 1 / (farClip - nearClip);
	MakOrthographicMatrix.m[2][3] = 0;

	MakOrthographicMatrix.m[3][0] = (left - right) / (left - right);
	MakOrthographicMatrix.m[3][1] = (top + bottom) / (bottom - top);
	MakOrthographicMatrix.m[3][2] = farClip / (nearClip - farClip);
	MakOrthographicMatrix.m[3][3] = 1;

	return MakOrthographicMatrix;
}
//3.ビューポート変換行
Matrix4x4 MakeViewPortMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 MakeViewportMatrix;
	MakeViewportMatrix.m[0][0] = width / 2;
	MakeViewportMatrix.m[0][1] = 0;
	MakeViewportMatrix.m[0][2] = 0;
	MakeViewportMatrix.m[0][3] = 0;

	MakeViewportMatrix.m[1][0] = 0;
	MakeViewportMatrix.m[1][1] = -height / 2;
	MakeViewportMatrix.m[1][2] = 0;
	MakeViewportMatrix.m[1][3] = 0;

	MakeViewportMatrix.m[2][0] = 0;
	MakeViewportMatrix.m[2][1] = 0;
	MakeViewportMatrix.m[2][2] = maxDepth - minDepth;
	MakeViewportMatrix.m[2][3] = 0;

	MakeViewportMatrix.m[3][0] = (width / 2) + left;
	MakeViewportMatrix.m[3][1] = (height / 2) + top;
	MakeViewportMatrix.m[3][2] = minDepth;
	MakeViewportMatrix.m[3][3] = 1;

	return MakeViewportMatrix;
}



Vector3 v1{ 1.2f,-3.9f,2.5f };
Vector3 v2{ 2.8f,0.4f,-1.3f };
Vector3 cross = Cross(v1, v2);
Vector3 screenVertices[3];


static const int kRowHeight = 20;
static const int kColumnWindth = 60;
static const int kColumWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWindth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumWidth * 3, y, "%s", label);
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 rotate{};
	Vector3 translate{ };
	Vector3 cameraPosition{ 0.0f,0.0f,10.0f };
	Vector3 cameraRotate{ 0.1f,0.0f,0.0f };
	Vector3 cameraTranslate{ 0.0f,1.0f,-6.49f };

	Sphere sphere = { 0.0f,0.0f, 0.0f, 1.0f };
	Vector3 kLoccalVerices[3];
	kLoccalVerices[0] = { 0.0f,0.0f,0.0f };
	kLoccalVerices[1] = { 1.0f,1.0f,0.0f };
	kLoccalVerices[2] = { -1.0f,1.0f,0.0f };

	Sphere sphere1 = { 0.0f,0.0f, 0.0f, 0.5f };

	Sphere sphere2 = { 2.0f,0.0f, 0.0f, 0.5f };

	Plane plane = { {0.0f,1.0f,0.0f},1.0f };

	Segment segment{ {0.0f,0.0f,0.0f},{1.0f,1.0f,0.0f} };
	int Color = WHITE;

	TriAngle triangle;
	triangle.vertices[0] = { -1.0f, 0.0f, 0.0f };
	triangle.vertices[1] = { 0.0f, 1.0f, 0.0f };
	triangle.vertices[2] = { 1.0f, 0.0f, 0.0f };

	AABB aabb1{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};

	AABB aabb2{
	.min{0.2f,-0.5f,-0.5f},
	.max{1.0f,1.0f,1.0f},
	};

	/*Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };
	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);
	Sphere pointSphere{ point,0.01f };
	Sphere closestPointSphere{ closestPoint,0.01f };*/

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


		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
		Matrix4x4 WorldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewPortMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("segment diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("segment origin", &segment.origin.x, 0.01f);

		ImGui::DragFloat3("AABB1min", &aabb1.min.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB1max", &aabb1.max.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB2min", &aabb2.min.x, 0.1f, -1.0f, 5.0f);
		ImGui::DragFloat3("AABB2max", &aabb2.max.x, 0.1f, -1.0f, 5.0f);
		if (IsCollision(aabb1, aabb2) == true) {
			Color = RED;
		}
		else {
			Color = WHITE;
		}
		ImGui::End();
		//	plane.normal = Normalize(plane.normal);


			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			//
		DrawGrid(WorldViewProjectionMatrix, viewportMatrix);
		DrawAABB(aabb1, WorldViewProjectionMatrix, viewportMatrix, Color);
		DrawAABB(aabb2, WorldViewProjectionMatrix, viewportMatrix, WHITE);


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