#include "Mesh.h"

Mesh::Mesh(void) {
	//Most objects in OpenGL are represented as 'names' - an unsigned int
	//index, really. They are always generated and destroyed by OpenGL 
	//functions. Most of these functions allow you to generate multiple
	//names at once (the first parameter here is a count).
	glGenVertexArrays(1, &arrayObject);

	for (int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}

	numVertices = 0;
	type = GL_TRIANGLES;

	//Later tutorial stuff
	numIndices = 0;
	vertices = NULL;
	textureCoords = NULL;
	normals = NULL;
	tangents = NULL;
	indices = NULL;
	colours = NULL;
}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);			//Delete our VAO
	glDeleteBuffers(MAX_BUFFER, bufferObject);		//Delete our VBOs

	//Later tutorial stuff
	delete[]vertices;
	delete[]indices;
	delete[]textureCoords;
	delete[]tangents;
	delete[]normals;
	delete[]colours;
}

void Mesh::Draw() {
	/*
	To render with a mesh in OpenGL, we need to bind all of the buffers
	containing vertex data to the pipeline, and attach them to the
	generic attributes referenced in our vertex shader.
	That's quite a lot of code to set up, but fear not - all of the state
	is cached within our Vertex Array Object, so once that's been set up
	by the BufferData function, all we need to do is bind the VAO and it
	all happens automagically
	*/
	glBindVertexArray(arrayObject);
	//There are two draw functions in OpenGL, depending on whether we're 
	//using indices or not. Both start off taking a primitive type - 
	//triangles, quads, lines, points etc. 

	if (bufferObject[INDEX_BUFFER]) {
		/*
		If we have an index buffer, we tell OpenGL how to parse that
		buffer data (is it bytes/ints/shorts), and how many data
		elements there are. The last parameter should always be 0,
		it's part of the old OpenGL spec.
		*/
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else {
		/*
		If we don't have indices, we can just use this function.
		Its extra parameters define which is the first vertex
		to draw, and how many vertices past this point to draw.
		*/
		glDrawArrays(type, 0, numVertices);	//Draw the triangle!
	}
	/*
	We don't strictly have to do this, but 'undoing' whatever
	we do to OpenGL in a function generally keeps the pipeline
	from getting incorrect states, or otherwise not doing what
	you want it to do.
	*/
	glBindVertexArray(0);
}
Mesh* Mesh::GeneratePoints(Vector3 v) {
	Mesh*m = new Mesh();
	m->numVertices = 1;

	m->vertices = new Vector3[m->numVertices];
	m->vertices[0] = v;

	m->textureCoords = new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f, 0.0f);

	m->colours = new Vector4[m->numVertices];
	m->colours[0] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	m->BufferData();

	m->type = GL_POINTS;


	return m;

}

Mesh* Mesh::GenerateLine(Vector3 v, Vector3 u) {
	Mesh* m = new Mesh();

	m->numVertices = 2;

	m->vertices = new Vector3[m->numVertices];
	m->vertices[0] = v;
	m->vertices[1] = u;

	m->textureCoords = new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f, 0.0f);
	m->textureCoords[1] = Vector2(0.5f, 0.0f);

	m->colours = new Vector4[m->numVertices];
	m->colours[0] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->colours[1] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m->BufferData();
	m->type = GL_LINES;
	return m;
}

Mesh* Mesh::GenerateArrow(Vector3 v, Vector3 u) {
	Mesh* m = new Mesh();

	m->numVertices = 6;

	m->vertices = new Vector3[m->numVertices];
	m->vertices[0] = v;
	m->vertices[1] = u;
	m->vertices[2] = Vector3(u.x - 0.01f, u.y, 0.0f);
	m->vertices[3] = Vector3(u.x, u.y + 0.025f, 0.0f);
	m->vertices[4] = Vector3(u.x + 0.01f, u.y, 0.0f);
	m->vertices[5] = u;

	m->textureCoords = new Vector2[m->numVertices];
	m->colours = new Vector4[m->numVertices];

	for (int i = 0; i < m->numVertices; i++) {
		m->textureCoords[i] = Vector2(0.5f, 0.0f);
		m->colours[i] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	
	m->BufferData();
	m->type = GL_LINE_STRIP;;
	return m;

}

Mesh* Mesh::GenerateCircle(Vector3 v, Vector4 colour, float range) {
	Mesh*m = new Mesh();
	int seg = 60;
	m->numVertices = seg;

	m->vertices = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->colours = new Vector4[m->numVertices];

	for (int i = 0; i < seg; ++i) {
		float theta = 2.0f * 3.1415926f *float(i) / float(seg);

		float X = range * cosf(theta);
		float Y = range * sinf(theta);

		m->vertices[i] = Vector3((X + v.x), (Y + v.y), v.z);
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
		m->colours[i] = colour;
	}

	m->BufferData();

	m->type = GL_TRIANGLE_FAN;

	return m;
}

Mesh* Mesh::GenerateHalfCircle(Vector3 v, Vector4 colour, float range) {
	Mesh* m = new Mesh();
	int seg = 360;
	m->numVertices = seg;

	m->vertices = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->colours = new Vector4[m->numVertices];

	for (int i = 0; i < seg; ++i) {
		float theta = 3.1415926f *float(i) / float(seg);

		float X = range * sinf(theta);
		float Y = range * cosf(theta);

		m->vertices[i] = Vector3((X + v.x), (Y + v.y), v.z);
		m->textureCoords[i] = Vector2(0.0f, 0.0f);
		m->colours[i] = colour;
	}

	m->BufferData();

	m->type = GL_LINE_STRIP;

	return m;
}


Mesh* Mesh::GenerateTriangle() {
	Mesh*m = new Mesh();
	m->numVertices = 3;

	m->vertices = new Vector3[m->numVertices];
	m->vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m->vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m->vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

	m->textureCoords = new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f, 0.0f);
	m->textureCoords[1] = Vector2(1.0f, 1.0f);
	m->textureCoords[2] = Vector2(0.0f, 1.0f);

	m->colours = new Vector4[m->numVertices];
	m->colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

	m->BufferData();

	return m;
}

Mesh* Mesh::GenerateTriangleStrip(const Vector4 colour, const Vector4 colour2, const Vector4 colour3, vector<Vector3> v) {
	Mesh*m = new Mesh();
	m->numVertices = v.size();

	m->vertices = new Vector3[m->numVertices];
	m->colours = new Vector4[m->numVertices];

	for (int i = 0; i < m->numVertices; ++i) {
		m->vertices[i] = v[i];
		//m->colours[i] = colour;

	}
	m->colours[0] = colour;
	m->colours[1] = colour;
	m->colours[2] = colour2;
	m->colours[3] = colour2;
	m->colours[4] = colour3;
	m->colours[5] = colour3;

	m->type = GL_TRIANGLE_STRIP;

	m->BufferData();

	return m;
}

Mesh*	Mesh::LoadMeshFile(const string &filename) {
	ifstream f(filename);

	if (!f) {
		return NULL;
	}

	Mesh*m = new Mesh();
	f >> m->numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex;
	f >> hasColour;

	m->vertices = new Vector3[m->numVertices];

	if (hasTex) {
		m->textureCoords = new Vector2[m->numVertices];
		m->colours = new Vector4[m->numVertices];
	}

	for (unsigned int i = 0; i < m->numVertices; ++i) {
		f >> m->vertices[i].x;
		f >> m->vertices[i].y;
		f >> m->vertices[i].z;
	}

	if (hasColour) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			unsigned int r, g, b, a;

			f >> r;
			f >> g;
			f >> b;
			f >> a;
			//OpenGL can use floats for colours directly - this will take up 4x as
			//much space, but could avoid any byte / float conversions happening
			//behind the scenes in our shader executions
			m->colours[i] = Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
	}

	if (hasTex) {
		for (unsigned int i = 0; i < m->numVertices; ++i) {
			f >> m->textureCoords[i].x;
			f >> m->textureCoords[i].y;
		}
	}

	m->BufferData();
	return m;
}

void	Mesh::BufferData() {
	/*
		To more efficiently bind and unbind the states required to draw a mesh,
		we can encapsulate them all inside a Vertex Array Object.

		When a VAO is bound, all further changes to vertex buffers and vertex
		attributes are cached inside the VAO, and will be reapplied whenever
		that VAO is later bound again
	*/
	glBindVertexArray(arrayObject);

	/*
	To put some vertex data on the GPU, we must create a buffer object to store it.

	To upload data to a vertex buffer, it must be bound, with a specific 'target',
	which defines what the buffer is to be used for.

	Then, once bound, data can be uploaded using the glBufferData function, which
	takes a pointer to the data to be sent, and the size of that data, as well as
	a usage parameter - this lets OpenGL know how the data will be accessed.

	To turn a vertex buffer into a vertex attribute suitable for sending to a
	vertex shader, the glVertexAttribPointer function must be called.
	This takes in an attribute 'slot', how many elements each data entry has
	(i.e 2 for a vector2 etc), and what datatype (usually float) it is.
	This will bind the currently bound vertex buffer to that attribute slot.
	To actually enable that attribute slot, the glEnableVertexAttribArray is called.

	Note that we use the value VERTEX_BUFFER for the 'slot' parameter - this is just
	an enum value, that equates to 0. It's common to use enums as indices into arrays
	in this way, as it keeps everything consistent. It's also pretty sensible to always
	bind the same data types to the same attribute slots, it makes life much easier!

	These last two functions, along with the glBindBuffer call, are examples of
	functionality that is cached in the actual VAO.
	*/

	//Buffer vertex data
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	////Buffer texture data
	if (textureCoords) {
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	//buffer colour data
	if (colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector4), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	//buffer index data
	if (indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	//Once we're done with the vertex buffer binding, we can unbind the VAO,
	//ready to reapply later, such as in the Draw function above!
	glBindVertexArray(0);
}