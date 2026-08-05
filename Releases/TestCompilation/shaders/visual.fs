#version 330 core
uniform float iTime;
uniform vec3 iResolution;
out vec4 fragColor;

vec3 rand_colors(float f)
{
  vec3 a = vec3(0.5f, 0.5f, 0.5f);
  vec3 b = vec3(0.5f, 0.5f, 0.5f);
  vec3 c = vec3(1.0f, 1.0f, 1.0f);
  vec3 d = vec3(0.123f, 0.456f, 0.567f);

  return a + b * cos(6.5 * (c * f + d));
}

void main()
{
   vec2 fragCoord = gl_FragCoord.xy;
   vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;

   for (int i = 0; i< 4; ++i) {
    uv = fract(uv);
    uv -= 0.5;

    float d = length(uv);

    vec3 color = rand_colors(d + iTime);

    d = sin(d * 8.f + iTime * 3.f) / 6.f;
    d = abs(d);

    d = 0.02f / d;
    color *= d;

    fragColor = vec4(color, 1.0);
   }

}
