#pragma once

#include "mqtt/ipersistable.h"
#include "mqtt/client.h"
#include <map>

namespace BiosMqtt {

  class MemoryPersistenceStore : public virtual mqtt::iclient_persistence {

    private:
    	bool open_;
    	std::map<std::string, mqtt::ipersistable_ptr> store_;

    public:
    	MemoryPersistenceStore();

    public:
    	virtual void open(const std::string& clientId, const std::string& serverURI);
    	virtual void close();
    	virtual void clear();

    	virtual bool contains_key(const std::string &key);
    	virtual std::vector<std::string> keys() const;

    	virtual mqtt::ipersistable_ptr get(const std::string& key) const;
    	virtual void put(const std::string& key, mqtt::ipersistable_ptr persistable);
    	virtual void remove(const std::string &key);
  };

};
