#ifndef UV_PORT_MANAGER_HPP
#define UV_PORT_MANAGER_HPP


#include <uv.h>
#include <string>
#include <unordered_map>
#include <vector>

class PortManager {
private:
	enum class Transport : uint8_t {
		UDP = 1, TCP
	};

public:
	static uv_udp_t* BindUdp(std::string &ip);
	static uv_tcp_t* BindTcp(std::string &ip);
	static uv_tcp_t* BindTcp(std::string &ip, uint16_t port);
	static void UnbindUdp(std::string &ip, uint16_t port);
	static void UnbindTcp(std::string &ip, uint16_t port);


private:
	static uv_handle_t* Bind(Transport transport, std::string &ip);
	static uv_handle_t* Bind(Transport transport, std::string &ip, uint16_t port);
	static void Unbind(Transport transport, std::string &ip, uint16_t port);

	static void NormalizeIp(std::string& ip);
	static int GetFamily(std::string &ipstring);


private:
	static std::unordered_map<std::string, std::vector<bool>> mapUdpIpPorts;
	static std::unordered_map<std::string, std::vector<bool>> mapTcpIpPorts;
};

/* Inline static methods. */

inline uv_udp_t* PortManager::BindUdp(std::string &ip) {
	return reinterpret_cast<uv_udp_t*>(Bind(Transport::UDP, ip));
}

inline uv_tcp_t* PortManager::BindTcp(std::string &ip) {
	return reinterpret_cast<uv_tcp_t*>(Bind(Transport::TCP, ip));
}

inline uv_tcp_t* PortManager::BindTcp(std::string &ip, uint16_t port) {
	return reinterpret_cast<uv_tcp_t*>(Bind(Transport::TCP, ip, port));
}

inline void PortManager::UnbindUdp(std::string &ip, uint16_t port) {
	return Unbind(Transport::UDP, ip, port);
}

inline void PortManager::UnbindTcp(std::string &ip, uint16_t port) {
	return Unbind(Transport::TCP, ip, port);
}

#endif
