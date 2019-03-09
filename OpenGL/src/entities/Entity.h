#pragma once

#include "../renderengine/models.h"
#include <glm/glm/glm.hpp>

class Entity {

private:
	TexturedModel m_model;
	glm::vec3 m_position, m_rotation, m_scale;

public:
	Entity(const TexturedModel &model, const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) :
		m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) {};

	inline void setPosition(const glm::vec3 &position) { m_position = position; };
	inline void setRotation(const glm::vec3 &rotation) { m_rotation = rotation; };
	inline void setScale(const glm::vec3 &scale) { m_scale = scale; };

	inline void move(const glm::vec3 &d_pos) { m_position += d_pos; };
	inline void move(float dx, float dy, float dz) { m_position.x += dx; m_position.y += dy; m_position.z += dz; };
	inline void rotate(const glm::vec3 &d_rot) { m_rotation += d_rot; };
	inline void rotate(float rx, float ry, float rz) { m_rotation.x += rx; m_rotation.y += ry; m_rotation.z += rz; }

	inline const TexturedModel &getModel() const { return m_model; };
	inline const glm::vec3 &getPosition() const { return m_position; };
	inline const glm::vec3 &getRotation() const { return m_rotation; };
	inline const glm::vec3 &getScale() const { return m_scale; };

};

