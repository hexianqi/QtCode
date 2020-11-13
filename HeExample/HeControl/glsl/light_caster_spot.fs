#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.innerCutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;

    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
// spot
//void main()
//{
//    // ambient
//    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

//    // check if lighting is inside the spotlight cone
//    vec3 lightDir = normalize(light.position - FragPos);
//    float theta = dot(lightDir, normalize(-light.direction));
//    if (theta > light.innerCutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
//    {
//        // diffuse
//        vec3 norm = normalize(Normal);
//        float diff = max(dot(norm, lightDir), 0.0);
//        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

//        // specular
//        vec3 viewDir = normalize(viewPos - FragPos);
//        vec3 reflectDir = reflect(-lightDir, norm);
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

//        // attenuation
//        float distance    = length(light.position - FragPos);
//        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
//        diffuse  *= attenuation;
//        specular *= attenuation;

//        vec3 result = ambient + diffuse + specular;
//        FragColor = vec4(result, 1.0);
//    }
//    else
//    {
//        // else, use ambient light so scene isn't completely dark outside the spotlight.
//        FragColor = vec4(ambient, 1.0);
//    }
//}


