#version 330 core
in vec3 ourColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��

out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4

void main()
{
    color = vec4(ourColor, 1.0f);
}