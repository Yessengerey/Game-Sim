#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 FragColor;

void main(void)	{	
	FragColor = IN.colour;
}