#include <iostream>

#include <string>
#include <Poco/Net/HTTPClientSession.h>
//#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>
#include <sstream>

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::NetException;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;

int main() {
    URI url("http://api.open-notify.org/astros.json");

    std::string path(url.getPathAndQuery());
    if (path.empty()) {
        path = "/";
    }


    HTTPClientSession session(url.getHost(), url.getPort());

//    https example
//    const Poco::Net::Context::Ptr context = new Poco::Net::Context(
//            Poco::Net::Context::CLIENT_USE, "", "", "",
//            Poco::Net::Context::VERIFY_NONE, 9, false,
//            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
//    HTTPRequest req(HTTPRequest::HTTP_GET, path, context);

    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    std::cout << url.getHost() << std::endl;
    std::cout << url.getPort() << std::endl;
    std::cout << path << std::endl;

    session.sendRequest(req);
    HTTPResponse res;

    //接收结果
    std::istream &rs = session.receiveResponse(res);
    int result = (int) res.getStatus();
    std::cout << "result:" << result
              << ", reason:" << res.getReason()
              << std::endl;
    if (result == Poco::Net::HTTPResponse::HTTP_OK) {
        std::ostringstream ostr1;
        StreamCopier::copyStream(rs, ostr1);
        std::string strData = ostr1.str(); //返回的结果
        std::cout << "data:" << strData << std::endl;
        res.write(ostr1);
        std::string dumpData = ostr1.str();
        return 1;
    } else {
        return 0;
    }




}