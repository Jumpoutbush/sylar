#include "http_server.h"
#include "../log.h"

namespace sylar {
namespace http {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

HttpServer::HttpServer (bool keepalive
                        ,sylar::IOManager* worker
                        ,sylar::IOManager* io_worker
                        ,sylar::IOManager* accept_worker
                        )
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
                << " client:" << *client << " keep_alive=" << m_isKeepalive;
            break;
        }

        HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                            ,req->isClose() || !m_isKeepalive));
        m_dispatch->handle(req, rsp, session);
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
