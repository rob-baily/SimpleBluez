#pragma once

#include <simpledbus/advanced/Proxy.h>

#include <simplebluez/Device.h>
#include <simplebluez/interfaces/Adapter1.h>

#include <functional>

namespace SimpleBluez {

class Adapter : public SimpleDBus::Proxy {
  public:
    typedef Adapter1::DiscoveryFilter DiscoveryFilter;

    Adapter(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);
    virtual ~Adapter() = default;

    std::string identifier() const;
    std::string address();
    bool discovering();

    void discovery_filter(const DiscoveryFilter& filter);
    void discovery_start();
    void discovery_stop();

    std::shared_ptr<Device> device_get(const std::string& path);
    void set_on_device_updated(std::function<void(std::shared_ptr<Device> device)> callback);

  private:
    std::shared_ptr<SimpleDBus::Proxy> path_create(const std::string& path) override;
    std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& interface_name) override;

    std::shared_ptr<Adapter1> adapter1();
};

}  // namespace SimpleBluez
