varying vec4 diffuse,ambientGlobal, ambient, ecPos;
varying vec3 normal,halfVector;
varying float dist;
varying vec3 lightDir2;
uniform sampler2D tex;
 
void main()
{
    vec3 n,halfV,viewV,lightDir;
    float NdotL,NdotHV;
    vec4 color = ambientGlobal;
    float att,spotEffect;
     
    /* a fragment shader can't write a verying variable, hence we need
    a new variable to store the normalized interpolated normal */
    n = normalize(normal);
     
    // Compute the ligt direction
    lightDir = vec3(gl_LightSource[0].position-ecPos);
     
    
     
    /* compute the dot product between normal and ldir */
    NdotL = max(dot(n,normalize(lightDir)),0.0);
 
	/*if(gl_LightSource[0].spotCutoff > 90.0)

    if (NdotL > 0.0) {
     
        att = 1.0 / (gl_LightSource[0].constantAttenuation +
                gl_LightSource[0].linearAttenuation * dist +
                gl_LightSource[0].quadraticAttenuation * dist * dist);
        color += att * (diffuse * NdotL + ambient);
     
         
        halfV = normalize(halfVector);
        NdotHV = max(dot(n,halfV),0.0);
        color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
    }
	else */
	if(gl_LightSource[0].spotCutoff <= 90.0)
	{
		if (NdotL > 0.0) {
     
        		spotEffect = dot(normalize(gl_LightSource[0].spotDirection), normalize(-lightDir));
        		if (spotEffect > gl_LightSource[0].spotCosCutoff) {
            		spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
            		att = spotEffect / (gl_LightSource[0].constantAttenuation +
                    gl_LightSource[0].linearAttenuation * dist +
                    gl_LightSource[0].quadraticAttenuation * dist * dist);
                 
            		color += att * (diffuse * NdotL + ambient);
         
             
            		halfV = normalize(halfVector);
            		NdotHV = max(dot(n,halfV),0.0);
            		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
        		}
    		}
	}
	else
	{
		if (NdotL > 0.0) {
     
        		att = 1.0 / (gl_LightSource[0].constantAttenuation +
                gl_LightSource[0].linearAttenuation * dist +
                gl_LightSource[0].quadraticAttenuation * dist * dist);
        		color += att * (diffuse * NdotL + ambient);
     
         
        		halfV = normalize(halfVector);
        		NdotHV = max(dot(n,halfV),0.0);
        		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
    		}

	}

/* For texture*/
	vec3 ct,cf;
    vec4 texel;
    float intensity,at,af;
    intensity = max(dot(lightDir2,normalize(normal)),0.0);
 
    cf = intensity * (gl_FrontMaterial.diffuse).rgb +
                  gl_FrontMaterial.ambient.rgb;
    af = gl_FrontMaterial.diffuse.a;
    texel = texture2D(tex,gl_TexCoord[0].st);
 
    ct = texel.rgb;
    at = texel.a; 

    //gl_FragColor = color;

	gl_FragColor = color* vec4(ct * cf, at * af);
}