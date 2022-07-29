#include "Line.hpp"
#include "Angel.hpp"
#include <iostream>

Line::Line(float xa, float ya, float xb, float yb, unsigned int t)
    : thickness(t), frameCount(60) {
	auto point0 = Angel::map(xa, ya);
	auto point1 = Angel::map(xb, yb);
	int x0 = point0.x;
	int y0 = point0.y;
	int xl = point1.x;
	int yl = point1.y;

	int delx = std::abs(xl - x0);
	int dely = std::abs(yl - y0);
	int a = 0, b = 0;
	int p = 0;
	a = ((xl - x0) > 0) ? thickness : -thickness;
	b = ((yl - y0) > 0) ? thickness : -thickness;
	int tempx = x0, tempy = y0;
	if (delx > dely) {
		p = 2 * dely - delx;
		for (int i = 0; i <= delx; i += thickness) {
			points.push_back(Angel::demap(x0, y0));
			false_points.push_back(Angel::demap(tempx, tempy));
			x0 += a;
			tempx += a;
			if (p <= 0) {
				p += 2 * dely;
				tempy = y0 + b;
			} else {
				p += 2 * dely - 2 * delx;
				tempy = y0;
				y0 += b;
			}
		}
	} else {
		p = 2 * delx - dely;
		for (int i = 0; i <= dely; i += thickness) {
			points.push_back(Angel::demap(x0, y0));
			false_points.push_back(Angel::demap(tempx, tempy));
			y0 += b;
			tempy += b;
			if (p <= 0) {
				tempx = x0 + a;
				p += 2 * delx;
			} else {
				p += 2 * delx - 2 * dely;
				tempx = x0;
				x0 += a;
			}
		}
	}
}

Line::Line(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2,
           unsigned int t)
    : thickness(t), frameCount(60) {
	points3D.push_back((oglm::vec3(_x1, _y1, _z1)));
	oglm::vec3i pointone = Angel::map(oglm::vec3(_x1, _y1, _z1));
	oglm::vec3i pointtwo = Angel::map(oglm::vec3(_x2, _y2, _z2));
	int x1 = pointone.x;
	int y1 = pointone.y;
	int z1 = pointone.z;
	int x2 = pointtwo.x;
	int y2 = pointtwo.y;
	int z2 = pointtwo.z;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);
	int xs{1}, ys{1}, zs{1};

	if (x2 <= x1)
		xs = -1;

	if (y2 <= y1)
		ys = -1;
	if (z2 <= z1)
		zs = -1;

	// driving axis is X-axis
	if (dx >= dy && dx >= dz) {
		float p1 = 2 * dy - dx;
		float p2 = 2 * dz - dx;
		while (x1 != x2) {
			x1 += xs;
			if (p1 >= 0) {
				y1 += ys;
				p1 -= 2 * dx;
			}
			if (p2 >= 0) {
				z1 += zs;
				p2 -= 2 * dx;
			}
			p1 += 2 * dy;
			p2 += 2 * dz;
			points3D.push_back(Angel::demap(oglm::vec3i(x1, y1, z1)));
		}
	}
	// driving axis is y-axis
	else if (dy >= dx && dy >= dz) {
		float p1 = 2 * dx - dy;
		float p2 = 2 * dz - dy;
		while (y1 != y2) {
			y1 += ys;
			if (p1 >= 0) {
				x1 += xs;
				p1 -= 2 * dy;
			}
			if (p2 >= 0) {
				z1 += zs;
				p2 -= 2 * dy;
			}
			p1 += 2 * dx;
			p2 += 2 * dz;
			points3D.push_back(Angel::demap(oglm::vec3i(x1, y1, z1)));
		}
	} else {
		float p1 = 2 * dy - dz;
		float p2 = 2 * dx - dz;
		while (z1 != z2) {
			z1 += zs;
			if (p1 >= 0) {
				y1 += ys;
				p1 -= 2 * dz;
			}
			if (p2 >= 0) {
				x1 += xs;
				p2 -= 2 * dz;
			}
			p1 += 2 * dy;
			p2 += 2 * dx;
			points3D.push_back(Angel::demap(oglm::vec3i(x1, y1, z1)));
		}
	}
}
void Line::show_points() {
	for (auto &i : points3D) {
		std::cout << i.x << " " << i.y << " " << i.z << std::endl;
	}
}
void Line::draw() {
	for (auto &i : points) {
		Angel::putPixel(i.x, i.y, thickness);
	}
}
void Line::draw3D() {
	for (auto &i : points3D) {
		std::string key = std::to_string(i.x) + ',' + std::to_string(i.y);

		// Angel::putPixel(i.x, i.y, thickness);
		if (i.x >= -0.75f && i.x <= 0.75f && i.y >= -0.75f && i.y <= 0.75f) {
			if (Angel::depth_buffer.find(key) == Angel::depth_buffer.end()) {
				Angel::depth_buffer[key] = i.z;
				Angel::putPixel(i.x, i.y, thickness);
			} else {
				if (i.z >= Angel::depth_buffer[key]) {
		            std::cout << key << std::endl;
					Angel::depth_buffer[key] = i.z;
					Angel::putPixel(i.x, i.y, thickness);
				}
				else{
                    std::cout<<"Not drawing"<<std::endl;

				}
			}
		} else {
			std::cout << "Crossed the border" << std::endl;
		}
	}
}

void Line::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;

	int cur;
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x, points[cur].y, thickness);
	}
	Angel::putPixel(points[points.size() - 1].x, points[points.size() - 1].y,
	                thickness);
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10 + 4) % 2 == 0) {
				Angel::putPixel(points[i].x, points[i].y, thickness);

			} else {
				Angel::putPixel(false_points[i].x, false_points[i].y,
				                thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x, points[cur - 1].y,
				                thickness);
			}
		}
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			stuck = 0;
			i++;
			count = 0;
		} else {
			count++;
			stuck++;
		}
	}
}
void Line::translate(float x, float y) {}
void Line::translate(oglm::vec2 factor) {}
void Line::rotate(float radians, float x, float y) {}
void Line::rotate(float radians, oglm::vec2 factor) {}
void Line::scale(float x, float y) {}
void Line::scale(oglm::vec2 factor) {}
bool Line::isCompleted() { return false; }
void Line::pause() {}
void Line::reset() {}
void Line::increaseSpeed(float speed) {}
void Line::decreaseSpeed(float speed) {}
