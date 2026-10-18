// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vectornav_msgs:action/MagCal.idl
// generated code does not contain a copyright notice

#ifndef VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__BUILDER_HPP_
#define VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vectornav_msgs/action/detail/mag_cal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vectornav_msgs
{

namespace action
{


}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_Goal>()
{
  return ::vectornav_msgs::action::MagCal_Goal(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_Result_calib
{
public:
  explicit Init_MagCal_Result_calib(::vectornav_msgs::action::MagCal_Result & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_Result calib(::vectornav_msgs::action::MagCal_Result::_calib_type arg)
  {
    msg_.calib = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_Result msg_;
};

class Init_MagCal_Result_avg_dev
{
public:
  Init_MagCal_Result_avg_dev()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_Result_calib avg_dev(::vectornav_msgs::action::MagCal_Result::_avg_dev_type arg)
  {
    msg_.avg_dev = std::move(arg);
    return Init_MagCal_Result_calib(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_Result>()
{
  return vectornav_msgs::action::builder::Init_MagCal_Result_avg_dev();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_Feedback_samples
{
public:
  explicit Init_MagCal_Feedback_samples(::vectornav_msgs::action::MagCal_Feedback & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_Feedback samples(::vectornav_msgs::action::MagCal_Feedback::_samples_type arg)
  {
    msg_.samples = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_Feedback msg_;
};

class Init_MagCal_Feedback_curr_calib
{
public:
  explicit Init_MagCal_Feedback_curr_calib(::vectornav_msgs::action::MagCal_Feedback & msg)
  : msg_(msg)
  {}
  Init_MagCal_Feedback_samples curr_calib(::vectornav_msgs::action::MagCal_Feedback::_curr_calib_type arg)
  {
    msg_.curr_calib = std::move(arg);
    return Init_MagCal_Feedback_samples(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_Feedback msg_;
};

class Init_MagCal_Feedback_curr_avg_dev
{
public:
  Init_MagCal_Feedback_curr_avg_dev()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_Feedback_curr_calib curr_avg_dev(::vectornav_msgs::action::MagCal_Feedback::_curr_avg_dev_type arg)
  {
    msg_.curr_avg_dev = std::move(arg);
    return Init_MagCal_Feedback_curr_calib(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_Feedback>()
{
  return vectornav_msgs::action::builder::Init_MagCal_Feedback_curr_avg_dev();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_SendGoal_Request_goal
{
public:
  explicit Init_MagCal_SendGoal_Request_goal(::vectornav_msgs::action::MagCal_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_SendGoal_Request goal(::vectornav_msgs::action::MagCal_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_SendGoal_Request msg_;
};

class Init_MagCal_SendGoal_Request_goal_id
{
public:
  Init_MagCal_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_SendGoal_Request_goal goal_id(::vectornav_msgs::action::MagCal_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MagCal_SendGoal_Request_goal(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_SendGoal_Request>()
{
  return vectornav_msgs::action::builder::Init_MagCal_SendGoal_Request_goal_id();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_SendGoal_Response_stamp
{
public:
  explicit Init_MagCal_SendGoal_Response_stamp(::vectornav_msgs::action::MagCal_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_SendGoal_Response stamp(::vectornav_msgs::action::MagCal_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_SendGoal_Response msg_;
};

class Init_MagCal_SendGoal_Response_accepted
{
public:
  Init_MagCal_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_SendGoal_Response_stamp accepted(::vectornav_msgs::action::MagCal_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MagCal_SendGoal_Response_stamp(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_SendGoal_Response>()
{
  return vectornav_msgs::action::builder::Init_MagCal_SendGoal_Response_accepted();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_GetResult_Request_goal_id
{
public:
  Init_MagCal_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vectornav_msgs::action::MagCal_GetResult_Request goal_id(::vectornav_msgs::action::MagCal_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_GetResult_Request>()
{
  return vectornav_msgs::action::builder::Init_MagCal_GetResult_Request_goal_id();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_GetResult_Response_result
{
public:
  explicit Init_MagCal_GetResult_Response_result(::vectornav_msgs::action::MagCal_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_GetResult_Response result(::vectornav_msgs::action::MagCal_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_GetResult_Response msg_;
};

class Init_MagCal_GetResult_Response_status
{
public:
  Init_MagCal_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_GetResult_Response_result status(::vectornav_msgs::action::MagCal_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MagCal_GetResult_Response_result(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_GetResult_Response>()
{
  return vectornav_msgs::action::builder::Init_MagCal_GetResult_Response_status();
}

}  // namespace vectornav_msgs


namespace vectornav_msgs
{

namespace action
{

namespace builder
{

class Init_MagCal_FeedbackMessage_feedback
{
public:
  explicit Init_MagCal_FeedbackMessage_feedback(::vectornav_msgs::action::MagCal_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::vectornav_msgs::action::MagCal_FeedbackMessage feedback(::vectornav_msgs::action::MagCal_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_FeedbackMessage msg_;
};

class Init_MagCal_FeedbackMessage_goal_id
{
public:
  Init_MagCal_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MagCal_FeedbackMessage_feedback goal_id(::vectornav_msgs::action::MagCal_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MagCal_FeedbackMessage_feedback(msg_);
  }

private:
  ::vectornav_msgs::action::MagCal_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::vectornav_msgs::action::MagCal_FeedbackMessage>()
{
  return vectornav_msgs::action::builder::Init_MagCal_FeedbackMessage_goal_id();
}

}  // namespace vectornav_msgs

#endif  // VECTORNAV_MSGS__ACTION__DETAIL__MAG_CAL__BUILDER_HPP_
