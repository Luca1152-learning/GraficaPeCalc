// Shader-ul de fragment / Fragment shader  
 #version 330

in vec4 ex_Color;
in vec2 tex_Coord; 
out vec4 out_Color;

uniform int codCuloare;
uniform sampler2D myTexture;

void main(void) {
	 switch (codCuloare)
	 {
		case 0: 
			out_Color = ex_Color;
			break;
		case 1:
			out_Color = mix(texture(myTexture, tex_Coord), ex_Color, 0.0);
			break;
		default:
			out_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			break;
	}
}
 