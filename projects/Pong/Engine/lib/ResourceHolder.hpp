#pragma once

#include <assert.h>
#include <iostream>

///////////////////////////////////
/// \brief A utility class for managing and accessing game resources.
///
/// This class provides additional functionality to load, store and retrieve various game resources.
/// Resources are identified by unique identifiers.
///
/// \tparam Resource Type of the resource to be managed.
/// \tparam Identifier Type of identifier used to uniquely identify resources.
///
/////////////////////////////////// 
template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	////////////////////////////////
	/// \brief Loads a resource from a path.
	///
	/// This function loads a resource from a specified file path into memory.
	///
	/// \param id The identifier for the resource.
	/// \param path The path to the file to load as resource.
	///
	//////////////////////////////// 
	void Load(Identifier id, const std::string& path);


	////////////////////////////////
	/// \brief Loads a resource from a file with additional parameters.
	///
	/// \tparam Parameter Type of additional parameter(s) required for loading the resource.
	/// \param id The identifier for the resource.
	/// \param path The name of the file from which to load the resource.
	/// \param secondParam Additional parameter(s) required from loading the resource.
	///
	////////////////////////////////
	template <typename Parameter>
	void Load(Identifier id, const std::string& path, const Parameter& secondParam);


	// Retrieves a mutable reference to a resource by its identifier.
	Resource& Get(Identifier id);

	// Retrieves a constant reference to a resource by its identifier.
	const Resource& Get(Identifier id) const;

private:
	// Map to store resources associated with their identifiers.
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& path)
{
	// load in a new resource
	std::unique_ptr<Resource> resource(new Resource());

	if(!resource->loadFromFile(path))
		throw std::runtime_error("ResourceHolder::Load - Failed to Load: " + path);

	// Insert the resource to the resource map
	const auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);

	std::cout << "Loaded in: " << path << "\n";
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& path, const Parameter& secondParam)
{
	// load in a new resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(path, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load: " + path);

	// insert the resource to the resource map
	const auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	// Find the resource with the id
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	// Return the found resource
	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	// Find the resource with the id
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}
