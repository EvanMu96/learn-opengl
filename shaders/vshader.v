#version 330 core
layout (location = 0) in vec3 position; // position变量的属性位置值为0
layout (location = 1) in vec3 color; // 颜色变量的属性位置为1
layout (location = 2) in vec2 texCoord;

out vec3 ourColor; // 为片段着色器指定一个颜色输出 对接片段着色器的 in in vec4 vertexColor
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    ourColor = color; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
    TexCoord = texCoord;
}