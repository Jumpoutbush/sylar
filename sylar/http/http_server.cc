#include "http_server.h"
#include "../log.h"

namespace sylar {
namespace http {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

HttpServer::HttpServer (sylar::IOManager* worker
                        ,sylar::IOManager* io_worker
                        ,sylar::IOManager* accept_worker
                        ,bool keepalive)
    :TcpServer(worker, io_worker, accept_worker), m_isKeepalive(keepalive) {
        m_dispatch.reset(new ServletDispatch);
}

void HttpServer::setName(const std::string& v) {
    TcpServer::setName(v);
    m_dispatch->setDefault(std::make_shared<NotFoundServlet>(v));
}

void HttpServer::handleClient(Socket::ptr client) {
    SYLAR_LOG_DEBUG(g_logger) << "handleClient " << *client;
    HttpSession::ptr session(new HttpSession(client));
    do {
        auto req = session->recvRequest();
        if(!req) {
            SYLAR_LOG_DEBUG(g_logger) << "recv http request fail, errno="
                << errno << " errstr=" << strerror(errno)
                << " cliet:" << *client << " keep_alive=" << m_isKeepalive;
            break;
        }

        HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                            ,req->isClose() || !m_isKeepalive));
        // rsp->setBody("hello sylar");
        // SYLAR_LOG_INFO(g_logger) << "request:" << std::endl
        //     << *req;
        // SYLAR_LOG_INFO(g_logger) << "res: " << std::endl
        //     << *req;
        session->sendResponse(rsp);
    } while(m_isKeepalive);
    session->close();
}

}
}
