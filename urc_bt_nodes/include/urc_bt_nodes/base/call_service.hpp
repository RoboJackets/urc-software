#ifndef CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__
#define CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__

#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/basic_types.h"

namespace behavior::base
{

class CallService : public BT::SyncActionNode
{
public:
  CallService(const std::string& name) : BT::SyncActionNode(name, {}){};

  BT::NodeStatus tick() override
  {
  }

private:
};

}  // namespace behavior::base

#endif /* CALL_SERVICE_DD53F430_C731_4D3D_93FF_368D153F1B29_HPP__ */
