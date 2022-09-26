# ROS2 Library and Working package
This repository is created for reference source code which is used on medium article. Please use the following link to access the article
Part 1
Part 2

## Command to build library package
``` colcon build --packages-select try_out_utils ```

## Command to build operational package
``` colcon build --packages-select try_out ```

## Command to test library package
``` colcon test --event-handlers console_direct+ --packages-select try_out_utils ```

## Command to test operational package
``` colcon test --event-handlers console_direct+ --packages-select try_out ```

