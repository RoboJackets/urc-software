import { DriverStation } from "./components/DriverStation";
import ROSLIB from "roslib";
function App() {
  const ROS = new ROSLIB.Ros({ url: "ws://localhost:9090" });
  return (
    <div className="App w-screen h-screen">
      <DriverStation ROS={ROS} />
    </div>
  );
}

export default App;
