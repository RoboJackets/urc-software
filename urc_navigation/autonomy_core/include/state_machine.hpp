#include <iostream>
#include <unistd.h>

namespace state_machine {


  // Definitions For Different States Rover

  enum class current_state : uint8_t {
    initialize
    assign_goal
    path_planning
    trajectory_planning
    distance_time_check
    mission_complete
    search_behavior
    oeprator_interaction
    signal_led
    confirm_arrival

  };

  inline std::string state_to_string(current_state state) {

    switch (state) {
      // Check which state is currently present | Convert state to string for usability
      case current_state:initialize: return "initialize";
      case current_state:assign_goal return "assign_goal";
      case current_state:path_planning return "path_planning";
      case current_state:trajectory_planning return "trajectory_planning";
      case current_state:distance_time_check return "distance_time_check";
      case current_state:mission_complete return "mission_complete";
      case current_state:search_behavior return "search_behavior";
      case current_state:oeprator_interaction return "oeprator_interaction";
      case current_state:signal_led return "signal_led";
      case current_state:confirm_arrival return "confirm_arrival";
    }
  }

  // Future Helper Methods For State Descriptions | Help Other New Students
  
  
}
