// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from urc_msgs:action/NavigateToWaypoint.idl
// generated code does not contain a copyright notice

#ifndef URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__BUILDER_HPP_
#define URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "urc_msgs/action/detail/navigate_to_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_Goal_enforce_goal_heading
{
public:
  explicit Init_NavigateToWaypoint_Goal_enforce_goal_heading(::urc_msgs::action::NavigateToWaypoint_Goal & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_Goal enforce_goal_heading(::urc_msgs::action::NavigateToWaypoint_Goal::_enforce_goal_heading_type arg)
  {
    msg_.enforce_goal_heading = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Goal msg_;
};

class Init_NavigateToWaypoint_Goal_has_goal
{
public:
  explicit Init_NavigateToWaypoint_Goal_has_goal(::urc_msgs::action::NavigateToWaypoint_Goal & msg)
  : msg_(msg)
  {}
  Init_NavigateToWaypoint_Goal_enforce_goal_heading has_goal(::urc_msgs::action::NavigateToWaypoint_Goal::_has_goal_type arg)
  {
    msg_.has_goal = std::move(arg);
    return Init_NavigateToWaypoint_Goal_enforce_goal_heading(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Goal msg_;
};

class Init_NavigateToWaypoint_Goal_has_path
{
public:
  explicit Init_NavigateToWaypoint_Goal_has_path(::urc_msgs::action::NavigateToWaypoint_Goal & msg)
  : msg_(msg)
  {}
  Init_NavigateToWaypoint_Goal_has_goal has_path(::urc_msgs::action::NavigateToWaypoint_Goal::_has_path_type arg)
  {
    msg_.has_path = std::move(arg);
    return Init_NavigateToWaypoint_Goal_has_goal(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Goal msg_;
};

class Init_NavigateToWaypoint_Goal_goal
{
public:
  explicit Init_NavigateToWaypoint_Goal_goal(::urc_msgs::action::NavigateToWaypoint_Goal & msg)
  : msg_(msg)
  {}
  Init_NavigateToWaypoint_Goal_has_path goal(::urc_msgs::action::NavigateToWaypoint_Goal::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return Init_NavigateToWaypoint_Goal_has_path(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Goal msg_;
};

class Init_NavigateToWaypoint_Goal_path
{
public:
  Init_NavigateToWaypoint_Goal_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_Goal_goal path(::urc_msgs::action::NavigateToWaypoint_Goal::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_NavigateToWaypoint_Goal_goal(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_Goal>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_Goal_path();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_Result_error_code
{
public:
  explicit Init_NavigateToWaypoint_Result_error_code(::urc_msgs::action::NavigateToWaypoint_Result & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_Result error_code(::urc_msgs::action::NavigateToWaypoint_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Result msg_;
};

class Init_NavigateToWaypoint_Result_result
{
public:
  Init_NavigateToWaypoint_Result_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_Result_error_code result(::urc_msgs::action::NavigateToWaypoint_Result::_result_type arg)
  {
    msg_.result = std::move(arg);
    return Init_NavigateToWaypoint_Result_error_code(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_Result>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_Result_result();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_Feedback_replan_count
{
public:
  explicit Init_NavigateToWaypoint_Feedback_replan_count(::urc_msgs::action::NavigateToWaypoint_Feedback & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_Feedback replan_count(::urc_msgs::action::NavigateToWaypoint_Feedback::_replan_count_type arg)
  {
    msg_.replan_count = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Feedback msg_;
};

class Init_NavigateToWaypoint_Feedback_is_planning
{
public:
  explicit Init_NavigateToWaypoint_Feedback_is_planning(::urc_msgs::action::NavigateToWaypoint_Feedback & msg)
  : msg_(msg)
  {}
  Init_NavigateToWaypoint_Feedback_replan_count is_planning(::urc_msgs::action::NavigateToWaypoint_Feedback::_is_planning_type arg)
  {
    msg_.is_planning = std::move(arg);
    return Init_NavigateToWaypoint_Feedback_replan_count(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Feedback msg_;
};

class Init_NavigateToWaypoint_Feedback_distance_to_goal
{
public:
  Init_NavigateToWaypoint_Feedback_distance_to_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_Feedback_is_planning distance_to_goal(::urc_msgs::action::NavigateToWaypoint_Feedback::_distance_to_goal_type arg)
  {
    msg_.distance_to_goal = std::move(arg);
    return Init_NavigateToWaypoint_Feedback_is_planning(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_Feedback>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_Feedback_distance_to_goal();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_SendGoal_Request_goal
{
public:
  explicit Init_NavigateToWaypoint_SendGoal_Request_goal(::urc_msgs::action::NavigateToWaypoint_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Request goal(::urc_msgs::action::NavigateToWaypoint_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Request msg_;
};

class Init_NavigateToWaypoint_SendGoal_Request_goal_id
{
public:
  Init_NavigateToWaypoint_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_SendGoal_Request_goal goal_id(::urc_msgs::action::NavigateToWaypoint_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_NavigateToWaypoint_SendGoal_Request_goal(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_SendGoal_Request>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_SendGoal_Request_goal_id();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_SendGoal_Response_stamp
{
public:
  explicit Init_NavigateToWaypoint_SendGoal_Response_stamp(::urc_msgs::action::NavigateToWaypoint_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Response stamp(::urc_msgs::action::NavigateToWaypoint_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Response msg_;
};

class Init_NavigateToWaypoint_SendGoal_Response_accepted
{
public:
  Init_NavigateToWaypoint_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_SendGoal_Response_stamp accepted(::urc_msgs::action::NavigateToWaypoint_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_NavigateToWaypoint_SendGoal_Response_stamp(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_SendGoal_Response>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_SendGoal_Response_accepted();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_GetResult_Request_goal_id
{
public:
  Init_NavigateToWaypoint_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::urc_msgs::action::NavigateToWaypoint_GetResult_Request goal_id(::urc_msgs::action::NavigateToWaypoint_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_GetResult_Request>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_GetResult_Request_goal_id();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_GetResult_Response_result
{
public:
  explicit Init_NavigateToWaypoint_GetResult_Response_result(::urc_msgs::action::NavigateToWaypoint_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_GetResult_Response result(::urc_msgs::action::NavigateToWaypoint_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_GetResult_Response msg_;
};

class Init_NavigateToWaypoint_GetResult_Response_status
{
public:
  Init_NavigateToWaypoint_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_GetResult_Response_result status(::urc_msgs::action::NavigateToWaypoint_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_NavigateToWaypoint_GetResult_Response_result(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_GetResult_Response>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_GetResult_Response_status();
}

}  // namespace urc_msgs


namespace urc_msgs
{

namespace action
{

namespace builder
{

class Init_NavigateToWaypoint_FeedbackMessage_feedback
{
public:
  explicit Init_NavigateToWaypoint_FeedbackMessage_feedback(::urc_msgs::action::NavigateToWaypoint_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::urc_msgs::action::NavigateToWaypoint_FeedbackMessage feedback(::urc_msgs::action::NavigateToWaypoint_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_FeedbackMessage msg_;
};

class Init_NavigateToWaypoint_FeedbackMessage_goal_id
{
public:
  Init_NavigateToWaypoint_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NavigateToWaypoint_FeedbackMessage_feedback goal_id(::urc_msgs::action::NavigateToWaypoint_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_NavigateToWaypoint_FeedbackMessage_feedback(msg_);
  }

private:
  ::urc_msgs::action::NavigateToWaypoint_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::urc_msgs::action::NavigateToWaypoint_FeedbackMessage>()
{
  return urc_msgs::action::builder::Init_NavigateToWaypoint_FeedbackMessage_goal_id();
}

}  // namespace urc_msgs

#endif  // URC_MSGS__ACTION__DETAIL__NAVIGATE_TO_WAYPOINT__BUILDER_HPP_
