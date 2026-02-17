#ifndef VECTOR2_h
#define VECTOR2_h

class Vector2
{
    public:
        Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y (_y){}

        ~Vector2()
        {
            x = 0.0f;
            y = 0.0f;
        }

    private:
        float x;
        float y;
};

#endif