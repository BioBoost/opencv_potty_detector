#pragma once

#include "memory_persistence_store.h"
#include "callback.h"
#include "quality_of_service.h"

#include <string>

namespace BiosMqtt {

  class SimpleMqttPublisher
  {
    private:
      MemoryPersistenceStore store;
      mqtt::client * client;
      Callback callback;
      mqtt::connect_options connectionOptions;

      std::string defaultTopic;
      bool isConnected;
      bool retained;

    public:
      SimpleMqttPublisher(std::string address, std::string clientId);
      virtual ~SimpleMqttPublisher(void);

    private:
      void connect(void);
      void disconnect(void);

    public:
      void set_default_topic(std::string topic);
      void set_retained(bool retain);
      void publish(std::string message, std::string topic, QualityOfService qos=AT_MOST_ONCE);
      void publish(std::string message, QualityOfService qos=AT_MOST_ONCE);
      void publish(std::string message);
      bool is_connected(void);

  };

};
