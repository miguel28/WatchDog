varying vec4 diffuse,ambientGlobal,ambient, ecPos;
varying vec3 normal,halfVector;
varying float dist;
varying vec3 lightDir2;
 
void main()
{  
    vec3 aux;

    /* compute the vertex position  in camera space. */
    ecPos = gl_ModelViewMatrix * gl_Vertex;
 
    /* first transform the normal into eye space and normalize the result */
    /* compute the distance to the light source to a varying variable*/
    	vec3 lightDir = vec3(gl_LightSource[0].position-ecPos);
     
	dist = length(lightDir);
	normal = normalize(gl_NormalMatrix * gl_Normal);
 
    /* Normalize the halfVector to pass it to the fragment shader */
    halfVector = gl_LightSource[0].halfVector.xyz;
     
    /* Compute the diffuse, ambient and globalAmbient terms */
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
    ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
     
    lightDir2 = normalize(vec3(gl_LightSource[0].position));
    gl_TexCoord[0] = gl_MultiTexCoord0;    
     
    gl_Position = ftransform();
}

