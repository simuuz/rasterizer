#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdint>

using u8 = uint8_t;
using u32 = uint32_t;

struct Color {
	u8 r,g,b,a;
	Color() : r(0), g(0), b(0), a(0) { }
	Color(u32 col) : r(col >> 24), g(col >> 16), b(col >> 8), a(col & 0xff) { }
	Color(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) { }

	auto operator=(const u32& rhs) {
		r = rhs >> 24;
		g = rhs >> 16;
		b = rhs >> 8;
		a = rhs & 0xff;
	}

	auto operator+(const Color& rhs) {
		return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
	}

	auto operator+=(const Color& rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
	}

	auto operator-(const Color& rhs) {
		return Color(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
	}

	auto operator-=(const Color& rhs) {
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
	}

	auto operator*(const int& rhs) {
		return Color(r * rhs, g * rhs, b * rhs, a * rhs);
	}

	auto operator*=(const int& rhs) {
		r *= rhs;
		g *= rhs;
		b *= rhs;
		a *= rhs;
	}

	auto operator/(const int& rhs) {
		return Color(r / rhs, g / rhs, b / rhs, a / rhs);
	}

	auto operator/=(const int& rhs) {
		r /= rhs;
		g /= rhs;
		b /= rhs;
		a /= rhs;
	}
};

struct Vec2i {
	int x, y;
	Vec2i() : x(0), y(0) { }
	Vec2i(int x, int y) : x(x), y(y) { }

	auto operator+(const Vec2i& rhs) {
		return Vec2i(x + rhs.x, y + rhs.y);
	}

	auto operator+=(const Vec2i& rhs) {
		x += rhs.x;
		y += rhs.y;
	}
};

struct Vertex {
	Vec2i pos;
	Color col;
	Vertex() { }
	Vertex(Vec2i pos) : pos(pos) { }
	Vertex(Vec2i pos, Color col) : pos(pos), col(col) { }
	Vertex(int x, int y, Color col) : pos(x, y), col(col) { }
};

struct VertexArray {
	std::vector<Vertex> v;

	VertexArray(size_t s) { v.resize(s); }

	auto begin() { return v.begin(); }
	auto end() { return v.end(); }

	Vertex& operator[](int i) { return v[i]; }
	Vertex operator[](int i) const { return v[i]; }
};

class Rasterizer {
public:
	Rasterizer(int w, int h);
	void clear();
	void DrawTriangle(VertexArray& verts);
	std::vector<Color> buffer;
private:
	void Line(Vertex v1, Vertex v2);
	int w, h;
};

Color lerp(Vertex v1, Vertex v2, int x, int y);