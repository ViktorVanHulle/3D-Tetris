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
layout (location = 3) in vec3 aNormal;


out vec2 outTexCoord;
out vec3 Normal;
out vec3 position;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

out vec4 vColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
	vColor = aColor;
	outTexCoord = texCoord;
    position = vec3(model * vec4(aPos, 0.0, 1.0));
	Normal = normalize(model * vec4(aNormal, 0.0)).xyz;

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
in vec3 position;
in vec3 Normal;

out vec4 FragColor;

uniform vec4 ourColor;
uniform float texRatio;
uniform float ambientStrength = 0.5;
uniform float diffuseStrength = 0.5;
uniform vec3 lightColor;
uniform vec3 lightPosition= vec3(0.0, 0.0, 1.0);
uniform bool illuminationMode = false;

void main()
{
   if(illuminationMode){
	   //ambient lighting
	   vec3 ambient = ambientStrength * lightColor;

	   //diffuse lighting
	   vec3 lightDir = normalize(lightPosition - position);
	   float diff = max(dot(lightDir, Normal), 0.0);
	   vec3 diffuse = diffuseStrength * diff * lightColor;

	   vec4 color = mix(ourColor, texture(uTexture, outTexCoord), texRatio);
	   FragColor = vec4((ambient + diffuse) * color.rgb, 1.0);
	}else {
	   FragColor = mix(ourColor, texture(uTexture, outTexCoord), texRatio);
	}

}
)";


const std::string fragmentShaderSourceCube = R"(#version 330 core
layout(binding = 1) uniform samplerCube uCubeTexture;

out vec4 FragColor;

uniform vec4 ourColor;
uniform float texRatio;
uniform float transparency;

in vec3 position;


void main()
{
    vec4 color = mix(ourColor, texture(uCubeTexture, position), texRatio);
	FragColor = vec4(color.rgb, transparency);
}
)";
#endif