import { DriverStation } from "./components/DriverStation/DriverStation";
import ROSLIB from "roslib";
function App() {
  const ROS = new ROSLIB.Ros({ url: "ws://localhost:9090" });
  return (
    <div className="App w-screen h-screen p-2">
      <DriverStation ROS={ROS} />
    </div>
  );
}

export default App;
