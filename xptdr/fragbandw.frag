uniform sampler2D texture;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = vec4( vec3(pixel.x+pixel.y+pixel.z)/3.0, pixel.w);
}