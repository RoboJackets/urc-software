# URC Behavior Tree

This package provides the central orchestor for running the behavior tree.

## Launching

You should run `urc_bt_orchestor` node, which is registered as a plugin in this package. For an example, check out `bt.launch.py` under `urc_bringup` package.

There are several parameters for the `urc_bt_orchestor` node:

- `node_lib_dirs`: *array of string*, specifying path to dynamic library files for bt nodes. Will be loaded on runtime.
- `tree_file_dir`: *string*, to the path of .xml file for behavior tree. If not specified, the tree will not be loaded and started on launching.
- `start_bridge`: *bool*, whether initialize some of the convenient variables in the root Blackboard of the current behavior tree.

## Editing the Tree

You can specify path to your tree during launch. For an example, check out `strategies` folder under `urc_bringup` package, which contains `.btproj` containing definitions for all the nodes that is going to be used inside URC.

Note that to provide a bridge between ros and bt, upon launch, `urc_bt_orchestor` write several values to the root Blackboard of the current behavior tree by default. They are:

- `ros_nh`: *shared ptr*, node handle to a ros node.
- `ros_log`: *shared ptr*, a ros logger.

This functionality can be disabled by changing the settings.
