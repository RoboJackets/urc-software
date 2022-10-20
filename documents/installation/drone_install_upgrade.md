# Drone install 
This is for members who followed the old install instructions. 

## 1. Navigate to `/colcon-urc`

## 2. Move back one directory
```bash
cd ..
```

## 3. Create `/urc` directory
```bash
mkdir urc
```

## 4. Move `/colcon-urc` into `/urc`
```bash
mv colcon-urc urc
```

## 5. Rename `/colcon-urc` to `/rover-colcon`
```bash
mv colcon-urc/ rover-colcon
```

## 6. Follow the [drone install steps](ubuntu_installation.md#drone), ignoring the first directory change as you should already be in `/urc`
