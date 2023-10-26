import { Coordinate } from "../CoordinateInterface";

interface OdometryProps {
  odometry: Coordinate;
}

export const Odometry = (props: OdometryProps) => {
  return (
    <div className="card">
      <div className="card-subtitle">Odometry</div>
      <div className="whitespace-nowrap">{`Lat: ${props.odometry.lat},  Lng: ${props.odometry.lng}`}</div>
    </div>
  );
};
