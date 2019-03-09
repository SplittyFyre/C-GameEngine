#include "ShaderProgram.h"
#include <string>
#include <fstream>

uint ShaderProgram::loadShader(const char* file, GLenum type) {

	std::string shadersrc = "", line;

	std::ifstream fin;
	fin.open(file);

	if (fin.fail()) {
		fprintf(stderr, "unable to open shader file %s\n", file);
		exit(1);
	}

	while (std::getline(fin, line)) {
		shadersrc += line;
		shadersrc += '\n';
	}
	fin.close();

	uint shaderid = glCreateShader(type);

	
	const char *srcStrings[1];
	srcStrings[0] = shadersrc.c_str();
	int srcLens[1];
	srcLens[0] = shadersrc.length();

	glShaderSource(shaderid, 1, srcStrings, srcLens);
	glCompileShader(shaderid);

	int status;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &status);
	if (!status /*status == GL_FALSE*/) {
		int infoLogLen;
		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &infoLogLen);
		char *log = new char[infoLogLen];
		glGetShaderInfoLog(shaderid, infoLogLen, NULL, log);
		fprintf(stderr, "error compiling shader %s:\n", file);
		fprintf(stderr, "\n%s\n", log);
		//puts("press any key to continue... :)");
		//getchar();
		delete[] log;
		exit(1);
	}

	return shaderid;
}

void ShaderProgram::bindAttrib(int attrib, const char *varName) {
	glBindAttribLocation(m_programID, attrib, varName);
}

void ShaderProgram::manualLink() {
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);
}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile) {
	m_vertexID = loadShader(vertexFile, GL_VERTEX_SHADER);
	m_fragmentID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);
	// incomplete, bind attributes, get uniform locations, and link program in sub-class constructor
}

ShaderProgram::~ShaderProgram() {
	stop();
	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_fragmentID);
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_programID);
}
