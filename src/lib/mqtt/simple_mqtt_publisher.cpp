#include "simple_mqtt_publisher.h"

#include <iostream>

namespace BiosMqtt {

	SimpleMqttPublisher::SimpleMqttPublisher(std::string address, std::string clientId) {

    client = new mqtt::client(address, clientId, &store);
    client->set_callback(callback);

    mqtt::connect_options connectionOptions;
    connectionOptions.set_keep_alive_interval(20);
    connectionOptions.set_clean_session(true);

    isConnected = false;

    connect();
  }

	SimpleMqttPublisher::~SimpleMqttPublisher(void) {
    disconnect();
    delete client;
  }

  void SimpleMqttPublisher::connect(void) {
    try {
      std::cout << "Connecting..." << std::flush;
      client->connect(connectionOptions);
      isConnected = true;
      std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
      std::cerr << "Error: " << exc.what() << " ["
        << exc.get_reason_code() << "]" << std::endl;
    }
  }

  void SimpleMqttPublisher::set_default_topic(std::string topic) {
    this->defaultTopic = topic;
  }

  void SimpleMqttPublisher::publish(std::string message, QualityOfService qos) {
    publish(message, defaultTopic, qos);
  }

  void SimpleMqttPublisher::publish(std::string message, std::string topic, QualityOfService qos) {
    try {
      std::cout << "Sending message..." << std::flush;
      mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(message);
      pubmsg->set_qos((int)(qos));
      pubmsg->set_retained(RETAINED);
      client->publish(topic, pubmsg);
      std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
      std::cerr << "Error: " << exc.what() << " ["
        << exc.get_reason_code() << "]" << std::endl;
    }
  }

  void SimpleMqttPublisher::disconnect(void) {
    std::cout << "Disconnecting..." << std::flush;
    client->disconnect();
    std::cout << "OK" << std::endl;
    isConnected = false;
  }

  bool SimpleMqttPublisher::is_connected(void) {
    return isConnected;
  }

};
