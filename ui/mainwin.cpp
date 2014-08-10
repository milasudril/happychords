#ifdef __WAND__
target[name[mainwin.o] type[object]
dependency[glew32;external]]
#endif

#include "mainwin.h"

#include <herbs/exceptionmissing/exceptionmissing.h>
#include <herbs/include_binary/include_binary.h>
#include <cstdio>

#include <glm/glm.hpp>

INCLUDE_BINARY(vert_shader,"ui/vert_shader.glsl");
INCLUDE_BINARY(frag_shader,"ui/frag_shader.glsl");

namespace
	{
	static const GLfloat vertex_buffer_data[] =
		{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
		};

	GLuint shaderCompile(const uint8_t* source_begin,const uint8_t* source_end
		,GLuint type)
		{

		GLuint shader_id=glCreateShader(type);
		GLint source_length=source_begin-source_end;
		glShaderSource(shader_id,1,(const char**)&source_begin,&source_length);
		glCompileShader(shader_id);

		GLint res=0;
		int length_log=0;
		glGetShaderiv(shader_id,GL_COMPILE_STATUS,&res);
		glGetShaderiv(shader_id,GL_INFO_LOG_LENGTH,&length_log);
		Herbs::Stringbase<char> message;
		message.lengthValidSet(length_log);
		glGetShaderInfoLog(shader_id, length_log, NULL,message.begin());
		printf("%s\n", message.begin());

		return shader_id;
		}

	GLuint shadersLink(std::initializer_list<GLuint> shaders)
		{
		GLuint program_id=glCreateProgram();
		auto ptr=shaders.begin();
		while(ptr!=shaders.end())
			{
			glAttachShader(program_id,*ptr);
			++ptr;
			}
		glLinkProgram(program_id);

		GLint res=0;
		int length_log=0;
		glGetProgramiv(program_id,GL_LINK_STATUS,&res);
		glGetProgramiv(program_id,GL_INFO_LOG_LENGTH,&length_log);
		Herbs::Stringbase<char> message;
		message.lengthValidSet(length_log);
		glGetProgramInfoLog(program_id, length_log, NULL,message.begin());
		printf("%s\n", message.begin());

		return program_id;
		}
	}

void Happychords::Ui::Mainwin::onResize(int width,int height)
	{
	GlBlock block(*this);
	glViewport(0,0,width,height);
	}

void Happychords::Ui::Mainwin::onRender()
	{
	GlBlock block(*this);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,v_buffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
	glDrawArrays(GL_TRIANGLES,0,3);
	glDisableVertexAttribArray(0);
	buffersSwap();
	}

size_t Happychords::Ui::Mainwin::onEvent(uint32_t message_id,size_t param_0,size_t param_1)
	{
	switch(message_id)
		{
		case MessageLbuttondown:
			printf("You clicked in the window...\n");
			break;

		case MessageClose:
			m_connection.messageSend({Bridge::Message::Type::TERMINATE
				,{{0}}});
			break;
		}
	return GlViewport::onEvent(message_id,param_0,param_1);
	}

Happychords::Ui::Mainwin::Mainwin(Gui::Gui& gui_obj,uint32_t style_0
	,uint32_t style_1,Window* parent,Bridge::Connection& connection):
	Gui::GlViewport(gui_obj,style_0,style_1,parent),m_connection(connection)
	{
	GlBlock block(*this);
	glewExperimental=true;
	auto status=glewInit();
	if(status!=GLEW_OK)
		{
		printf("Error: %s\n", glewGetErrorString(status));
		throw Herbs::ExceptionMissing(___FILE__,__LINE__);
		}
	printf("OpenGL initialized: %s %s %s %s\n"
		,glGetString(GL_VENDOR)
		,glGetString(GL_RENDERER)
		,glGetString(GL_VERSION)
		,glGetString(GL_SHADING_LANGUAGE_VERSION));
	glGenVertexArrays(1,&v_array_id);
	glBindVertexArray(v_array_id);
	glGenBuffers(1,&v_buffer);
	glBindBuffer(GL_ARRAY_BUFFER,v_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data)
		, vertex_buffer_data, GL_STATIC_DRAW);

	auto vert_shader=shaderCompile(vert_shader_begin,vert_shader_end,GL_VERTEX_SHADER);
	auto frag_shader=shaderCompile(frag_shader_begin,frag_shader_end,GL_FRAGMENT_SHADER);

	program=shadersLink({vert_shader,frag_shader});

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	}

Happychords::Ui::Mainwin::~Mainwin()
	{
	GlBlock block(*this);
	glDeleteProgram(program);
	}

