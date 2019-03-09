#pragma once

#include <GL/glew.h>
#include <glm/glm/glm.hpp>
#include <unordered_map>
#include "../../utils/mytypes.h"

class ShaderProgram {
 
public:
	ShaderProgram(const char *vertexFile, const char *fragmentFile);
	virtual ~ShaderProgram();
	inline void start() { glUseProgram(m_programID); };
	inline void stop() { glUseProgram(0); };

private:
	uint m_programID, m_vertexID, m_fragmentID;
	static uint loadShader(const char *file, GLenum type);

protected:

	std::unordered_map<std::string, uint> uniformLocationsHashMap;

	inline void addUniformVariable(const char *varName) { uniformLocationsHashMap[varName] = glGetUniformLocation(m_programID, varName); };
	inline uint uniformLocationOf(const char *varName) const { return uniformLocationsHashMap.at(varName); };

	virtual void bindAttributes() = 0;
	/*use getAllUniformLocations() before manualLink*/
	virtual void getAllUniformLocations() = 0; 
	void bindAttrib(int attrib, const char *varName);
	void manualLink();

	inline void loadfloat(uint location, float value) const { glUniform1f(location, value); };
	inline void loadvector(uint location, const glm::vec3 &vec) const { glUniform3f(location, vec.x, vec.y, vec.z); };
	inline void loadBool(uint location, bool value) { glUniform1f(location, value ? 1.0f : 0.0f); };
	inline void loadMatrix(uint location, const glm::mat4 &matrix) const { glUniformMatrix4fv(location, 1, false, &matrix[0][0]); };

};