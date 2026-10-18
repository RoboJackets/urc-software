
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to urc_msgs__action__NavigateToWaypoint_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::Path,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: geometry_msgs::msg::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub has_path: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub has_goal: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enforce_goal_heading: bool,

}



impl Default for NavigateToWaypoint_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Goal {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Owned(msg.path)).into_owned(),
        goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
        has_path: msg.has_path,
        has_goal: msg.has_goal,
        enforce_goal_heading: msg.enforce_goal_heading,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Borrowed(&msg.path)).into_owned(),
        goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      has_path: msg.has_path,
      has_goal: msg.has_goal,
      enforce_goal_heading: msg.enforce_goal_heading,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      path: nav_msgs::msg::Path::from_rmw_message(msg.path),
      goal: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.goal),
      has_path: msg.has_path,
      has_goal: msg.has_goal,
      enforce_goal_heading: msg.enforce_goal_heading,
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result: std_msgs::msg::Empty,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,

}

impl NavigateToWaypoint_Result {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SUCCESS: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FAILURE: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OBSTACLE_DETECTED: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PLANNING_FAILED: u16 = 3;

}


impl Default for NavigateToWaypoint_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_Result::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Result {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        result: std_msgs::msg::Empty::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
        error_code: msg.error_code,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        result: std_msgs::msg::Empty::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      error_code: msg.error_code,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      result: std_msgs::msg::Empty::from_rmw_message(msg.result),
      error_code: msg.error_code,
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_to_goal: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_planning: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub replan_count: u16,

}



impl Default for NavigateToWaypoint_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Feedback {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        distance_to_goal: msg.distance_to_goal,
        is_planning: msg.is_planning,
        replan_count: msg.replan_count,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      distance_to_goal: msg.distance_to_goal,
      is_planning: msg.is_planning,
      replan_count: msg.replan_count,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      distance_to_goal: msg.distance_to_goal,
      is_planning: msg.is_planning,
      replan_count: msg.replan_count,
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::NavigateToWaypoint_Feedback,

}



impl Default for NavigateToWaypoint_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_FeedbackMessage {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::NavigateToWaypoint_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::NavigateToWaypoint_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::NavigateToWaypoint_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to urc_msgs__action__NavigateToWaypoint_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::NavigateToWaypoint_Goal,

}



impl Default for NavigateToWaypoint_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_SendGoal_Request {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::NavigateToWaypoint_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::NavigateToWaypoint_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::NavigateToWaypoint_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for NavigateToWaypoint_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_SendGoal_Response {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for NavigateToWaypoint_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_GetResult_Request {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to urc_msgs__action__NavigateToWaypoint_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::NavigateToWaypoint_Result,

}



impl Default for NavigateToWaypoint_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::NavigateToWaypoint_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_GetResult_Response {
  type RmwMsg = super::action::rmw::NavigateToWaypoint_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::NavigateToWaypoint_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::NavigateToWaypoint_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::NavigateToWaypoint_Result::from_rmw_message(msg.result),
    }
  }
}






#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct NavigateToWaypoint_SendGoal;

impl rosidl_runtime_rs::Service for NavigateToWaypoint_SendGoal {
    type Request = NavigateToWaypoint_SendGoal_Request;
    type Response = NavigateToWaypoint_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal() }
    }
}




#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct NavigateToWaypoint_GetResult;

impl rosidl_runtime_rs::Service for NavigateToWaypoint_GetResult {
    type Request = NavigateToWaypoint_GetResult_Request;
    type Response = NavigateToWaypoint_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult() }
    }
}






#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__urc_msgs__action__NavigateToWaypoint() -> *const std::ffi::c_void;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint
#[allow(missing_docs, non_camel_case_types)]
pub struct NavigateToWaypoint;

impl rosidl_runtime_rs::Action for NavigateToWaypoint {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = NavigateToWaypoint_Goal;

  /// The result message defined in the action definition.
  type Result = NavigateToWaypoint_Result;

  /// The feedback message defined in the action definition.
  type Feedback = NavigateToWaypoint_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::NavigateToWaypoint_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::NavigateToWaypoint_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::NavigateToWaypoint_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__urc_msgs__action__NavigateToWaypoint() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::NavigateToWaypoint_Goal,
  ) -> super::action::rmw::NavigateToWaypoint_SendGoal_Request {
   super::action::rmw::NavigateToWaypoint_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::NavigateToWaypoint_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::NavigateToWaypoint_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::NavigateToWaypoint_SendGoal_Response {
   super::action::rmw::NavigateToWaypoint_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::NavigateToWaypoint_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::NavigateToWaypoint_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::NavigateToWaypoint_Feedback,
  ) -> super::action::rmw::NavigateToWaypoint_FeedbackMessage {
    let mut message = super::action::rmw::NavigateToWaypoint_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::NavigateToWaypoint_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::NavigateToWaypoint_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::NavigateToWaypoint_GetResult_Request {
   super::action::rmw::NavigateToWaypoint_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::NavigateToWaypoint_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::NavigateToWaypoint_Result,
  ) -> super::action::rmw::NavigateToWaypoint_GetResult_Response {
   super::action::rmw::NavigateToWaypoint_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::NavigateToWaypoint_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::NavigateToWaypoint_Result,
  ) {
    (response.status, response.result)
  }
}


