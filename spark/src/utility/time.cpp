#include "spark/utility/time.h"
#include "spark/renderer/opengl.h"

float Spark::Time::m_deltaTime = 0.0f;
bool Spark::Time::m_shouldUpdate = false;
double Spark::Time::m_lastTime = 0;

void Spark::Time::Initialize(){
    m_lastTime = glfwGetTime();
}

float Spark::Time::DeltaTime(){
    return m_deltaTime;
}

void Spark::Time::NextFrame(){
    double diff = glfwGetTime() - m_lastTime;
    m_deltaTime = (float )diff;
    auto m_timeToWait = SPARK_TARGET_FRAME_TIME - (float)(diff);
    if(m_timeToWait > 0 && m_timeToWait <= SPARK_TARGET_FRAME_TIME){
        m_shouldUpdate = false;
    } else{
        m_shouldUpdate = true;
        m_lastTime = glfwGetTime();
    }
}

bool Spark::Time::ShouldUpdateFrame(){
    return m_shouldUpdate;
}