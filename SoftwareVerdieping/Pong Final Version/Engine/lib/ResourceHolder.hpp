#pragma once

#include <cassert>
#include <iostream>
#include <map>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	// Loads in a specific resource from the path and assigns it to the ID.
	void Load(Identifier id, const std::string& path);

	// Loads in a specific resource from the path and assigns it to the ID.
	template <typename ShaderParam>
	void Load(Identifier id, const std::string& path, ShaderParam shaderParam);

	// Gathers the const resource via the id of the resource
	Resource& get(Identifier id);

	// Gathers a constant reference to the Resource via the identifier.
	const Resource& get(Identifier id) const;

private:
	// The resource map of the resources.
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& path)
{
	// create a new resource and load it in
	std::unique_ptr<Resource> resource(new Resource());

	if (!resource->loadFromFile(path))
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + path);

	// insert the resource to the map
	const auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename ShaderParam>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& path, ShaderParam shaderParam)
{
	// load in a new resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path, shaderParam))
		throw std::runtime_error("ResourceHolder::Load - Failed to load: " + path);

	// insert the resource to the resource map
	const auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	// Find the resource with the id
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	// Return the found resource
	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	// Find the resource with the id
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	// Return the found resource
	return *found->second;
}
