// #include "Shape2D.hpp"
#include "Angel.hpp"
#include "Cube.hpp"
#include "Line.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <oglm.hpp>
#include <transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(unsigned int length, unsigned int thickness) : thickness(thickness) {
	points.push_back(oglm::vec3(-0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, -0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, -0.5f));
	points.push_back(oglm::vec3(-0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, -0.5f, 0.5f));
	points.push_back(oglm::vec3(0.5f, 0.5f, 0.5f));
	points.push_back(oglm::vec3(-0.5f, 0.5f, 0.5f));

	indices.push_back(oglm::vec2i(0, 1));
	indices.push_back(oglm::vec2i(1, 2));
	indices.push_back(oglm::vec2i(2, 3));
	indices.push_back(oglm::vec2i(0, 3));

	indices.push_back(oglm::vec2i(0, 4));
	indices.push_back(oglm::vec2i(1, 5));
	indices.push_back(oglm::vec2i(2, 6));
	indices.push_back(oglm::vec2i(3, 7));

	indices.push_back(oglm::vec2i(4, 5));
	indices.push_back(oglm::vec2i(5, 6));
	indices.push_back(oglm::vec2i(6, 7));
	indices.push_back(oglm::vec2i(7, 4));
	// initializing depth buffer
}

void Cube::animate() {}
void Cube::rasterize() {
	float offset = 0.07f;
	for (auto &i : indices) {
		float x0 = points[i.x].x;
		float y0 = points[i.x].y;
		float z0 = points[i.x].z;
		float x1 = points[i.y].x;
		float y1 = points[i.y].y;
		float z1 = points[i.y].z;
		if (x0 == -x1) {
			float temp = y0;
			while (temp < 0.5) {
				Angel::vertexBuffer.push_back(oglm::vec3(x0, temp, z0));
				Angel::vertexBuffer.push_back(oglm::vec3(x1, temp, z1));
				temp += offset;
			}
			temp = z0;
			while (temp < 0.5) {
				Angel::vertexBuffer.push_back(oglm::vec3(x0, y0, temp));
				Angel::vertexBuffer.push_back(oglm::vec3(x1, y1, temp));
				temp += offset;
			} }
		if (z0 == -z1) {
			float temp = y0;
			while (temp < 0.5) {
				Angel::vertexBuffer.push_back(oglm::vec3(x0, temp, z0));
				Angel::vertexBuffer.push_back(oglm::vec3(x1, temp, z1));
				temp += offset;
			}
		}
	}
}

void Cube::load() {
	for (auto &i : indices) {
		float x0 = points[i.x].x;
		float y0 = points[i.x].y;
		float z0 = points[i.x].z;
		float x1 = points[i.y].x;
		float y1 = points[i.y].y;
		float z1 = points[i.y].z;
		Angel::vertexBuffer.push_back(oglm::vec3(x0, y0, z0));
		Angel::vertexBuffer.push_back(oglm::vec3(x1, y1, z1));
	}
	rasterize();
}

void Cube::translate(float x, float y, float z) {}

void Cube::translate(oglm::vec3f factor) {
	oglm::mat4 trans_mat = oglm::translate(factor);
	for (auto &i : points) {
		oglm::vec4f v(i.x, i.y, i.z, 1);
		v = trans_mat * v;
		i = oglm::vec3f(v.x, v.y, v.z);
	}
}

void Cube::rotate(float degree, float x, float y, float z) {}
void Cube::rotate(float degree, oglm::vec3 factor) {
	oglm::mat4 scal = oglm::scale(oglm::vec3(1.0f, 1.0f, 1.0f));
	oglm::mat4 trans = oglm::translate(oglm::vec3(0.0f, 0.0f, 0.0f));
	oglm::mat4 rot = oglm::rotate(30.0f, oglm::vec3(0.0f, 1.0f, 0.0f));
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = trans * rot * scal * v;
		drawing_points.push_back(oglm::vec3(v.x, v.y, v.z));
	}
}

void Cube::scale(float x, float y, float z) {}
void Cube::scale(oglm::vec3 factor) {
	oglm::mat4 scale_mat = oglm::scale(factor);
	for (auto &i : points) {
		oglm::vec4 v(i.x, i.y, i.z, 1);
		v = scale_mat * v;
		i = oglm::vec3f((v.x), (v.y), (v.z));
	}
}

bool Cube::isCompleted() { return false; }
void Cube::pause() {}
void Cube::reset() {}
void Cube::increaseSpeed(int speed) {}
void Cube::decreaseSpeed(int speed) {}

Cube::~Cube() {}
