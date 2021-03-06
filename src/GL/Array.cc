/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Array.hh"

#include "Bind.hh"

using namespace Entropy::Theia::GL;
using namespace Entropy::Log;
using namespace std;

using Entropy::Theia::Log;

Array::Array()
{
	glGenVertexArrays(1, &_vao);
}

Array::~Array()
{
	glDeleteVertexArrays(1, &_vao);
}

void Array::Bind(const Program &prog, const Buffer &buff, const string &name, const size_t count, const GLenum type, const size_t stride, const size_t offset)
{
	GL::Bind a(*this), b(buff);

	GLint attrib = glGetAttribLocation(prog.Handle(), name.c_str());
	CHECK_GL_ERRORS_WITH("Failed to get Attribute Location", AttributeName(name));
	if(attrib < 0)
		ENTROPY_THROW(Exception("Attribute doesn't exist") << AttributeName(name));
	glEnableVertexAttribArray(attrib);
	CHECK_GL_ERRORS_WITH("Failed to enable Attribute", AttributeName(name));
	glVertexAttribPointer(attrib, count, type, GL_FALSE, stride, reinterpret_cast<void *>(offset));
	CHECK_GL_ERRORS_WITH("Failed to specify Attribute Pointer", AttributeName(name));
}

const GLuint &Array::Handle() const
{
	return _vao;
}
