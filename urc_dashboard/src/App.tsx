import { DriverStation } from "./components/DriverStation/DriverStation";
import ROSLIB from "roslib";
import { Navigation } from "./components/Navigation/Navigation";
function App() {
  const ROS = new ROSLIB.Ros({ url: "ws://localhost:9090" });
  return (
    <div className="App w-screen h-screen p-2 flex gap-2">
      <DriverStation ROS={ROS} />
      <Navigation />
    </div>
  );
}

export default App;
