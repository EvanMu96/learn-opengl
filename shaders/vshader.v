#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 color; // ��ɫ����������λ��Ϊ1
layout (location = 2) in vec2 texCoord;

out vec3 ourColor; // ΪƬ����ɫ��ָ��һ����ɫ��� �Խ�Ƭ����ɫ���� in in vec4 vertexColor
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
    TexCoord = texCoord;
}