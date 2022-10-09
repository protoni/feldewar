#include "DataLoader.h"


namespace ENGINE
{

std::vector<std::shared_ptr<DataObject>> DataLoader::s_objects;

DataLoader::DataLoader()
{
    
}
DataLoader::~DataLoader()
{
    //for (auto& object : s_objects) {
    //    delete object;
    //}
}

const bool DataLoader::LoadTexture(const char* path, bool useRGBA)
{
    std::shared_ptr<DataObject> obj = std::make_shared<DataObject>();
    obj->type = DataObjectType::TypeTexture;
    obj->texture = Texture(path, useRGBA);
    obj->id = s_objects.size() + 1;
    obj->filename = std::string(path).substr(std::string(path).find_last_of("/\\") + 1);
    s_objects.push_back(obj);

    return obj->texture.Loaded;
}

const bool DataLoader::LoadShader(const char* vertexPath, const char* fragmentPath)
{
    std::shared_ptr<DataObject> obj = std::make_shared<DataObject>();
    obj->type = DataObjectType::TypeShader;
    obj->shader = Shader(vertexPath, fragmentPath);
    obj->id = s_objects.size() + 1;
    obj->filename = std::string(vertexPath).substr(std::string(vertexPath).find_last_of("/\\") + 1);
    obj->filename2 = std::string(fragmentPath).substr(std::string(fragmentPath).find_last_of("/\\") + 1);
    s_objects.push_back(obj);

    return obj->shader.Loaded;
}

const Texture& DataLoader::GetTexture(const char* filename)
{
    for (auto& object : s_objects) {
        if (object->filename.compare(std::string(filename)) == 0)
            return object->texture;//static_cast<Texture>(object->data);
    }
}

void DataLoader::Cleanup()
{
    for (auto& object : s_objects) {
        if (object->type == DataObjectType::TypeTexture) {
            object->texture.Clear();
        }
    }
}

} // namespace ENGINE