#version 330 core

// Interpolated values from the vertex shaders
in vec3 position_for_color;

uniform float mandelbrot_iteration;
// Ouput data
out vec4 color;

int MAX_ITER = int(mandelbrot_iteration);
vec2 complex_mult(vec2 a, vec2 b){
	return vec2((a.x * b.x) - (a.y * b.y), (a.x * b.y + a.y * b.x));
}

float complex_abs(vec2 a){
	return sqrt((a.x * a.x) + (a.y * a.y));
}

float mandelbrot_set(vec2 c){
	//c = c / pow(2.4, 4.0) - vec2(0.65, 0.45);
	vec2 z = vec2(0, 0);
	float n = 0;

	while((complex_abs(z) < 2) && (n < MAX_ITER)){
		z = complex_mult(z, z) + c;
		n++; 
	}
	return n;
}

void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	float m = mandelbrot_set(position_for_color.xy);	// 1 - m for color invertion
	if(m == MAX_ITER){
		color = vec4(0, 0, 0, 1);
	}else{
		m = m/ MAX_ITER;
		color = vec4(0.7, m * 0.9, 0, 1);
	}
}