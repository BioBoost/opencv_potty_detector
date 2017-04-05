#pragma once

#include "mqtt/client.h"

namespace BiosMqtt {

  class Callback : public virtual mqtt::callback
  {
    public:
    	virtual void connection_lost(const std::string& cause);
    	virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg);
    	virtual void delivery_complete(mqtt::idelivery_token_ptr tok);
  };

};
