
#include <httplib.h>

#define HTTP_PORT 8090

int main(int argc, char *argv[]) {
    httplib::Server server;

    server.Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    // Match the request path against a regular expression
    // and extract its captures
    server.Get(R"(/numbers/(\d+))",
               [&](const httplib::Request &req, httplib::Response &res) {
                   auto numbers = req.matches[1];
                   res.set_content(numbers, "text/plain");
               });

    // Capture the second segment of the request path as "id" path param
    server.Get("/users/:id",
               [&](const httplib::Request &req, httplib::Response &res) {
                   auto user_id = req.path_params.at("id");
                   res.set_content(user_id, "text/plain");
               });

    // Extract values from HTTP headers and URL query params
    server.Get("/body-header-param",
               [](const httplib::Request &req, httplib::Response &res) {
                   if (req.has_header("Content-Length")) {
                       auto val = req.get_header_value("Content-Length");
                   }
                   if (req.has_param("key")) {
                       auto val = req.get_param_value("key");
                   }
                   res.set_content(req.body, "text/plain");
               });

    server.Get("/stop", [&](const httplib::Request &req,
                            httplib::Response &res) { server.stop(); });

    server.listen("0.0.0.0", HTTP_PORT);

    return 0;
}
