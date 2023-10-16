export interface Odometry {
  lat: number;
  lng: number;
}
interface OdometryProps {
  odometry: Odometry;
}

export const Odometry = (props: OdometryProps) => {
  const d = "0";
  return (
    <div className="card">
      <div className="card-subtitle">Odometry</div>
      <div className="whitespace-nowrap">{`Lat: ${props.odometry.lat},  Lng: ${props.odometry.lng}`}</div>
    </div>
  );
};
