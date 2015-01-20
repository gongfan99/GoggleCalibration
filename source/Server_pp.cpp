#include "Server_pp.hpp"

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace ozo {

Server_pp::Server_pp() : mSocketConnected(false), outputReady(false) {
	server.set_open_handler(bind(&Server_pp::on_open,this,::_1));
	server.set_fail_handler(bind(&Server_pp::on_fail,this,::_1));
	server.set_close_handler(bind(&Server_pp::on_close,this,::_1));
	server.set_message_handler(bind(&Server_pp::on_message,this,::_1,::_2));
	server.clear_access_channels(websocketpp::log::alevel::frame_header | websocketpp::log::alevel::frame_payload);
	
	server.init_asio();
	server.listen(9002);
	server.start_accept();
	std::cout << "Listening to localhost:9002\n";
}

Server_pp::~Server_pp() {
	if (mSocketConnected) server.close(mHandle, websocketpp::close::status::normal, "Connection closed.");
}

void Server_pp::process() {
    if( mSocketConnected && *inputReady ) {
		std::ostringstream tempString;
		//"distortionK" is obfuscated to  "_e"; "chromaAbParameter" is obfuscated to  "_f"
		tempString << "{\"_e\": [" << distortionK[0] << "," << distortionK[1] << "," << distortionK[2] << "," << distortionK[3] << "], ";
		tempString << "\"_f\": [" << chromaAbParameter[0] << "," << chromaAbParameter[1] << "," << chromaAbParameter[2] << "," << chromaAbParameter[3] << "]}";
		//std::cout << tempString.str() << std::endl;
		server.send(mHandle, tempString.str(), websocketpp::frame::opcode::TEXT);
		*inputReady = false;
		outputReady = false;	
	}
	server.poll();
}

void Server_pp::on_open(websocketpp::connection_hdl hdl) {
	mHandle = hdl;
	std::cout << server.get_con_from_hdl(mHandle)->get_host() << std::endl;
    // Only accept connections from another mobile phone
/*     if( server.get_con_from_hdl(mHandle)->get_host() == "localhost"){
        server.close(hdl, websocketpp::close::status::normal, "Connection closed.");
		return;
    } */
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000)); //wait for web side to initialize
    mSocketConnected = true;
    std::cout << "Connected.\n";
}

void Server_pp::on_close(websocketpp::connection_hdl hdl) {
    std::cout << "Disonnected.\n";
    mSocketConnected = false;
}

void Server_pp::on_fail(websocketpp::connection_hdl hdl) {
	std::cout << "Connection failed.\n";
    mSocketConnected = false;
}

void Server_pp::on_message(websocketpp::connection_hdl hdl, 
							websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
    if( (msg->get_payload()) == "image ready"){
		outputReady = true;
    }
}

} //namespace ozo