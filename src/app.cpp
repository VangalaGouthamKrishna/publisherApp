#include <mosaiqpp/app.hpp>
#include <mosaiqpp/intercom/publication.hpp>

#include <iomanip>
#include <sstream>
#include <string>

class PublisherApp : public MosaiqSdk::CyclicApp
{
public:
  PublisherApp(MosaiqSdk::Intercom::Broker&& broker)
    : MosaiqSdk::CyclicApp{std::move(broker)}
    , m_cycleCount{0}
    , m_integralPub{getBroker().template publish<uint32_t>("cycleCounter")}
    , m_stringPub{getBroker().template publish<std::string>("cycleCounterHex")}
  {}

  void onCyclicExecution()
  {
    ++m_cycleCount;
    m_integralPub.write(m_cycleCount);

    std::stringstream sstr;
    sstr << "0x" << std::hex << std::setfill('0') << std::setw(8) << m_cycleCount;
    m_stringPub.write(sstr.str());
  }

private:
  uint32_t m_cycleCount;
  MosaiqSdk::Intercom::Publication<uint32_t> m_integralPub;
  MosaiqSdk::Intercom::Publication<std::string> m_stringPub;
};

MOSAIQ_DECLARE_APP(PublisherApp);