#include "callback.h"

#include <iostream>

namespace BiosMqtt {

	void Callback::connection_lost(const std::string& cause) {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	// We're not subscrived to anything, so this should never be called.
	void Callback::message_arrived(const std::string& topic, mqtt::message_ptr msg) {
	}

	void Callback::delivery_complete(mqtt::idelivery_token_ptr tok) {
		std::cout << "\n\t[Delivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << "]" << std::endl;
	}

};
