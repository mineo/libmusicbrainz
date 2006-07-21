/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id$
 */
 
#ifndef __MUSICBRAINZ3_WEBSERVICE_H__
#define __MUSICBRAINZ3_WEBSERVICE_H__

#include <string>
#include <musicbrainz3/musicbrainz.h> 
#include <musicbrainz3/iwebservice.h>

namespace MusicBrainz
{
  
	/**
	 * A web service error has occurred.
	 * 
	 * This is the base class for several other web service related
	 * exceptions.
	 */
	class MB_API WebServiceError : public Exception
	{
	public:
		WebServiceError(const std::string &msg = std::string()) : Exception(msg) {}
	};
	
	/**
	 * Getting a server connection failed.
	 *
	 * This exception is mostly used if the client couldn't connect to
	 * the server because of an invalid host name or port. It doesn't
	 * make sense if the web service in question doesn't use the network. 
	 */
	class MB_API ConnectionError : public WebServiceError
	{
	public:
		ConnectionError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * Connection to a server timed out.
	 *
	 */
	class MB_API TimeOutError : public WebServiceError
	{
	public:
		TimeOutError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * No resource with the given ID exists.
	 */
	class MB_API ResourceNotFoundError : public WebServiceError
	{
	public:
		ResourceNotFoundError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * Authentication failed.
	 *
	 * This is thrown if user name, password or realm were invalid while
	 * trying to access a protected resource. 
	 */
	class MB_API AuthenticationError : public WebServiceError
	{
	public:
		AuthenticationError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * The returned resource was invalid.
	 *
	 * This may be due to a malformed XML document or if the requested
	 * data wasn't part of the response. It can only occur in case of
	 * bugs in the web service itself. 
	 */
	class MB_API ResponseError : public WebServiceError
	{
	public:
		ResponseError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * An invalid request was made.
	 *
	 * This exception is raised if the client made an invalid request.
	 * That could be syntactically invalid identifiers or unknown or
	 * invalid parameter values. 
	 */
	class MB_API RequestError : public WebServiceError
	{
	public:
		RequestError(const std::string &msg = std::string()) : WebServiceError(msg) {}
	};
	
	/**
	 * An interface to the MusicBrainz XML web service via HTTP.
	 *
	 * By default, this class uses the MusicBrainz server but may be
	 * configured for accessing other servers as well using the
	 * constructor (WebService::WebService). This implements IWebService, so
	 * additional documentation on method parameters can be found there.
	 */
	
	class MB_API WebService : public IWebService
	{
	public:
	
		/**
		 * Constructor.
		 * 
		 * This can be used without parameters. In this case, the
		 * MusicBrainz server will be used.
		 *
		 * @param host a string containing a host name
		 * @param port an integer containing a port number
		 * @param pathPrefix a string prepended to all URLs
		 * @param username a string containing a MusicBrainz user name
		 * @param password a string containing the user's password
		 * @param realm a string containing the realm used for authentication
		 */
		WebService(const std::string &host = "musicbrainz.org",
				   const int port = 80,
				   const std::string &pathPrefix = "/ws",
				   const std::string &username = std::string(),
				   const std::string &password = std::string(),
				   const std::string &realm = "musicbrainz.org");

		void setHost(const std::string &host);
		std::string getHost() const;
		
		void setPort(const int port);
		int getPort() const;
		
		void setPathPrefix(const std::string &pathPrefix);
		std::string getPathPrefix() const;
		
		void setUserName(const std::string &username);
		std::string getUserName() const;
		
		void setPassword(const std::string &password);
		std::string getPassword() const;
		
		void setRealm(const std::string &realm);
		std::string getRealm() const;
		
		void setProxyHost(const std::string &host);
		std::string getProxyHost() const;
		
		void setProxyPort(const int port);
		int getProxyPort() const;
		
		void setProxyUserName(const std::string &username);
		std::string getProxyUserName() const;
		
		void setProxyPassword(const std::string &password);
		std::string getProxyPassword() const;
		
		/**
		 * Query the web service via HTTP-GET.
		 *
		 * Returns a string containing the result or raises a
		 * WebServiceError. Conditions leading to errors may be
		 * invalid entities, IDs, \a include or \a filter parameters
		 * and unsupported version numbers.
		 *
		 * @throw ConnectionError couldn't connect to server
		 * @throw RequestError invalid IDs or parameters
		 * @throw AuthenticationError invalid user name and/or password
		 * @throw ResourceNotFoundError resource doesn't exist
		 * 
		 * @see IWebService::get  		 
		 */
		std::string get(const std::string &entity,
						const std::string &id,
						const IIncludes::IncludeList &include,
						const IFilter::ParameterList &filter,
						const std::string &version = "1"); 

		/**
		 * Send data to the web service via HTTP-POST.
		 *
		 * Note that this may require authentication. You can set
		 * user name, password and realm in the constructor
		 * (WebService::WebService).
		 * 
		 * @throw ConnectionError couldn't connect to server
		 * @throw RequestError invalid IDs or parameters
		 * @throw AuthenticationError invalid user name and/or password
		 * @throw ResourceNotFoundError resource doesn't exist
		 * 
		 * @see IWebService::post 
		 */		 
		 void post(const std::string &entity,
				   const std::string &id,
				   const std::string &data,
				   const std::string &version = "1");
		
		/**
		 * Initialized networking environment required by the web service.
		 *
		 * @note You must call this function at start of your program.
		 */
		static void init();
		
	private:
	
		static int httpAuth(void *userdata, const char *realm, int attempts,
							char *username, char *password);
		static int proxyAuth(void *userdata, const char *realm, int attempts,
							char *username, char *password);
		static int httpResponseReader(void *userdata, const char *buf, size_t len);
	
		std::string host;
		int port;
		std::string pathPrefix;
		std::string username;
		std::string password;
		std::string realm;
		std::string proxyHost;
		int proxyPort;
		std::string proxyUserName;
		std::string proxyPassword;
		
		static std::string systemProxyHost;
		static int systemProxyPort;
		static std::string systemProxyUserName;
		static std::string systemProxyPassword;
		
	};
	
}

#endif