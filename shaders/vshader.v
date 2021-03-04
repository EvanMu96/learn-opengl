#version 330 core
layout (location = 0) in vec3 position; // position����������λ��ֵΪ0
layout (location = 1) in vec3 color; // ��ɫ����������λ��Ϊ1

out vec3 ourColor; // ΪƬ����ɫ��ָ��һ����ɫ��� �Խ�Ƭ����ɫ���� in in vec4 vertexColor

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}