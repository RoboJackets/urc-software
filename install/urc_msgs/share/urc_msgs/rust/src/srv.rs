#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to urc_msgs__srv__GeneratePlan_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GeneratePlan_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: geometry_msgs::msg::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::PoseStamped,

}



impl Default for GeneratePlan_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GeneratePlan_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GeneratePlan_Request {
  type RmwMsg = super::srv::rmw::GeneratePlan_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.start)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.start)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.goal),
      start: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.start),
    }
  }
}


// Corresponds to urc_msgs__srv__GeneratePlan_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GeneratePlan_Response {
    /// Response definition
    pub path: nav_msgs::msg::Path,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GeneratePlan_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GeneratePlan_Response {
  type RmwMsg = super::srv::rmw::GeneratePlan_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Owned(msg.path)).into_owned(),
        error_code: msg.error_code,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Borrowed(&msg.path)).into_owned(),
      error_code: msg.error_code,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      path: nav_msgs::msg::Path::from_rmw_message(msg.path),
      error_code: msg.error_code,
    }
  }
}


// Corresponds to urc_msgs__srv__GenerateSpiralSearch_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GenerateSpiralSearch_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub center: geometry_msgs::msg::PoseStamped,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GenerateSpiralSearch_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GenerateSpiralSearch_Request {
  type RmwMsg = super::srv::rmw::GenerateSpiralSearch_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        center: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.center)).into_owned(),
        search_radius: msg.search_radius,
        track_spacing: msg.track_spacing,
        waypoint_spacing: msg.waypoint_spacing,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        center: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.center)).into_owned(),
      search_radius: msg.search_radius,
      track_spacing: msg.track_spacing,
      waypoint_spacing: msg.waypoint_spacing,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      center: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.center),
      search_radius: msg.search_radius,
      track_spacing: msg.track_spacing,
      waypoint_spacing: msg.waypoint_spacing,
    }
  }
}


// Corresponds to urc_msgs__srv__GenerateSpiralSearch_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GenerateSpiralSearch_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::Path,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GenerateSpiralSearch_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GenerateSpiralSearch_Response {
  type RmwMsg = super::srv::rmw::GenerateSpiralSearch_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Owned(msg.path)).into_owned(),
        track_spacing: msg.track_spacing,
        path_length: msg.path_length,
        traversability_checked: msg.traversability_checked,
        truncated: msg.truncated,
        skipped_waypoints: msg.skipped_waypoints,
        error_code: msg.error_code,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Borrowed(&msg.path)).into_owned(),
      track_spacing: msg.track_spacing,
      path_length: msg.path_length,
      traversability_checked: msg.traversability_checked,
      truncated: msg.truncated,
      skipped_waypoints: msg.skipped_waypoints,
      error_code: msg.error_code,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      path: nav_msgs::msg::Path::from_rmw_message(msg.path),
      track_spacing: msg.track_spacing,
      path_length: msg.path_length,
      traversability_checked: msg.traversability_checked,
      truncated: msg.truncated,
      skipped_waypoints: msg.skipped_waypoints,
      error_code: msg.error_code,
    }
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


