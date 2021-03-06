#pragma once

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

class SpriteRenderer {

  public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Texture2D &texture, glm::vec2 position,
	                glm::vec2 size = glm::vec2(10.0f, 10.0f),
	                float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

  private:
	Shader m_Shader;
	unsigned int m_QuadVAO;
	void InitRenderData();
};
