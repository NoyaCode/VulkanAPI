#pragma once
#include <vector>
#include <iostream>
#include "Utils.hpp"


namespace Resources
{
    class  IResource
    {

    public:
        IResource() {}
        virtual ~IResource() {}

        virtual void Load(const char* path) = 0;
        virtual void Unload() = 0;
        virtual void SetUp() = 0;
    };

    class Mesh : public IResource
    {

    public:
        std::vector<Vertex> vertices;
        VkBuffer vertexBuffer;

        std::vector<uint32_t> indices;
        VkBuffer indexBuffer;

    private:
        VkDeviceMemory vertexBufferMemory;
        VkDeviceMemory indexBufferMemory;

    public:
        Mesh() {};
        ~Mesh() {};
        void Load(const char* path);
        void Unload();
        void SetUp();

    private:
        void CreateVertexBuffer();
        void CreateIndexBuffer();
    };



    class Texture : public IResource
    {

    public:
        VkImage textureImage;
        VkImageView textureImageView;
        VkSampler textureSampler;

    private:
        VkDeviceMemory textureImageMemory;

    public:
        Texture() {};
        ~Texture() {};
        void Load(const char* path);
        void Unload();
        void SetUp();

    private:
        void CreateTextureImageView();
        void CreateTextureSampler();
    };
}

