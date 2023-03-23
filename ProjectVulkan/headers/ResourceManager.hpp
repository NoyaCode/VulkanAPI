#pragma once
#include <iostream>
#include <unordered_map>
#include "IResource.hpp"

namespace Resources
{
    static class ResourceManager
    {
    public:
        ~ResourceManager() {}
        static void DeleteMap()
        {
            for (std::pair<std::string, Resources::IResource*> resource : resources)
            {
                resource.second->Unload();
                delete resource.second;
            }
        }

        template <class T>
        static T* Create(const char* name, const char* path)
        {
            bool IsInherit = std::is_base_of<Resources::IResource, T>::value;
            if (!IsInherit) { abort(); }

            if (resources.find(name) == resources.end())
            {
                Resources::IResource* resource_base = (Resources::IResource*)(new T);
                resource_base->Load(path);
                resources.emplace(name, resource_base);
                return (T*)resource_base;
            }
            else
            {
                std::cout << ">> The name : \"" << name << "\" is already used <<" << std::endl;
                return (T*)resources.at(name);
            }

        }

        template <typename T>
        static T* Get(const char* name)
        {
            return (T*)(resources.find(name)->second);
        }

    private:
        ResourceManager() {};
        static std::unordered_map<std::string, Resources::IResource*> resources;
    };
}