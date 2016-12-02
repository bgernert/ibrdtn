/*
 * EventClient.cpp
 *
 * Copyright (C) 2016 IBR, TU Braunschweig
 *
 * Written-by: Björn Gernert <gernert@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "EventClient.h"

#include <ibrcommon/Logger.h>

namespace dtn
{
	namespace api
	{

		EventClient::AsyncReceiver::AsyncReceiver(ibrcommon::socketstream& stream, dtn::api::EventClient* client)
		 : _stream(stream), _client(client), _running(true)
		{
		}

		EventClient::AsyncReceiver::~AsyncReceiver()
		{
		}

		void EventClient::AsyncReceiver::__cancellation() throw ()
		{
			_running = false;
		}

		void EventClient::AsyncReceiver::run() throw ()
		{
			try {
				while (_running)
				{
					try
					{
						std::string event = getValue("Event");

						// NodeEvent
						if(event.compare("NodeEvent") == 0)
						{
							std::string action(getValue("Action"));
							dtn::data::EID eid(getValue("EID"));

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::NodeEvent* ev = new dtn::api::EventClient::NodeEvent(event, action, eid);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// GlobalEvent
						if(event.compare("GlobalEvent") == 0)
						{
							std::string action(getValue("Action"));

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::GlobalEvent* ev = new dtn::api::EventClient::GlobalEvent(event, action);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// CustodyEvent
						if(event.compare("CustodyEvent") == 0)
						{
							std::string action(getValue("Action"));
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));
							dtn::data::Number lifetime;
							lifetime.fromString(getValue("Lifetime"));
							dtn::data::Number procflags;
							procflags.fromString(getValue("Procflags"));
							dtn::data::EID destination(getValue("Destination"));

							bool isFragment = false;
							dtn::data::Number appdatalength;
							dtn::data::Number fragmentoffset;
							try {
								appdatalength.fromString(getValue("Appdatalength"));
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::CustodyEvent* ev = new dtn::api::EventClient::CustodyEvent(event, action, source, timestamp, sequencenumber, lifetime, procflags, destination, isFragment, appdatalength, fragmentoffset);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// TransferAbortedEvent
						if(event.compare("TransferAbortedEvent") == 0)
						{
							dtn::data::EID peer(getValue("Peer"));
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));

							bool isFragment = false;
							dtn::data::Number fragmentoffset;
							dtn::data::Number fragmentpayload;
							try {
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								fragmentpayload.fromString(getValue("Fragmentpayload"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::TransferAbortedEvent* ev = new dtn::api::EventClient::TransferAbortedEvent(event, peer, source, timestamp, sequencenumber, isFragment, fragmentoffset, fragmentpayload);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// TransferCompletedEvent
						if(event.compare("TransferCompletedEvent") == 0)
						{
							dtn::data::EID peer(getValue("Peer"));
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));
							dtn::data::Number lifetime;
							lifetime.fromString(getValue("Lifetime"));
							dtn::data::Number procflags;
							procflags.fromString(getValue("Procflags"));
							dtn::data::EID destination(getValue("Destination"));

							bool isFragment = false;
							dtn::data::Number appdatalength;
							dtn::data::Number fragmentoffset;
							try {
								appdatalength.fromString(getValue("Appdatalength"));
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::TransferCompletedEvent* ev = new dtn::api::EventClient::TransferCompletedEvent(event, peer, source, timestamp, sequencenumber, lifetime, procflags, destination, isFragment, appdatalength, fragmentoffset);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// ConnectionEvent
						if(event.compare("ConnectionEvent") == 0)
						{
							std::string action(getValue("Action"));
							dtn::data::EID peer(getValue("Peer"));

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::ConnectionEvent* ev = new dtn::api::EventClient::ConnectionEvent(event, action, peer);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// QueueBundleEvent
						if(event.compare("QueueBundleEvent") == 0)
						{
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));
							dtn::data::Number lifetime;
							lifetime.fromString(getValue("Lifetime"));
							dtn::data::Number procflags;
							procflags.fromString(getValue("Procflags"));
							dtn::data::EID destination(getValue("Destination"));

							bool isFragment = false;
							dtn::data::Number appdatalength;
							dtn::data::Number fragmentoffset;
							try {
								appdatalength.fromString(getValue("Appdatalength"));
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::QueueBundleEvent* ev = new dtn::api::EventClient::QueueBundleEvent(event, source, timestamp, sequencenumber, lifetime, procflags, destination, isFragment, appdatalength, fragmentoffset);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// BundlePurgeEvent
						if(event.compare("BundlePurgeEvent") == 0)
						{
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));
							dtn::data::Number lifetime;
							lifetime.fromString(getValue("Lifetime"));
							dtn::data::Number procflags;
							procflags.fromString(getValue("Procflags"));
							dtn::data::EID destination(getValue("Destination"));

							bool isFragment = false;
							dtn::data::Number appdatalength;
							dtn::data::Number fragmentoffset;
							try {
								appdatalength.fromString(getValue("Appdatalength"));
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::BundlePurgeEvent* ev = new dtn::api::EventClient::BundlePurgeEvent(event, source, timestamp, sequencenumber, lifetime, procflags, destination, isFragment, appdatalength, fragmentoffset);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						// BundleExpiredEvent
						if(event.compare("BundleExpiredEvent") == 0)
						{
							dtn::data::EID source(getValue("Source"));
							dtn::data::Timestamp timestamp;
							timestamp.fromString(getValue("Timestamp"));
							dtn::data::Number sequencenumber;
							sequencenumber.fromString(getValue("Sequencenumber"));

							bool isFragment = false;
							dtn::data::Number payloadlength;
							dtn::data::Number fragmentoffset;
							try {
								payloadlength.fromString(getValue("Payloadlength"));
								fragmentoffset.fromString(getValue("Fragmentoffset"));
								isFragment = true;
							} catch (const EventClient::GetValueException& ex) {}

							// Get empty row
							std::string tmp;
							std::getline(_stream, tmp);

							// Raise event
							dtn::api::EventClient::BundleExpiredEvent* ev = new dtn::api::EventClient::BundleExpiredEvent(event, source, timestamp, sequencenumber, isFragment, payloadlength, fragmentoffset);
							_client->raise(ev);
							delete ev;
							ev = 0;
						}

						yield();
					} catch (const EventClient::GetValueException& ex) {
						IBRCOMMON_LOGGER_TAG("EventClient", error) << ex.what() << IBRCOMMON_LOGGER_ENDL;
					}
				}
			} catch (const std::exception& ex) {
				IBRCOMMON_LOGGER_TAG("EventClient::AsyncReceiver", error) << ex.what() << IBRCOMMON_LOGGER_ENDL;
			}
		}

		std::string EventClient::AsyncReceiver::getValue(std::string field)
		{
			std::string value;
			std::string buffer;

			std::getline(_stream, buffer);
			std::string fieldFromStream = buffer.substr(0, (field.length() + 2));

			if(fieldFromStream.compare(field + ": ") == 0)
			{
				return buffer.substr(field.length() + 2);
			} else {
				throw EventClient::GetValueException("Unable to extract value of '" + field + "' from stream.");
			}
		}

		EventClient::EventClient(ibrcommon::socketstream& stream) : _stream(stream), _receiver(stream, this)
		{
		}

		EventClient::~EventClient()
		{
		}


		void EventClient::connect()
		{
			// receive API banner
			std::string buffer;
			std::getline(_stream, buffer);

			// switch to API event mode
			_stream << "protocol event" << std::endl;

			// receive ok
			std::getline(_stream, buffer);

			try {
				// run the receiver
				_receiver.start();
			} catch (const ibrcommon::ThreadException &ex) {
				IBRCOMMON_LOGGER_TAG("EventClient", error) << "failed to start EventClient::Receiver\n" << ex.what() << IBRCOMMON_LOGGER_ENDL;
			}
		}

		void EventClient::addReceiver(EventReceiver* recv)
		{
			_eventReceiver.push_back(recv);
		}

		void EventClient::removeReceiver(EventReceiver* recv)
		{
			_eventReceiver.remove(recv);
		}

		void EventClient::raise(dtn::api::EventClient::Event* e)
		{
			for(std::list<dtn::api::EventClient::EventReceiver*>::iterator it = _eventReceiver.begin(); it != _eventReceiver.end(); ++it)
			{
				(*it)->raiseEvent(e);
			}
		}
	}
}
