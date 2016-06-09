#version 150 core

in Vertex	{
	vec2 texCoord;
	vec3 outPos;
	vec4 colour;
} IN;

out vec4 FragColor;

void main(void)	{	
	if (((IN.outPos.x * IN.outPos.x) + (IN.outPos.y * IN.outPos.y)) > 0.0004)
	{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	} else {
		FragColor = IN.colour;
	}
}