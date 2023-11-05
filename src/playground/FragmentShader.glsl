#version 330 core

// Interpolated values from the vertex shaders
in vec3 position_for_color;



// Ouput data
out vec3 color;

int MAX_ITER = 100;
vec2 complex_mult(vec2 a, vec2 b){
	return vec2((a.x * b.x) - (a.y * b.y), (a.x * b.y + a.y * b.x));
}

float complex_abs(vec2 a){
	return sqrt((a.x * a.x) + (a.y * a.y));
}

float mandelbrot_set(vec2 c){
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
	float m = mandelbrot_set(position_for_color.xy) / MAX_ITER;
	color = vec3(m, m, m);
}