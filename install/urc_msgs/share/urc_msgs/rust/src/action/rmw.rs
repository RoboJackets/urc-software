
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Goal() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_Goal__init(msg: *mut NavigateToWaypoint_Goal) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Goal>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Goal>);
    fn urc_msgs__action__NavigateToWaypoint_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Goal>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::rmw::Path,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: geometry_msgs::msg::rmw::PoseStamped,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_Goal__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Goal() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Result() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_Result__init(msg: *mut NavigateToWaypoint_Result) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Result>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Result>);
    fn urc_msgs__action__NavigateToWaypoint_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Result>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub result: std_msgs::msg::rmw::Empty,


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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_Result__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_Result where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Result() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_Feedback__init(msg: *mut NavigateToWaypoint_Feedback) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Feedback>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Feedback>);
    fn urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_Feedback>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_Feedback__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_Feedback() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(msg: *mut NavigateToWaypoint_FeedbackMessage) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_FeedbackMessage>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_FeedbackMessage>);
    fn urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_FeedbackMessage>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::NavigateToWaypoint_Feedback,

}



impl Default for NavigateToWaypoint_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_FeedbackMessage() }
  }
}




#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(msg: *mut NavigateToWaypoint_SendGoal_Request) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Request>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Request>);
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Request>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::NavigateToWaypoint_Goal,

}



impl Default for NavigateToWaypoint_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal_Request() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(msg: *mut NavigateToWaypoint_SendGoal_Response) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Response>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Response>);
    fn urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_SendGoal_Response>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for NavigateToWaypoint_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_SendGoal_Response() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(msg: *mut NavigateToWaypoint_GetResult_Request) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Request>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Request>);
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Request>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for NavigateToWaypoint_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult_Request() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(msg: *mut NavigateToWaypoint_GetResult_Response) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Response>, size: usize) -> bool;
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Response>);
    fn urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigateToWaypoint_GetResult_Response>) -> bool;
}

// Corresponds to urc_msgs__action__NavigateToWaypoint_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigateToWaypoint_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::NavigateToWaypoint_Result,

}



impl Default for NavigateToWaypoint_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__action__NavigateToWaypoint_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__action__NavigateToWaypoint_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigateToWaypoint_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__action__NavigateToWaypoint_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigateToWaypoint_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigateToWaypoint_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/action/NavigateToWaypoint_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__action__NavigateToWaypoint_GetResult_Response() }
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


