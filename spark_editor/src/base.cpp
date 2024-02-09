#include "spark_editor/base.h"

uuids::uuid_random_generator* UUIDGenerator::m_gen = nullptr;
UUID UUIDGenerator::Create(){
    if (!m_gen){
        std::random_device rd;
        auto seedData = std::array<int, std::mt19937::state_size> {};
        std::generate(std::begin(seedData), std::end(seedData), std::ref(rd));
        std::seed_seq seq(std::begin(seedData), std::end(seedData));
        std::mt19937 generator(seq);
        m_gen = new uuids::uuid_random_generator(generator);
    }
    return (*m_gen)();
}

void UUIDGenerator::Destroy() {
    delete m_gen;
}