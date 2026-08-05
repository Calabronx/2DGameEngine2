// #version 330 core

// uniform float uTime;
// in vec2 uv;
// out vec4 FragColor;

// vec3 rand_colors(float f)
// {
//     // color base (centro de la paleta)
//     vec3 a = vec3(0.5f, 0.5f, 0.5f);

//     // amplitud del color 
//     vec3 b = vec3(0.5f, 0.5f, 0.5f);

//     // frecuencia
//     vec3 c = vec3(1.0f, 1.0f, 1.0f);

//     // offset de fase (desfase entre canales RGB)
//     vec3 d = vec3(0.123f, 0.456f, 0.567f);

//     return a + b * cos(6.5 * (c * f + d));
// }

// void main()
// {
//     vec3 color = rand_colors(uTime * 0.40);
//     FragColor = vec4(color, 1.0);
// }


#version 330 core

uniform float uTime;

uniform vec3 iResolution;

uniform vec4 backroundColor;

out vec4 fragColor;

// ------------------------------------------------------------
// Generador de paleta procedural usando coseno
// Técnica muy común para generar colores suaves animados
// ------------------------------------------------------------
vec3 rand_colors(float f)
{
    // Color base (centro de la paleta)
    vec3 a = vec3(0.5f, 0.5f, 0.5f);

    // Amplitud del color (qué tanto varía)
    vec3 b = vec3(0.5f, 0.5f, 0.5f);

    // Frecuencia (escala del patrón)
    vec3 c = vec3(1.0f, 1.0f, 1.0f);

    // Offset de fase (desfase entre canales RGB)
    vec3 d = vec3(0.123f, 0.456f, 0.567f);

    // Fórmula de paleta:
    // a + b * cos( frecuencia * (valor + fase) )
    return a + b * cos(6.5 * (c * f + d));
}


void main()
{
    vec2 fragCoord = gl_FragCoord.xy;

    // Normalizamos coordenadas:
    // - Centro en (0,0)
    // - Mantiene proporción usando altura
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;

    // cambio color de fondo
    // Loop que repite el efecto 4 veces
    // OJO: actualmente NO acumula color,
    // solo pisa fragColor cada iteración.

    for (int i = 0; i < 4; ++i)
    {
        // --------------------------------------------------------
        // TILING (repetición en mosaico)
        // fract() deja solo la parte decimal
        // Esto repite el espacio cada 1.0
        // --------------------------------------------------------
        // uv = fract(uv);

        // Movemos el centro de cada celda a (0,0)
        // uv -= 0.5;

        // --------------------------------------------------------
        // Distancia radial al centro de la celda
        // Esto genera patrones circulares
        // --------------------------------------------------------
        float d = length(uv);

        // --------------------------------------------------------
        // Color basado en distancia + tiempo
        // Produce anillos de colores animados
        // --------------------------------------------------------
        vec3 color = rand_colors(d + uTime);

        // --------------------------------------------------------
        // Generamos ondas sinusoidales radiales
        // d * 8.0  -> frecuencia espacial (cantidad de anillos)
        // iTime*3  -> velocidad de animación
        // --------------------------------------------------------
        d = sin(d * 2.0 + uTime * 1.0) / 6.0;

        // Hacemos el valor siempre positivo
        d = abs(d);

        // --------------------------------------------------------
        // Glow / Intensidad
        // Dividir por valores pequeños genera brillo fuerte
        // Cuanto más cerca de 0 esté d, más brillante será
        // --------------------------------------------------------
        d = 0.02 / d;

        // Aplicamos intensidad al color
        color *= d;

        // Escribimos el color final del pixel
        fragColor = vec4(color, 1.0);
    }
}
