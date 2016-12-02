/*
 * EventClient.h
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

#ifndef EVENTCLIENT_H_
#define EVENTCLIENT_H_

#include "data/EID.h"
#include <ibrcommon/net/socketstream.h>
#include <ibrcommon/thread/Thread.h>

namespace dtn
{
	namespace api
	{

		class EventClient
		{
			public:
				/**
				 *
				 */
				class GetValueException : public ibrcommon::Exception
				{
				public:
					GetValueException(std::string what = "Unable to get value.") throw() : ibrcommon::Exception(what) {};
				};

				class Event
				{
					public:
						Event() {};
						virtual ~Event() {};
						virtual const std::string getName() const = 0;
				};

				class EventReceiver
				{
					public:
						virtual ~EventReceiver() {};
						virtual void raiseEvent(dtn::api::EventClient::Event* e) = 0;
				};

				class NodeEvent : public dtn::api::EventClient::Event
				{
					public:
						NodeEvent(std::string& event, std::string& action, dtn::data::EID& eid) :
							_event(event), _action(action), _eid(eid) {};
						virtual ~NodeEvent() {};
						const std::string getName() const { return "NodeEvent"; };
						std::string getEvent() { return _event; };
						std::string getAction() { return _action; };
						dtn::data::EID getEID() { return _eid; };
					private:
						std::string _event;
						std::string _action;
						dtn::data::EID _eid;
				};

				class GlobalEvent : public dtn::api::EventClient::Event
				{
					public:
						GlobalEvent(std::string& event, std::string& action) :
							_event(event), _action(action) {};
						virtual ~GlobalEvent() {};
						const std::string getName() const { return "GlobalEvent"; };
						std::string getEvent() { return _event; };
						std::string getAction() { return _action; };
					private:
						std::string _event;
						std::string _action;
				};

				class CustodyEvent : public dtn::api::EventClient::Event
				{
					public:
						CustodyEvent(std::string& event, std::string& action, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, dtn::data::Number& lifetime, dtn::data::Number& procflags, dtn::data::EID& destination, bool& isFragment, dtn::data::Number& appdatalength, dtn::data::Number& fragmentoffset) :
							_event(event), _action(action), _source(source), _timestamp(timestamp), _lifetime(lifetime), _procflags(procflags), _destination(destination), _isFragment(isFragment), _appdatalength(appdatalength), _fragmentoffset(fragmentoffset) {};
						virtual ~CustodyEvent() {};
						const std::string getName() const { return "CustodyEvent"; };
						std::string getEvent() { return _event; };
						std::string getAction() { return _action; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						dtn::data::Number getLifetime() { return _lifetime; };
						dtn::data::Number getProcflags() { return _procflags; };
						dtn::data::EID getDestination() { return _destination; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getAppdatalength() { return _appdatalength; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
					private:
						std::string _event;
						std::string _action;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						dtn::data::Number _lifetime;
						dtn::data::Number _procflags;
						dtn::data::EID _destination;
						bool _isFragment;
						dtn::data::Number _appdatalength;
						dtn::data::Number _fragmentoffset;
				};

				class TransferAbortedEvent : public dtn::api::EventClient::Event
				{
					public:
						TransferAbortedEvent(std::string& event, dtn::data::EID& peer, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, bool& isFragment, dtn::data::Number& fragmentoffset, dtn::data::Number& fragmentpayload) :
							_event(event), _peer(peer), _source(source), _timestamp(timestamp), _sequencenumber(sequencenumber), _isFragment(isFragment), _fragmentpayload(fragmentpayload), _fragmentoffset(fragmentoffset) {};
						virtual ~TransferAbortedEvent() {};
						const std::string getName() const { return "TransferAbortedEvent"; };
						std::string getEvent() { return _event; };
						dtn::data::EID getPeer() { return _peer; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
						dtn::data::Number getFragmentpayload() { return _fragmentpayload; };
					private:
						std::string _event;
						dtn::data::EID _peer;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						bool _isFragment;
						dtn::data::Number _fragmentoffset;
						dtn::data::Number _fragmentpayload;
				};

				class TransferCompletedEvent : public dtn::api::EventClient::Event
				{
					public:
						TransferCompletedEvent(std::string& event, dtn::data::EID& peer, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, dtn::data::Number& lifetime, dtn::data::Number& procflags, dtn::data::EID& destination, bool& isFragment, dtn::data::Number& appdatalength, dtn::data::Number& fragmentoffset) :
							_event(event), _peer(peer), _source(source), _timestamp(timestamp), _sequencenumber(sequencenumber), _lifetime(lifetime), _procflags(procflags), _destination(destination), _isFragment(isFragment), _appdatalength(appdatalength), _fragmentoffset(fragmentoffset) {};
						virtual ~TransferCompletedEvent() {};
						const std::string getName() const { return "TransferCompletedEvent"; };
						std::string getEvent() { return _event; };
						dtn::data::EID getPeer() { return _peer; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						dtn::data::Number getLifetime() { return _lifetime; };
						dtn::data::Number getProcflags() { return _procflags; };
						dtn::data::EID getDestination() { return _destination; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getAppdatalength() { return _appdatalength; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
					private:
						std::string _event;
						dtn::data::EID _peer;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						dtn::data::Number _lifetime;
						dtn::data::Number _procflags;
						dtn::data::EID _destination;
						bool _isFragment;
						dtn::data::Number _appdatalength;
						dtn::data::Number _fragmentoffset;
				};

				class ConnectionEvent : public dtn::api::EventClient::Event
				{
					public:
						ConnectionEvent(std::string& event, std::string& action, dtn::data::EID& peer) :
							_event(event), _action(action), _peer(peer) {};
						virtual ~ConnectionEvent() {};
						const std::string getName() const { return "ConnectionEvent"; };
						std::string getEvent() { return _event; };
						std::string getAction() { return _action; };
						dtn::data::EID getPeer() { return _peer; };
					private:
						std::string _event;
						std::string _action;
						dtn::data::EID _peer;
				};

				class QueueBundleEvent : public dtn::api::EventClient::Event
				{
					public:
						QueueBundleEvent(std::string& event, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, dtn::data::Number& lifetime, dtn::data::Number& procflags, dtn::data::EID& destination, bool& isFragment, dtn::data::Number& appdatalength, dtn::data::Number& fragmentoffset) :
							_event(event), _source(source), _timestamp(timestamp), _sequencenumber(sequencenumber), _lifetime(lifetime), _procflags(procflags), _destination(destination), _isFragment(isFragment), _appdatalength(appdatalength), _fragmentoffset(fragmentoffset) {};
						virtual ~QueueBundleEvent() {};
						const std::string getName() const { return "QueueBundleEvent"; };
						std::string getEvent() { return _event; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						dtn::data::Number getLifetime() { return _lifetime; };
						dtn::data::Number getProcflags() { return _procflags; };
						dtn::data::EID getDestination() { return _destination; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getAppdatalength() { return _appdatalength; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
					private:
						std::string _event;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						dtn::data::Number _lifetime;
						dtn::data::Number _procflags;
						dtn::data::EID _destination;
						bool _isFragment;
						dtn::data::Number _appdatalength;
						dtn::data::Number _fragmentoffset;
				};

				class BundlePurgeEvent : public dtn::api::EventClient::Event
				{
					public:
						BundlePurgeEvent(std::string& event, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, dtn::data::Number& lifetime, dtn::data::Number& procflags, dtn::data::EID& destination, bool& isFragment, dtn::data::Number& appdatalength, dtn::data::Number& fragmentoffset) :
							_event(event), _source(source), _timestamp(timestamp), _sequencenumber(sequencenumber), _lifetime(lifetime), _procflags(procflags), _destination(destination), _isFragment(isFragment), _appdatalength(appdatalength), _fragmentoffset(fragmentoffset) {};
						virtual ~BundlePurgeEvent() {};
						const std::string getName() const { return "BundlePurgeEvent"; };
						std::string getEvent() { return _event; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						dtn::data::Number getLifetime() { return _lifetime; };
						dtn::data::Number getProcflags() { return _procflags; };
						dtn::data::EID getDestination() { return _destination; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getAppdatalength() { return _appdatalength; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
					private:
						std::string _event;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						dtn::data::Number _lifetime;
						dtn::data::Number _procflags;
						dtn::data::EID _destination;
						bool _isFragment;
						dtn::data::Number _appdatalength;
						dtn::data::Number _fragmentoffset;
				};

				class BundleExpiredEvent : public dtn::api::EventClient::Event
				{
					public:
						BundleExpiredEvent(std::string& event, dtn::data::EID& source, dtn::data::Timestamp& timestamp, dtn::data::Number& sequencenumber, bool& isFragment, dtn::data::Number& payloadlength, dtn::data::Number& fragmentoffset) :
							_event(event), _source(source), _timestamp(timestamp), _sequencenumber(sequencenumber), _isFragment(isFragment), _payloadlength(payloadlength), _fragmentoffset(fragmentoffset) {};
						virtual ~BundleExpiredEvent() {};
						const std::string getName() const { return "BundleExpiredEvent"; };
						std::string getEvent() { return _event; };
						dtn::data::EID getSource() { return _source; };
						dtn::data::Timestamp getTimestamp() { return _timestamp; };
						dtn::data::Number getSequencenumber() { return _sequencenumber; };
						bool isFragment() { return _isFragment; };
						dtn::data::Number getPayloadlength() { return _payloadlength; };
						dtn::data::Number getFragmentoffset() { return _fragmentoffset; };
					private:
						std::string _event;
						dtn::data::EID _source;
						dtn::data::Timestamp _timestamp;
						dtn::data::Number _sequencenumber;
						bool _isFragment;
						dtn::data::Number _payloadlength;
						dtn::data::Number _fragmentoffset;
				};


				EventClient(ibrcommon::socketstream& stream);
				virtual ~EventClient();

				void addReceiver(EventReceiver* recv);
				void removeReceiver(EventReceiver* recv);

				void connect();

			private:
				/**
				 * This sub-class implements the asynchronous receiver for the connection.
				 * In the run routine a blocking read is called and tries to convert the
				 * incoming data into event calls.
				 */
				class AsyncReceiver : public ibrcommon::JoinableThread
				{
					public:
						/**
						 * Constructor for the synchronous receiver class. It requires the reference to
						 * the Client class for calling the received() methods.
						 * @param client Reference to the client object.
						 */
						AsyncReceiver(ibrcommon::socketstream& stream, dtn::api::EventClient* client);

						/**
						 * Destructor of the asynchronous receiver. It do a join() call on the
						 * JoinableThread object and thus waits for the end of the run() method.
						 */
						virtual ~AsyncReceiver();

					protected:
						/**
						 * The run routine try to retrieve bundles from the stream continuously.
						 * It aborts if the stream of the client went bad or an error occurred during
						 * the deserialization.
						 */
						void run() throw ();

						/**
						 * Aborts the receiver thread
						 * @return
						 */
						void __cancellation() throw ();

					private:
						// member variable for the reference to the client object
						ibrcommon::socketstream& _stream;

						std::string getValue(std::string field);

						bool _running;

						dtn::api::EventClient* _client;
				};

				void raise(dtn::api::EventClient::Event* e);

				// TCP stream reference to send/receive data to the daemon
				ibrcommon::socketstream& _stream;

				// The asynchronous receiver thread which receives incoming bundles
				EventClient::AsyncReceiver _receiver;

				std::list<dtn::api::EventClient::EventReceiver*> _eventReceiver;
		};

	}
}

#endif /* EVENTCLIENT_H_ */
