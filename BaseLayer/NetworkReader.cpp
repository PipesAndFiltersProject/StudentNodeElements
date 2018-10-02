//
//  NetworkReader.cpp
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 20.9.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


#include "NetworkReader.h"
#include "NetworkReaderObserver.h"
#include "Log.h"

namespace OHARBase {
	
	/**
	 Constructor to create the reader with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName the host to reading data, including port number. In practise,
	 this should always be local host for reader, i.e. 127.0.0.1.
	 */
	NetworkReader::NetworkReader(const std::string & hostName,
										  NetworkReaderObserver & obs,
										  boost::asio::io_service & io_s)
	:		Networker(hostName, io_s),
			observer(obs),
			TAG("NetworkReader")
	{
        using namespace boost::asio::ip;
		remote_endpoint = std::unique_ptr<udp::endpoint>(new boost::asio::ip::udp::endpoint(udp::v4(), port));
		socket = std::unique_ptr<udp::socket>(new udp::socket(io_s, *remote_endpoint));
	}
	
	/**
	 Constructor to create the reader with host name. See the
	 constructor of Networker class about handling the parameters.
	 @param hostName the host to reading data. In practise,
	 this should always be local host for reader, i.e. 127.0.0.1.
	 @param portNumber The port to read data from.
	 */
	NetworkReader::NetworkReader(const std::string & hostName,
										  int portNumber,
										  NetworkReaderObserver & obs,
										  boost::asio::io_service & io_s)
	:		Networker(hostName, portNumber, io_s),
			observer(obs),
			TAG("NetworkReader")
	{
        using namespace boost::asio::ip;
		remote_endpoint = std::unique_ptr<udp::endpoint>(new udp::endpoint(udp::v4(), port));
		socket = std::unique_ptr<udp::socket>(new udp::socket(io_s, *remote_endpoint));
	}
	
	NetworkReader::~NetworkReader() {
	}
	
	
	
	/** Starts the reader. If necessary, connects to the endpoint and then does
	 asynchronous read. */
	void NetworkReader::start() {
		Log::getInstance().entry(TAG, "Start reading for data...");
		running = true;
		if (!socket->is_open()) {
			Log::getInstance().entry(TAG, "Opening read socket");
			socket->connect(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
		}
		buffer->fill(0);
		socket->async_receive_from(boost::asio::buffer(*buffer),
											*remote_endpoint,
											boost::bind(&NetworkReader::handleReceive, this,
															boost::asio::placeholders::error,
															boost::asio::placeholders::bytes_transferred));
		
		Log::getInstance().entry(TAG, "Async recv ongoing");
	}
	
	/** Handles the incoming data and possible errors. Places finally another read
	 to the socket. 
	 @param error Error code
	 @param bytes_transferred How many bytes came in. */
	void NetworkReader::handleReceive(const boost::system::error_code & error, std::size_t bytes_transferred) {
		Log::getInstance().entry(TAG, "Async recv finished code: %d %s", error.value(), error.message().c_str());
		if (!error || error == boost::asio::error::message_size)
		{
			if (buffer->data()) {
				std::string buf;
				buf.resize(bytes_transferred);
				buf.assign(buffer->begin(), bytes_transferred);
				Log::getInstance().entry(TAG, "Received %d bytes data: %s", bytes_transferred, buf.c_str());
				if (buf.length()>0) {
					Package p;
					if (p.parse(buf)) {
						guard.lock();
						msgQueue.push(p);
						guard.unlock();
						// And when data has been received, notify the observer.
						observer.receivedData();
					}
				}
			} else {
				Log::getInstance().entry(TAG, "Async recv finished but NO data");
			}
			if (running)
			{
				start();
			}
		}
	}
	
	/** Stops the reader by setting the running flag to false, effectively ending the thread
	 loop in the threadFunc(). */
	void NetworkReader::stop() {
		Log::getInstance().entry(TAG, "Stop the reader...");
		if (running) {
			running = false;
			Log::getInstance().entry(TAG, "Shutting down the socket.");
			socket->cancel();
			socket->close();
		}
	}
	
	/** Allows another object to read the package object received from the network.
	 This method should be called by the NetworkReaderObserver only when it has been notified
	 that data has arrived.
	 @return The Package containing the data received from the previous ProcessorNode.
	 */
	Package NetworkReader::read() {
		Log::getInstance().entry(TAG, "Getting results from reader");
		guard.lock();
		Package result;
		if (!msgQueue.empty()) {
			result = msgQueue.front();
			msgQueue.pop();
		}
		guard.unlock();
		return result;
	}
	

} //namespace