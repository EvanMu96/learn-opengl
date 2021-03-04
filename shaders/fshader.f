#version 330 core
in vec3 ourColor; // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
in vec2 TexCoord;

out vec4 color; // Ƭ����ɫ������ı����������������������ͱ�����vec4
uniform sampler2D ourTexture;

void main()
{
    //color = vec4(ourColor, 1.0f);
    color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
}