#ifndef SHADERS_H_
#define SHADERS_H_
#include<string>
#include "Externs.h"
#include <memory>

class Shader {
private:
	GLuint program;
public:
	GLuint getShaderProgram() { return program; };
	void makeShaderProgram(const std::string arg_vss, const std::string arg_fss);
};

const std::string vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 texCoord;

out vec2 outTexCoord;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

out vec4 vColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
	vColor = aColor;
	outTexCoord = texCoord;

}
)";


const std::string vertexShaderSourceCube = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec3 position;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 vColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vColor = aColor;
	position = aPos;
}
)";


const std::string fragmentShaderSource = R"(#version 330 core

layout(binding = 0) uniform sampler2D uTexture;

in vec2 outTexCoord;

out vec4 FragColor;

uniform vec4 ourColor;
uniform float texRatio;

void main()
{
   FragColor = mix(ourColor, texture(uTexture, outTexCoord), texRatio);
}
)";


const std::string fragmentShaderSourceCube = R"(#version 330 core
layout(binding = 1) uniform samplerCube uCubeTexture;

out vec4 FragColor;

uniform vec4 ourColor;
uniform float texRatio;

in vec3 position;


void main()
{
   FragColor = mix(ourColor, texture(uCubeTexture, position), texRatio);
}
)";
#endif