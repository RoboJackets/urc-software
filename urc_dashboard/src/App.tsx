import { SelectList } from "./components/SelectList";

function App() {
  return (
    <div className="App w-screen h-screen">
      <SelectList values={["Teleop", "Auto", "Test"]} />
    </div>
  );
}

export default App;
