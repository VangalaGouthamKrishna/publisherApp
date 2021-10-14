#include <mosaiqpp/app.hpp>
#include <mosaiqpp/intercom/publication.hpp>
#include <mosaiqpp/intercom/subscription.hpp>

#include <iomanip>
#include <sstream>
#include <string>

/// A cyclic Mosaiq App in C++ is formed by 3 functions which are methods of a class "Main" (Main is arbitrary)
/// Main::onInitialization()  -> will run once before the cyclic execution starts (optional)
/// Main::onCyclicExecution() -> will run periodically according to a preconfigured cycle time (mandatory)
/// Main::onExit()            -> will run once after finishing the cyclic execution. (optional)
class Main : public MosaiqSdk::CyclicApp
{
private:
  /// Declaration and intialization of members (variables) used in this app
  uint32_t m_Var1 = 0;
  std::stringstream m_Var1String{};

  /// Declaration and initialization Real-time Intercom variables for publishing and subscription
  /// Possible datatypes are:
  /// "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t",
  /// "float", "double", "std::string", "std::vector<std::byte>"
  MosaiqSdk::Intercom::Subscription<uint32_t> m_SubVar1;   ///subscription
  MosaiqSdk::Intercom::Publication<std::string> m_PubVar1String; ///publishing
  
public:
  /// Constructor of class of cyclic app
  Main(MosaiqSdk::Intercom::Broker &&broker) : MosaiqSdk::CyclicApp{std::move(broker)}, 
      // Set up topics to be published and subscribed and link it to local variables
      // Recommended: use public app id (to be found in the app details in the App Inventory) to ensure uniqueness across all apps
      // NOTE: the subscription of an app must match the datatype and topic name of the publication app
      m_SubVar1{getBroker().template subscribe<uint32_t>("rtitesta.lenze.mosaiq/Var1")},
      m_PubVar1String{getBroker().template publish<std::string>("rtitestb.lenze.mosaiq/Var1String")}
  {
  }
  
  /// Called once before cyclic execution (optional)
  void onInitialization()
  {
  }
 
  /// Called periodically according to the predefined cycle time (mandatory)
   void onCyclicExecution()
  {
    m_SubVar1.read(m_Var1);                // read value of subscribed topic and write it to m_Var1
    
    m_Var1String << "0x" << std::hex << std::setfill('0') << std::setw(8) << m_Var1;
    m_PubVar1String.write(m_Var1String.str());   // publish value converted to a string -> the app RTI Test B will subscribe to it, converts it into a hex string and pubslish this string
  }

  /// Called once after cyclic execution (optional)
  void onExit()
  {
  }
};
/// This macro needs to be called for Main to function in the Mosaiq Runtime
MOSAIQ_DECLARE_APP(Main);
