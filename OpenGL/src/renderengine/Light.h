#pragma once

#include "glm/glm/vec3.hpp"

class Light {

private:
	glm::vec3 m_pos, m_colour, m_attenuation;

public:

	inline void setPosition(const glm::vec3 &pos) { m_pos = pos; };
	inline void setColour(const glm::vec3 &colour) { m_colour = colour; };
	inline void setAttenuation(const glm::vec3 &atten) { m_attenuation = atten; };

	inline const glm::vec3 &getPosition() const { return m_pos; };
	inline const glm::vec3 &getColour() const { return m_colour; };
	inline const glm::vec3 &getAttenuation() const { return m_attenuation; };

	Light(const glm::vec3 &pos, const glm::vec3 &colour) :
		m_pos(pos), m_colour(colour), m_attenuation(1, 0, 0) {};

	Light(const glm::vec3 &pos, const glm::vec3 &colour, const glm::vec3 &atten) :
		m_pos(pos), m_colour(colour), m_attenuation(atten) {};

};

