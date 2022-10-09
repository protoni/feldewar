#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "Shader.h"
#include "Texture.h"

#include <vector>
#include <memory>
#include <string>

namespace ENGINE
{

typedef unsigned int DataObjectId;
typedef std::string DataObjectName;

enum class DataObjectType
{
        TypeUnknown = -1,
        TypeShader,
        TypeTexture
};

struct DataObject
{
    DataObjectId id;
    DataObjectName filename;

    // TODO: maybe not the best idea. Basically used for shaders,
    // since they have vertex- and fragment shaders.
    DataObjectName filename2; 

    //DataObjectBase data;
    Texture texture;
    Shader shader;

    DataObjectType type;

    DataObject()
        : type(DataObjectType::TypeUnknown)
        , id(0)
        , filename("")
        , filename2("")
    {}
};

class DataLoader
{

public:
    DataLoader();
    ~DataLoader();

    static const bool LoadTexture(const char* path, bool useRGBA = false);

    static const bool LoadShader(const char* vertexPath, const char* fragmentPath);

    static const Texture& GetTexture(const char* filename);

    static void Cleanup();

private:
    static std::vector<std::shared_ptr<DataObject>> s_objects;

};

} // namepsace ENGINE
#endif // DATA_LOADER_H