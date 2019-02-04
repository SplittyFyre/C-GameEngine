#pragma once

#include <GL/glew.h>
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
	virtual void bindAttributes() = 0;
	void bindAttrib(int attrib, const char *varName);

};