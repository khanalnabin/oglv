#pragma once

#include "Shape2D.hpp"
#include "Angel.hpp"
#include <vector>
class Ellipse : public Shape2D {
  private:
	std::vector<oglm::vec2<int>> points;
	unsigned int thickness;
	unsigned int frameCount;
	int centerX;
	int centerY;
	int majX;
	int majY;

  public:
	Ellipse(int x0, int y0,int a, int b, unsigned int thickness);
	void draw();
	void animate();
	void translate(int x, int y);
	void translate(oglm::vec2<int> factor);
	void rotate(int radians, int x, int y);
	void rotate(int radians, oglm::vec2<int> factor);
	void scale(int x, int y);
	void scale(oglm::vec2<int> factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
};
