#ifndef SPARK_ENGINE_IMCONFIG_H
#define SPARK_ENGINE_IMCONFIG_H

#define IM_VEC2_CLASS_EXTRA \
    ImVec2 operator*(float s) const { return ImVec2(x * s, y * s); } \
    ImVec2 operator+(const ImVec2& vec ) const { return ImVec2(x + vec.x, y + vec.y); } \
    ImVec2 operator-(const ImVec2& vec ) const { return ImVec2(x - vec.x, y - vec.y); }
#endif //SPARK_ENGINE_IMCONFIG_H
