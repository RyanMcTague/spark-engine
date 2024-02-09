#include <iostream>
#include "cmrc/cmrc.hpp"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

CMRC_DECLARE(spark);

auto fs = cmrc::spark::get_filesystem();

MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
{
    uint32_t fileSize = 0;
    auto file = fs.open(assemblyPath);
    char* fileData = (char *)&file.begin()[0];
    fileSize = file.size();
    MonoImageOpenStatus status;
    MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

    if (status != MONO_IMAGE_OK)
    {
        const char* errorMessage = mono_image_strerror(status);
        std::cout << errorMessage << std::endl;
        return nullptr;
    }

    MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
    mono_image_close(image);

    return assembly;
}


int main(int argc, char** argv){

    mono_set_dirs(MONO_LIB_PATH,
                  MONO_LIB_PATH);

    MonoDomain *domain = mono_jit_init ("../test.exe");

//    MonoAssembly *assembly = mono_domain_assembly_open (domain, "../test.dll");
    MonoAssembly *assembly  = LoadCSharpAssembly("Test.dll");
    if (!assembly)
    {
        std::cout << "Cannot open assembly" << std::endl;
    }

    MonoImage *image = mono_assembly_get_image(assembly);
    MonoClass *klass = mono_class_from_name(image, "", "Hello");
//    void* field = nullptr;
//    while (MonoMethod* method = mono_class_get_methods(klass, &field)){
//        std::cout << mono_method_get_name(method) << std::endl;
//    }
//    MonoMethod *method = mono_method_desc_search_in_class(desc, klass);
    MonoMethod *method = mono_class_get_method_from_name(klass, "GetMessage", 0);
    std::cout << mono_method_get_name(method) << std::endl;

    MonoObject *result = mono_runtime_invoke(method, nullptr, nullptr, nullptr);
    MonoClass *objClass = mono_object_get_class(result);
    auto name =  mono_class_get_name(objClass);
    MonoString* str = mono_object_to_string(result, nullptr);
    auto val =  mono_string_to_utf8(str);
    std::cout << name << std::endl;
    std::cout << val << std::endl;
    mono_jit_cleanup (domain);

}