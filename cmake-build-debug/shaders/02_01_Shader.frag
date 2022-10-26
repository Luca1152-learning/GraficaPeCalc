// Shader-ul de fragment / Fragment shader  
#version 330

in vec4 ex_Color;
out vec4 out_Color;
uniform int codCol;
uniform float red;
uniform float green;
uniform float blue;

void main(void)
{
    if (codCol==0){
        out_Color = ex_Color;
    } else {
        out_Color = vec4(red, green, blue, 0.0);
    }
}
 