
#include <PwmControl.h>
#include <httplib.h>

#define HTTP_PORT 80
#define LC_PWM_FREQ 400

int main(int argc, char *argv[]) {
    auto pwmControl = LC::PwmFactory().createPwmControl();

    httplib::Server server;

    server.Get("/on", [&pwmControl](const httplib::Request &req,
                                    httplib::Response &res) {
        std::vector<LC::PwmParameter> params{
            LC::PwmParameter(12, LC_PWM_FREQ, 1000000),
            LC::PwmParameter(13, LC_PWM_FREQ, 1000000)};
        pwmControl->set(params);
        res.set_content(R"({"status":"ok"})", "application/json");
    });

    server.Get("/off", [&pwmControl](const httplib::Request &req,
                                     httplib::Response &res) {
        std::vector<LC::PwmParameter> params{
            LC::PwmParameter(12, LC_PWM_FREQ, 0),
            LC::PwmParameter(13, LC_PWM_FREQ, 0)};
        pwmControl->set(params);
        res.set_content(R"({"status":"ok"})", "application/json");
    });

    server.Post("/pwm", [&pwmControl](const httplib::Request &req,
                                      httplib::Response &res) {
        std::vector<LC::PwmParameter> params;
        if (req.has_param("gpio12duty")) {
            auto val = req.get_param_value("gpio12duty");
            params.emplace_back(LC::PwmParameter(12, 400, std::stoi(val)));
        }
        if (req.has_param("gpio13duty")) {
            auto val = req.get_param_value("gpio13duty");
            params.emplace_back(LC::PwmParameter(13, 400, std::stoi(val)));
        }
        pwmControl->set(params);
        res.set_content(R"({"status":"ok"})", "application/json");
    });

    server.Get("/stop", [&](const httplib::Request &req,
                            httplib::Response &res) { server.stop(); });

    server.listen("0.0.0.0", HTTP_PORT);

    return 0;
}
