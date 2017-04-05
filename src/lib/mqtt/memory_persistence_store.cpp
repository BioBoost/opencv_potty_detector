#include "memory_persistence_store.h"

#include <iostream>

namespace BiosMqtt {

	MemoryPersistenceStore::MemoryPersistenceStore(void)
    : open_(false) {

  }

	// "Open" the store
	void MemoryPersistenceStore::open(const std::string& clientId, const std::string& serverURI) {
		std::cout << "[Opening persistence for '" << clientId
			<< "' at '" << serverURI << "']" << std::endl;
		open_ = true;
	}

	// Close the persistent store that was previously opened.
	void MemoryPersistenceStore::close() {
		std::cout << "[Closing persistence store.]" << std::endl;
		open_ = false;
	}

	// Clears persistence, so that it no longer contains any persisted data.
	void MemoryPersistenceStore::clear() {
		std::cout << "[Clearing persistence store.]" << std::endl;
		store_.clear();
	}

	// Returns whether or not data is persisted using the specified key.
	bool MemoryPersistenceStore::contains_key(const std::string &key) {
		return store_.find(key) != store_.end();
	}

	// Gets the specified data out of the persistent store.
	mqtt::ipersistable_ptr MemoryPersistenceStore::get(const std::string& key) const {
		std::cout << "[Searching persistence for key '"
			<< key << "']" << std::endl;
		auto p = store_.find(key);
		if (p == store_.end())
			throw mqtt::persistence_exception();
		std::cout << "[Found persistence data for key '"
			<< key << "']" << std::endl;

		return p->second;
	}
	/**
	 * Returns the keys in this persistent data store.
	 */
	std::vector<std::string> MemoryPersistenceStore::keys() const {
		std::vector<std::string> ks;
		for (const auto& k : store_)
			ks.push_back(k.first);
		return ks;
	}

	// Puts the specified data into the persistent store.
	void MemoryPersistenceStore::put(const std::string& key, mqtt::ipersistable_ptr persistable) {
		std::cout << "[Persisting data with key '"
			<< key << "']" << std::endl;

		store_[key] = persistable;
	}

	// Remove the data for the specified key.
	void MemoryPersistenceStore::remove(const std::string &key) {
		std::cout << "[Persistence removing key '" << key << "']" << std::endl;
		auto p = store_.find(key);
		if (p == store_.end())
			throw mqtt::persistence_exception();
		store_.erase(p);
		std::cout << "[Persistence key removed '" << key << "']" << std::endl;
	}

};
