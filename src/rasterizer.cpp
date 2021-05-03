#include "rasterizer.h"

Rasterizer::Rasterizer(int w, int h) : w(w), h(h) {
	buffer.resize(w * h);
}

void Rasterizer::clear() {
	std::fill(buffer.begin(), buffer.end(), 0);
}

void Rasterizer::DrawTriangle(VertexArray& verts) {
	std::sort(verts.begin(), verts.end(), [](Vertex a, Vertex b) {
		return a.pos.y < b.pos.y;
	});

	int x0 = verts[0].pos.x, y0 = verts[0].pos.y,
			x1 = verts[1].pos.x, y1 = verts[1].pos.y,
			x2 = verts[2].pos.x, y2 = verts[2].pos.y;
	int dx1 = abs(x1 - x0);
	int sx1 = x0 < x1 ? 1 : -1;
	int dy1 = -abs(y1 - y0);
	int sy1 = y0 < y1 ? 1 : -1;
	int err1 = dx1 + dy1;

	int dx2 = abs(x2 - x0);
	int sx2 = x0 < x2 ? 1 : -1;
	int dy2 = -abs(y1 - y0);
	int sy2 = y0 < y2 ? 1 : -1;
	int err2 = dx2 + dy2;

	int x0_copy = x0, y0_copy = y0;

	while(x0_copy < x2 && y0_copy < y2) {
		Color c1 = lerp(verts[0], verts[1], x0, y0);
		Color c2 = lerp(verts[0], verts[2], x0_copy, y0_copy);

		for(int x = x0; x < x0_copy; x++) {
			int index = x + w * y0;
			if(index >= 0 && index < buffer.size()) {
				buffer[index] = lerp(Vertex(x0, y0, c1), Vertex(x0_copy, y0, c2), x, y0);
			}
		}

		if(err1 * 2 >= dy1) {
			err1 += dy1;
			x0 += sx1;
		}

		if(err1 * 2 <= dx1) {
			err1 += dx1;
			y0 += sy1;
		}

		if(err2 * 2 >= dy2) {
			err2 += dy2;
			x0_copy += sx2;
		}

		if(err2 * 2 <= dx2) {
			err2 += dx2;
			y0_copy += sy2;
		}
	}
}

void Rasterizer::Line(Vertex v1, Vertex v2) {
}

Color lerp(Vertex v1, Vertex v2, int x, int y) {
	u8 r, g, b, a;
	if(v1.pos.y == v2.pos.y) {
		r = v1.col.r + (v2.col.r - v1.col.r) * (x - v1.pos.x) / (v2.pos.x - v1.pos.x);
		g = v1.col.g + (v2.col.g - v1.col.g) * (x - v1.pos.x) / (v2.pos.x - v1.pos.x);
		b = v1.col.b + (v2.col.b - v1.col.b) * (x - v1.pos.x) / (v2.pos.x - v1.pos.x);
		a = v1.col.a + (v2.col.a - v1.col.a) * (x - v1.pos.x) / (v2.pos.x - v1.pos.x);
	} else {
		r = v1.col.r + (v2.col.r - v1.col.r) * (y - v1.pos.y) / (v2.pos.y - v1.pos.y);
		g = v1.col.g + (v2.col.g - v1.col.g) * (y - v1.pos.y) / (v2.pos.y - v1.pos.y);
		b = v1.col.b + (v2.col.b - v1.col.b) * (y - v1.pos.y) / (v2.pos.y - v1.pos.y);
		a = v1.col.a + (v2.col.a - v1.col.a) * (y - v1.pos.y) / (v2.pos.y - v1.pos.y);
	}

	return Color(r, g, b, a);
}