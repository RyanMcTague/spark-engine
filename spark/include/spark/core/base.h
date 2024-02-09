#ifndef SPARK_ENGINE_BASE_H
#define SPARK_ENGINE_BASE_H
#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <stack>
#include <cmath>
#include <typeindex>
#include <typeinfo>
#include <forward_list>
#include <bitset>
#include <algorithm>
#include "cmrc/cmrc.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "spark/core/platform.h"
#include "spark/utility/logger.h"
#include <sstream>
CMRC_DECLARE(spark);

#define SPARK_FPS 60.0f
#define SPARK_TARGET_FRAME_TIME (1.0f / SPARK_FPS)

namespace Spark{
    SPARK_API using UUID = unsigned int;
    SPARK_API using glm::mat4, glm::vec2, glm::vec3, glm::vec4;

    template<typename T>
    using TypeMap = std::map<std::type_index, T>;

    template<typename T>
    using StringMap = std::map<std::string, T>;

    SPARK_API using StringCount = std::map<std::string, uint32_t>;

}

#endif //SPARK_ENGINE_BASE_H
