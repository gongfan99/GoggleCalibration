#ifndef __OZO_SERVER_PP_HPP__
#define __OZO_SERVER_PP_HPP__

#include "./websocketpp/config/asio_no_tls.hpp"
#include "./websocketpp/server.hpp"
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/format.hpp>
#include <fstream>
#include <sstream>

namespace ozo {

class Server_pp {
public:
	//external input interfaces
	float *distortionK;
	float *chromaAbParameter;
	
	//external output interfaces
	bool outputReady;

	Server_pp();
	~Server_pp();
	void process();
private:
	websocketpp::server<websocketpp::config::asio> server;
	websocketpp::connection_hdl mHandle;
	bool mSocketConnected;
	void on_open(websocketpp::connection_hdl hdl);
	void on_close(websocketpp::connection_hdl hdl);
	void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg);
	void on_fail(websocketpp::connection_hdl hdl);
};

} //namespace ozo

#endif // __OZO_SERVER_PP_HPP__