#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GeneratePlan_Request() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__srv__GeneratePlan_Request__init(msg: *mut GeneratePlan_Request) -> bool;
    fn urc_msgs__srv__GeneratePlan_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Request>, size: usize) -> bool;
    fn urc_msgs__srv__GeneratePlan_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Request>);
    fn urc_msgs__srv__GeneratePlan_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GeneratePlan_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Request>) -> bool;
}

// Corresponds to urc_msgs__srv__GeneratePlan_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GeneratePlan_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: geometry_msgs::msg::rmw::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::rmw::PoseStamped,

}



impl Default for GeneratePlan_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__srv__GeneratePlan_Request__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__srv__GeneratePlan_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GeneratePlan_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GeneratePlan_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GeneratePlan_Request where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/srv/GeneratePlan_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GeneratePlan_Request() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GeneratePlan_Response() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__srv__GeneratePlan_Response__init(msg: *mut GeneratePlan_Response) -> bool;
    fn urc_msgs__srv__GeneratePlan_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Response>, size: usize) -> bool;
    fn urc_msgs__srv__GeneratePlan_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Response>);
    fn urc_msgs__srv__GeneratePlan_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GeneratePlan_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GeneratePlan_Response>) -> bool;
}

// Corresponds to urc_msgs__srv__GeneratePlan_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GeneratePlan_Response {
    /// Response definition
    pub path: nav_msgs::msg::rmw::Path,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,

}

impl GeneratePlan_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SUCCESS: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FAILURE: u16 = 1;

}


impl Default for GeneratePlan_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__srv__GeneratePlan_Response__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__srv__GeneratePlan_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GeneratePlan_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GeneratePlan_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GeneratePlan_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GeneratePlan_Response where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/srv/GeneratePlan_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GeneratePlan_Response() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GenerateSpiralSearch_Request() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__srv__GenerateSpiralSearch_Request__init(msg: *mut GenerateSpiralSearch_Request) -> bool;
    fn urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Request>, size: usize) -> bool;
    fn urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Request>);
    fn urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Request>) -> bool;
}

// Corresponds to urc_msgs__srv__GenerateSpiralSearch_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GenerateSpiralSearch_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub center: geometry_msgs::msg::rmw::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub search_radius: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub track_spacing: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub waypoint_spacing: f64,

}



impl Default for GenerateSpiralSearch_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__srv__GenerateSpiralSearch_Request__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__srv__GenerateSpiralSearch_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GenerateSpiralSearch_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GenerateSpiralSearch_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GenerateSpiralSearch_Request where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/srv/GenerateSpiralSearch_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GenerateSpiralSearch_Request() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GenerateSpiralSearch_Response() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__srv__GenerateSpiralSearch_Response__init(msg: *mut GenerateSpiralSearch_Response) -> bool;
    fn urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Response>, size: usize) -> bool;
    fn urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Response>);
    fn urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GenerateSpiralSearch_Response>) -> bool;
}

// Corresponds to urc_msgs__srv__GenerateSpiralSearch_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GenerateSpiralSearch_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::rmw::Path,


    // This member is not documented.
    #[allow(missing_docs)]
    pub track_spacing: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path_length: f64,

    /// True when the path was routed against the traversability map.
    pub traversability_checked: bool,

    /// True when the outer part of the spiral was dropped because no safe route reached it.
    pub truncated: bool,

    /// Spiral waypoints left out of the path because they were blocked or unreachable.
    pub skipped_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,

}

impl GenerateSpiralSearch_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const SUCCESS: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const FAILURE: u16 = 2;

    /// No fresh traversability map was available and the server requires one.
    pub const MAP_UNAVAILABLE: u16 = 3;

    /// Every spiral waypoint was blocked or unreachable on the traversability map.
    pub const NO_TRAVERSABLE_PATH: u16 = 4;

}


impl Default for GenerateSpiralSearch_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__srv__GenerateSpiralSearch_Response__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__srv__GenerateSpiralSearch_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GenerateSpiralSearch_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__srv__GenerateSpiralSearch_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GenerateSpiralSearch_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GenerateSpiralSearch_Response where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/srv/GenerateSpiralSearch_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__srv__GenerateSpiralSearch_Response() }
  }
}






#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__srv__GeneratePlan() -> *const std::ffi::c_void;
}

// Corresponds to urc_msgs__srv__GeneratePlan
#[allow(missing_docs, non_camel_case_types)]
pub struct GeneratePlan;

impl rosidl_runtime_rs::Service for GeneratePlan {
    type Request = GeneratePlan_Request;
    type Response = GeneratePlan_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__srv__GeneratePlan() }
    }
}




#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__srv__GenerateSpiralSearch() -> *const std::ffi::c_void;
}

// Corresponds to urc_msgs__srv__GenerateSpiralSearch
#[allow(missing_docs, non_camel_case_types)]
pub struct GenerateSpiralSearch;

impl rosidl_runtime_rs::Service for GenerateSpiralSearch {
    type Request = GenerateSpiralSearch_Request;
    type Response = GenerateSpiralSearch_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__urc_msgs__srv__GenerateSpiralSearch() }
    }
}


