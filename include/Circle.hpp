#pragma once

#include "Angel.hpp"
#include "oglm.hpp"
#include <vector>
class Circle {
  private:
	std::vector<oglm::vec2> points;
	std::vector<oglm::vec2> false_points;
	unsigned int thickness;
	unsigned int frameCount;
	float centerX;
	float centerY;
	float radius;

  public:
	Circle(float x0, float y0, float r, unsigned int thickness);
	void draw();
	void animate();
	void translate(float x, float y);
	void translate(oglm::vec2 factor);
	void rotate(float radians, float x, float y);
	void rotate(float radians, oglm::vec2 factor);
	void scale(float x, float y);
	void scale(oglm::vec2 factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(float speed);
	void decreaseSpeed(float speed);
};
