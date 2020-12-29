
#version 430
uniform float offset;
uniform float oy;

void main(void){
    if(gl_VertexID == 0){
        gl_Position = vec4(0.25 + offset, -0.25 + oy, 0, 1);
    }else if(gl_VertexID == 1) {
        gl_Position = vec4(-0.25 + offset, -0.25, 0, 1);
    }else{
        gl_Position = vec4(0.25 + offset, 0.25 + oy, 0, 1 );
    }
}